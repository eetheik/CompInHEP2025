
import ROOT
from ROOT import TF1, TFile, TCanvas, TLegend
import numpy as np

LUMINOSITY = 1 # Set luminosity to 1 fb^-1 for now and figure out the actual scaling necessary for 5 sigma later

def read_metadata(file):
    try:
        sigma = float(file.Get("cross_section").GetTitle())  # fb
        n_gen = int(file.Get("n_generated").GetTitle())
        return sigma, n_gen
    except Exception as e:
        raise RuntimeError(f"Error reading metadata: {e}")

# Open ROOT files safely
f_sig = TFile.Open("signal_1e6_15_500GeV.root")
f_bkg = TFile.Open("background_3e6.root")
if not f_sig or f_sig.IsZombie():
    raise FileNotFoundError("Failed to open signal.root")
if not f_bkg or f_bkg.IsZombie():
    raise FileNotFoundError("Failed to open background.root")

h_sig = f_sig.Get("h_mass")
h_bkg = f_bkg.Get("h_mass")

# Make sure the histograms are going to be in Events/GeV instead of Events/bin
for bin in range(1, h_sig.GetNbinsX() + 1):
    bin_width = h_sig.GetBinWidth(bin)
    content = h_sig.GetBinContent(bin)
    error = h_sig.GetBinError(bin)
    h_sig.SetBinContent(bin, content / bin_width)
    h_sig.SetBinError(bin, error / bin_width)

for bin in range(1, h_bkg.GetNbinsX() + 1):
    bin_width = h_bkg.GetBinWidth(bin)
    content = h_bkg.GetBinContent(bin)
    error = h_bkg.GetBinError(bin)
    h_bkg.SetBinContent(bin, content / bin_width)
    h_bkg.SetBinError(bin, error / bin_width)

if not h_sig or not h_bkg:
    raise RuntimeError("Histogram 'h_mass' not found in input files.")

# Old lines from the code, still useful information so I leave it here as a comment
# SIGMA_SIGNAL, N_GEN_SIGNAL = read_metadata(f_sig) 
# SIGMA_BKG, N_GEN_BKG = read_metadata(f_bkg)

low_b = 50
up_b = 250

# Cut histograms to desired range (zero bins in undesired domain)
for bin in range(1, h_bkg.GetNbinsX() + 1):
    center = h_bkg.GetBinCenter(bin)
    if center < low_b or center > up_b:
        h_bkg.SetBinContent(bin, 0)
        h_bkg.SetBinError(bin, 0)

for bin in range(1, h_sig.GetNbinsX() + 1):
    center = h_sig.GetBinCenter(bin)
    if center < low_b or center > up_b:
        h_sig.SetBinContent(bin, 0)
        h_sig.SetBinError(bin, 0)

# .GetEntries() doesn't care for the zeroed histogram bins, they're just full of N zeroes. This works around that
def get_entries_in_range(hist, xmin, xmax):
    total = 0
    for bin in range(1, hist.GetNbinsX() + 1):
        center = hist.GetBinCenter(bin)
        if xmin <= center <= xmax:
            total += hist.GetBinContent(bin)
    return total

N_PASS_BG = get_entries_in_range(h_bkg, low_b, up_b)
N_PASS_SIGNAL = get_entries_in_range(h_sig, low_b, up_b)

# Non standard model-like signal cross section (sort of resolves small background issue)
SIGMA_SIGNAL = 62 * 1e3
SIGMA_BKG = 924 * 1e3


# Normalize histograms
scale_sig =  (SIGMA_SIGNAL * LUMINOSITY) / N_PASS_SIGNAL 
scale_bkg =  (SIGMA_BKG * LUMINOSITY) / N_PASS_BG
h_sig.Scale(scale_sig)
h_bkg.Scale(scale_bkg)
# print(f"SIGNAL: {N_TRIG_SIGNAL}")
# print(f"BKG: {N_TRIG_BKG}")

h_sig.SetTitle("Invariant Mass Spectrum")
h_sig.GetXaxis().SetTitle("#it{M}_{#mu#mu} [GeV]")
h_sig.GetYaxis().SetTitle("Events / GeV")
h_sig.GetXaxis().SetTitleSize(0.045)
h_sig.GetYaxis().SetTitleSize(0.045)
h_sig.GetXaxis().SetRangeUser(low_b, up_b)

# Combined signal + background histogram
h_sum = h_sig.Clone("h_sum")
h_sum.Add(h_bkg)

# Draw histograms
c = TCanvas("c", "Invariant Mass", 800, 600)
c.SetLogy() 
# c.SetLogx()

h_sig.SetLineColor(ROOT.kRed)
h_bkg.SetLineColor(ROOT.kBlue)
h_sum.SetLineColor(ROOT.kBlack)

for hist in (h_sig, h_bkg, h_sum): # Disables stats box
    hist.SetStats(0)

# Draw
h_sum.Draw("HIST")
h_bkg.Draw("HIST SAME")
h_sig.Draw("HIST SAME")
h_sig.Draw("E1 SAME")
h_bkg.Draw("E1 SAME")

# Legend
legend = TLegend(0.55, 0.65, 0.85, 0.85)
legend.AddEntry(h_sig, "Signal #it{(}#it{Z}#rightarrow#mu#mu#it{)} ", "l")
legend.AddEntry(h_bkg, "Background #it{(}#it{t}#bar{#it{t}}#it{)} ", "l")
legend.AddEntry(h_sum, "Total", "l")
legend.Draw()

# Defining fit functions
# def signal(x, p): # Signal modeled as a double sided crystal ball
#     # p[0]: gaussian core mean
#     # p[1]: gaussian core stdev
#     # p[2]: alpha left
#     # p[3]: power law exponent left
#     # p[4]: alpha right
#     # p[5]: power law exponent right
#     # p[6]: amplitude
#     t = (x[0] - p[0]) / (p[1])
#     if t < -p[2]:  # Left tail
#         a = np.power(p[3]/p[2], p[3]) * np.exp(-0.5 * p[2]**2)
#         b = p[3]/p[2] - p[2]
#         return p[6] * a / np.power(b - t, p[3])
#     elif t > p[4]:  # Right tail
#         a = np.power(p[5]/p[4], p[5]) * np.exp(-0.5 * p[4]**2)
#         b = p[5]/p[4] - p[4]
#         return p[6] * a / np.power(b + t, p[5])
#     else:  # Gaussian core
#         return p[6] * np.exp(-0.5 * t**2)

def signal(x, p): # Signal modeled as relativistic breit wigner
    return p[0] * ROOT.TMath.BreitWignerRelativistic(x[0], p[1], p[2])

def background(x, p): # background modeled as A / (1+ax+bx^2)
    # p[0]: amplitude
    # p[1]: linear part
    # p[2]: quadratic part
    return p[0] / (1 + p[1]*x[0] + p[2]*x[0]*x[0])

def full_model(x, p):
    # The list object stored in p gets converted to a cppyy.LowLevelView object when passed to ROOT, 
    # which doesn't admit standard Python list slicing, leading to a segfault so queue this stupid-looking solution
    # p_sig = [p[i] for i in range(7)] 
    # p_bg = [p[i] for i in range(7, 10)]
    p_sig = [p[i] for i in range(3)]
    p_bg = [p[i] for i in range(3, 6)]
    return signal(x, p_sig) + background(x, p_bg)

fit_min, fit_max = low_b, up_b

# Fit full model to background + signal distribution
fit = TF1("fit", full_model, fit_min, fit_max, 6)
fit.SetParameters(5e4, 91.2, 0.02, 1e4, -0.01, 1e-5)
fit.SetParLimits(0, 0.0, 1e5)
fit.SetParLimits(1, 89.0, 93.0)
fit.SetParLimits(2, 0.0, 5.0)
fit.SetParLimits(3, 0.0, 1e5)
fit.SetParLimits(4, -2.0, 2.0)
fit.SetParLimits(5, -1.0, 1.0)
h_sum.Fit(fit, "R")
fit.SetLineColor(ROOT.kBlack)
fit.SetLineStyle(2)  
fit.Draw("SAME")

# Plot the individual bg + signal parts obtained from the total fit
bg_func = TF1("bg", background, fit_min, fit_max, 3)
bg_func.SetParameter(0, fit.GetParameter(3))
bg_func.SetParameter(1, fit.GetParameter(4))
bg_func.SetParameter(2, fit.GetParameter(5))
bg_func.SetLineColor(ROOT.kBlue)
bg_func.SetLineStyle(2)  
bg_func.Draw("SAME")

sig_func = TF1("sig", signal, fit_min, fit_max, 7)
sig_func.SetParameter(0, fit.GetParameter(0))
sig_func.SetParameter(1, fit.GetParameter(1))
sig_func.SetParameter(2, fit.GetParameter(2))
sig_func.SetLineColor(ROOT.kRed)
sig_func.SetLineStyle(2)  
sig_func.Draw("SAME")

# Comment out, this was used to check if the combined fit was as good as one could expect
# fit_bg = TF1("fit_bg", background, fit_min, fit_max, 3)
# fit_bg.SetParameters(1e4, -0.001, 1e-5)
# h_bkg.Fit(fit_bg, "R")
# fit_bg.SetLineColor(ROOT.kBlack)
# fit_bg.SetLineStyle(2)  
# fit_bg.Draw("SAME")

# fit_sig = TF1("fit_sig", signal, fit_min, fit_max, 7)
# fit_sig.SetParameters(91.2, 2.0, 1.0, 3.0, 2.0, 3.0, 3e7)
# h_sig.Fit(fit_sig, "R")
# fit_sig.SetLineColor(ROOT.kBlack)
# fit_sig.SetLineStyle(2)  
# fit_sig.Draw("SAME")

# Define mass window and calculate integrals
mass_min, mass_max = 60, 120
bin_width = h_sum.GetBinWidth(1)

N_total = fit.Integral(mass_min, mass_max) / bin_width
N_bkg = bg_func.Integral(mass_min, mass_max) / bin_width

# Signal count and significance
N_sig = N_total - N_bkg
significance = N_sig / np.sqrt(N_bkg) if N_bkg > 0 else 0

# Required luminosity for 5 sigma
required_lumi = (5 / significance) ** 2 * LUMINOSITY if significance > 0 else float("inf")

# Print results
print(f"N_S = {N_sig:.1f}, N_B = {N_bkg:.1f}")
print(f"Significance: {significance:.2f} sigma")
print(f"Integrated luminosity for 5 sigma: {required_lumi:.6f} fb^-1")

# Save canvas
c.SaveAs("invariant_mass.pdf")
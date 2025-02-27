#!/usr/bin/env python3
import ROOT
import numpy as np

def histogram_macro():
    # TFile *file = TFile::Open("tree.root", "READ");
    file = ROOT.TFile.Open("tree.root", "READ")

    # TTree *tree = (TTree*) file->Get("tree"); 
    tree = file.Get("tree")

    # double x; 
    x = np.zeros(1, dtype=np.float64)

    # tree->SetBranchAddress("x", &x);
    tree.SetBranchAddress("x", x)

    # TH1D *hist = new TH1D("hist", "Histogram", 50, -3, 3);
    hist = ROOT.TH1D("hist", "Histogram", 50, -3, 3)

    # int N = tree->GetEntries();
    N = tree.GetEntries()

    # for (int i = 0; i < N; i++) {
    #     tree->GetEntry(i);
    #     hist->Fill(x);
    # }
    for i in range(1000):
        tree.GetEntry(i)
        hist.Fill(x)

    # hist->SetLineWidth(2);
    # hist->SetFillColor(kYellow);
    # hist->SetXTitle("x");
    # hist->SetYTitle("y");
    hist.SetLineWidth(2)
    hist.SetFillColor(ROOT.kYellow)
    hist.GetXaxis().SetTitle("x")
    hist.GetYaxis().SetTitle("y")

    # hist->Fit("gaus"); 
    hist.Fit("gaus")

    # TCanvas *c = new TCanvas("c", "Canvas", 800, 600);
    c = ROOT.TCanvas("c", "Canvas", 800, 600)

    # hist->Draw();
    hist.Draw()

    # c->SaveAs("histogram.png");
    c.SaveAs("histogram.png")

    # std::cout << "Histogram saved to histogram.png" << std::endl;
    print("Histogram saved to histogram.png")

    # file->Close();
    # c->Close();
    file.Close()
    c.Close()

# int main() {
#     histogram_macro();
#     return 0;
# }
def main():
    histogram_macro()

if __name__ == "__main__":
    main()
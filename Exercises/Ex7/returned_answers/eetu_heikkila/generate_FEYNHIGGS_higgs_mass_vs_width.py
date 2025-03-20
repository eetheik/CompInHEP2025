import subprocess
import numpy as np
import os

def main():
    # I made a separate folder for FeynHiggs but I think there is a smarter way to do this
    # How?
    FEYNHIGGS_PATH = f"{os.path.expanduser("~/FeynHigs/FeynHiggs-2.19.0")}"
    subprocess.run(f'{FEYNHIGGS_PATH}/build/f++ -o demo -I{FEYNHIGGS_PATH}/build demo.cc {FEYNHIGGS_PATH}/build/libFH.a', shell=True, check=True)

    higgs_masses = np.linspace(80, 300, 100)
    # higgs_masses = np.arange(115, 135.2, 0.2)

    with open("FEYNHIGGS_simulation_result_raw.dat", "w") as f:
        for higgs_mass in higgs_masses:
            print(f"Simulating HIGGS_MASS = {higgs_mass}")
            result = subprocess.run(f'./demo {higgs_mass}', shell=True, capture_output=True, text=True)
            f.write(result.stdout) 

    # Removing these lines was quite annoying, maybe regex would have been preferable
    removable_phrases = [
        "------------------------------------------------------------------------------",
        "FeynHiggs 2.19.0",
        "built on Mar 13, 2025",
        "H. Bahl, T. Hahn, S. Heinemeyer, W. Hollik, S. Passehr, H. Rzehak, G. Weiglein",
        "http://feynhiggs.de",
        "FHHiggsCorr contains code by:",
        "P. Slavich et al. (2L rMSSM Higgs self-energies)",
        "H. Rzehak et al. (2L cMSSM asat Higgs self-energies)",
        "S. Passehr et al. (2L cMSSM atat Higgs self-energies)",
        "FHCouplings warning: Extrapolating GammaSM(H0VV(1,3)) in MHiggs",
        "FHCouplings warning: Extrapolating GammaSM(H0VV(1,4)) in MHiggs",
        "FHCouplings warning: Extrapolating GammaSM(H0VV(3,3)) in MHiggs",
        "FHCouplings warning: Extrapolating GammaSM(H0VV(3,4)) in MHiggs"
    ]

    with open("FEYNHIGGS_simulation_result_raw.dat", "r") as f1:
        lines = f1.readlines()

    cleaned_data = []

    for line in lines:
        clean_line = line.strip()  
        if not any(phrase in clean_line for phrase in removable_phrases):  
            cleaned_data.append(line)

    with open("FEYNHIGGS_higgs_mass_vs_width.dat", "w") as f2:
        f2.writelines(cleaned_data)

    print("Data saved to FEYNHIGGS_higgs_mass_vs_width.dat")

main()

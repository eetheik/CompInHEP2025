#!/usr/bin/env python3
import ROOT
import numpy as np

def tree_macro():
    x = np.zeros(1, dtype=np.float64)

    file = ROOT.TFile("tree.root", "RECREATE")

    tree = ROOT.TTree("tree", "tree")

    tree.Branch("x", x, "x/D")

    for i in range(1000):
        x[0] = ROOT.gRandom.Gaus(0,1)
        tree.Fill()
    
    tree.Write()
    file.Close()

def main():
    tree_macro()

if __name__ == "__main__":
    main()
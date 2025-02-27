#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <iostream>

void histogram_macro() {
    TFile *file = TFile::Open("tree.root", "READ");

    // Returns a TObject so cast this to a TTree
    TTree *tree = (TTree*) file->Get("tree"); 

    double x;
    tree->SetBranchAddress("x", &x);

    TH1D *hist = new TH1D("hist", "Histogram", 50, -3, 3);

    int N = tree->GetEntries();
    for (int i = 0; i < N; i++) {
        tree->GetEntry(i);
        hist->Fill(x);
    }

    hist->SetLineWidth(2);
    hist->SetFillColor(kYellow);
    hist->SetXTitle("x");
    hist->SetYTitle("y");

    hist->Fit("gaus"); 
    TCanvas *c = new TCanvas("c", "Canvas", 800, 600);
    hist->Draw();
    c->SaveAs("histogram.png");
    std::cout << "Histogram saved to histogram.png" << std::endl;
    file->Close();
    c->Close();
}

int main() {
    histogram_macro();
    return 0;
}
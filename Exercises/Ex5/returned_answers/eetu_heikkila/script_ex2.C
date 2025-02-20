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

    // This creates an empty canvas that opens up on my screen, how to prevent that?
    // Doesn't happen with makefile because there I can suppress opening the GUI with -l
    hist->Fit("gaus"); 
    TCanvas *c = new TCanvas("c", "Canvas", 800, 600);
    hist->Draw();
    c->SaveAs("histogram.png");
    file->Close();
    c->Close();
}
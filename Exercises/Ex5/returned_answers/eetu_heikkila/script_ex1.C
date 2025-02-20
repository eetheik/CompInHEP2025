void tree_macro() {
    const int N = 1000;
    double x;

    TFile *file = new TFile("tree.root", "RECREATE");

    TTree *tree = new TTree("tree", "tree");

    tree->Branch("x", &x, "x/D");

    for (int i = 0; i < N; i++) {
        x = gRandom->Gaus(0, 1);
        tree->Fill();
    }

    tree->Write();
    file->Close();

}
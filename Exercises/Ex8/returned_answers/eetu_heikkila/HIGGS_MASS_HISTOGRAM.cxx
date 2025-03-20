// Compile and run using make HIGGS_MASS_HISTOGRAM

void HIGGS_MASS_HISTOGRAM() {
    TTree *tree = new TTree("tree", "Tree with Higgs masses");
    tree->ReadFile("higgs_masses.dat", "mass/F");
    
    TH1F *h1 = new TH1F("h1", "Histogram; Higgs mass (GeV); Frequency", 100, 124.95, 125.05);
    // h1->GetXaxis()->SetTitle("Higgs mass (GeV)");
    // h1->GetYaxis()->SetTitle("Frequency (in 1000 runs)");

    float mass;
    tree->SetBranchAddress("mass", &mass);

    for (int i = 0; i < tree->GetEntries(); i++) {
        tree->GetEntry(i); 
        h1->Fill(mass); 
    }

    TF1 *bw = new TF1("bw", "[0]*TMath::BreitWigner(x, [1], [2])", 124.95, 125.05);
    bw->SetParNames("Amplitude", "Mean", "Width");
    bw->SetParameters(h1->GetMaximum(), 125, 0.004083);
    bw->SetParLimits(1, 124, 126);     
    bw->SetParLimits(2, 0.001, 0.01);  

    h1->Fit("bw", "R");

    TCanvas *canvas = new TCanvas("canvas", "Canvas", 800, 600);

    h1->Draw();
    bw->Draw("same");

    canvas->SaveAs("higgs_mass_histogram.png");
    std::cout << "Read the Breit-Wigner width from the above curve-fit!" << std::endl;
    std::cout << "Histogram saved to higgs_mass_histogram.png" << std::endl;
}
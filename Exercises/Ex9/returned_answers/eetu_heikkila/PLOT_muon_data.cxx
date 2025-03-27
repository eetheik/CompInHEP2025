void PLOT_muon_data() {
    TH1F *h_eta = new TH1F("h_eta", "Pseudorapidity", 100, 0.0, 10.0);
    TH1F *h_pT = new TH1F("h_pT", "Transverse momentum", 50, 0.0, 5.0);

    std::ifstream eta_file("eta.dat");
    std::ifstream pT_file("pT.dat");
    
    if (!eta_file.is_open() || !pT_file.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    double eta, pT;
    int total_events, events_satisfying_cuts = 0;

    while (eta_file >> eta && pT_file >> pT) {
        h_eta->Fill(std::abs(eta));
        h_pT->Fill(pT);
        total_events++;
        if (std::abs(eta) < 2.5 && pT > 5.0) {
            events_satisfying_cuts++;
            // std::cout << eta << std::endl;
            // std::cout << pT << std::endl;
        }
    }

    eta_file.close();
    pT_file.close();

    TCanvas *c1 = new TCanvas("c1", "Data Histogram", 1600, 1200);
    c1->Divide(1,2);
    c1->cd(1);
    // c1->SetGridx();
    // c1->SetGridy();
    h_eta->SetFillColor(kBlue);
    h_eta->SetFillStyle(3003);
    h_eta->Draw();
    c1->cd(2);
    // c1->SetGridx();
    // c1->SetGridy();
    h_pT->SetFillColor(kBlue);
    h_pT->SetFillStyle(3003);
    h_pT->Draw();
    c1->Update();

    c1->SaveAs("muon_data.jpg");
    c1->Close();

    double P_muon_eta25_pt50 = float(events_satisfying_cuts) / float(total_events);
    std::cout << "Probability of minimum bias muon with |eta| < 2.5 & pT > 5 GeV/c: " << P_muon_eta25_pt50 << std::endl;
    std::cout << "Simulated histograms outputted to muon_data.jpg" << std::endl;
}
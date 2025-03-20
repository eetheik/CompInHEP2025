void plot_higgs_mass_vs_width() {
    TCanvas *canvas = new TCanvas("canvas", "Higgs Mass vs Width");
    canvas->Divide(1, 2);
    canvas->cd(1);
    gPad->SetLogy();

    TGraph *graph1 = new TGraph("FEYNHIGGS_higgs_mass_vs_width.dat", "%lg %lg");
    TGraph *graph2 = new TGraph("HDECAY_higgs_mass_vs_width.dat", "%lg %lg");
    graph1->SetLineWidth(2);
    graph2->SetLineWidth(2);
    graph1->SetLineColor(1);
    graph2->SetLineColor(2);
    // graph1->SetMarkerStyle(1);
    // graph2->SetMarkerStyle(2);

    TMultiGraph *mg  = new TMultiGraph();
    mg->Add(graph1);
    mg->Add(graph2);
    mg->Draw("ALP");
    mg->GetXaxis()->SetTitle("Mass (GeV)");
    mg->GetYaxis()->SetTitle("Total width");

    TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->AddEntry(graph1,"FEYNHIGGS", "l");
    legend->AddEntry(graph2,"HDECAY", "l");
    legend->Draw();
    canvas->SaveAs("higgs_mass_vs_width.png");

    canvas->cd(2);
    // gPad->SetLogy(0);

    int n = graph1->GetN();
    TGraph *ratioGraph = new TGraph(n);

    for (int i = 0; i < n; i++) {
        double x, y1, y2;
        graph1->GetPoint(i, x, y1);
        graph2->GetPoint(i, x, y2);
        if (y2 != 0) {
            ratioGraph->SetPoint(i, x, y1 / y2);
        }
    }

    ratioGraph->SetMarkerSize(1);
    ratioGraph->SetTitle("Ratio: FEYNHIGGS / HDECAY");
    ratioGraph->GetXaxis()->SetTitle("Mass (GeV)");
    ratioGraph->GetYaxis()->SetTitle("Ratio");
    ratioGraph->Draw("ALP");

    canvas->SaveAs("higgs_mass_vs_width.png");

    canvas->Close();
    delete canvas;
    delete mg;
    delete graph1;
    delete graph2;
    delete ratioGraph;
    delete legend;
}
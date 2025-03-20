void plot_HDECAY_higgs_mass_vs_width() {
    TCanvas *canvas = new TCanvas("canvas", "Higgs Mass vs Width");
    canvas->SetLogy();
    // The data is obtained from the output file via
    // awk ’NR > 2 {print $1, $7}’ br.sm2 > HDECAY higgs mass vs width.dat
    TGraph *graph = new TGraph("HDECAY_higgs_mass_vs_width.dat", "%lg %lg");
    graph->SetLineWidth(2);
    graph->GetXaxis()->SetTitle("Mass (GeV)");
    graph->GetYaxis()->SetTitle("Total width");
    graph->Draw("AC");
    canvas->SaveAs("HDECAY_higgs_mass_vs_width.png");
}
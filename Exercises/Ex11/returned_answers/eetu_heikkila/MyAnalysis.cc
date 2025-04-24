#define MyAnalysis_cxx
// The class definition in MyAnalysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("MyAnalysis.C")
// root> T->Process("MyAnalysis.C","some options")
// root> T->Process("MyAnalysis.C+")
//


#include "MyAnalysis.h"
#include <TH2.h>
#include <TStyle.h>

#include "TLorentzVector.h"

void MyAnalysis::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   hist_pileup = new TH1F("hist_pileup","Pileup distribution after HLT_IsoMu24 trigger",100,0,100);
}

void MyAnalysis::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

bool MyAnalysis::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   fReader.SetLocalEntry(entry);

   if (*HLT_IsoMu24 == false) return false;

   hist_pileup->Fill(*PV_npvs);

   return true;

   // if(*nMuon != 2) return false;

   // if((Muon_charge[0] + Muon_charge[1]) != 0) return false;

   // TLorentzVector muon1,muon2;
   // muon1.SetPtEtaPhiM(Muon_pt[0],Muon_eta[0],Muon_phi[0],Muon_mass[0]);
   // muon2.SetPtEtaPhiM(Muon_pt[1],Muon_eta[1],Muon_phi[1],Muon_mass[1]);
   // TLorentzVector dimuon = muon1+muon2;

   // h_mass->Fill(dimuon.M());
   // std::cout << "Di-Muon mass " << dimuon.M() << std::endl;
     
   // return true;
}

void MyAnalysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void MyAnalysis::Terminate(){
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

//   TFile* fOUT = TFile::Open("output.root","RECREATE");
//   fOUT->cd();

//   std::time_t result = std::time(nullptr);
//   TNamed* timestamp = new TNamed(std::asctime(std::localtime(&result)),"");
//   timestamp->Write();

//   h_mass->Write();
//   fOUT->Close();
   hist_pileup->Write();
      
   TCanvas *c1 = new TCanvas("c1", "Pileup Distribution", 800, 600);
   hist_pileup->Draw();
   c1->SaveAs("pileup_distribution.png");
}

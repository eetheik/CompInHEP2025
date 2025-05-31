// signal.cc
#include "Pythia8/Pythia.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include <vector>
#include <iostream>

using namespace Pythia8;

bool passesTrigger(const TLorentzVector& mu1, const TLorentzVector& mu2) {
    return (fabs(mu1.Eta()) < 2.1 && mu1.Pt() > 20.0 &&
            fabs(mu2.Eta()) < 2.1 && mu2.Pt() > 20.0);
}

// Apply Gaussian smearing to muon kinematics (to simulate detector resolution)
void smearMuon(TLorentzVector& muon, TRandom3& rng) {
    float smear = rng.Gaus(1.0, 0.01); // pT smearing
    float theta = muon.Theta() + rng.Gaus(0.0, 0.002); // angle smearing
    float phi = muon.Phi() + rng.Gaus(0.0, 0.002);
    float pt = muon.Pt() * smear;
    float mass = muon.M();
    float px = pt * cos(phi);
    float py = pt * sin(phi);
    float pz = pt / tan(theta);
    float energy = sqrt(px*px + py*py + pz*pz + mass*mass);
    muon.SetPxPyPzE(px, py, pz, energy); // update muon 4-momentum
}

bool isIsolated(const TLorentzVector& muon, const std::vector<TLorentzVector>& pions) {
    float ptSum = 0.0;
    for (const auto& pion : pions) {
        // If we want to make sure this would be realistic in CMS we 
        // would need some constraint on realistic pseudorapidies and p_Ts
        // if (pion.Pt() < 0.1 || fabs(pion.Eta()) > 2.5) continue; 
        if (muon.DeltaR(pion) < 0.3) ptSum += pion.Pt();
    }
    return ptSum < 1.5;
}

int main() {
    Pythia pythia;
    pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
    pythia.readString("23:onMode = off");
    pythia.readString("23:onIfMatch = 13 -13");
    pythia.readString("Beams:eCM = 13600.");
    pythia.readString("PhaseSpace:mHatMin = 15.");
    pythia.readString("PhaseSpace:mHatMax = 500.");
    pythia.init();

    TFile* file = new TFile("signal_1e6_15_500GeV.root", "RECREATE");
    TTree* tree = new TTree("Events", "Signal Events");
    TH1F* hist = new TH1F("h_mass", "Zmumu Invariant Mass;M_{#mu#mu} [GeV];Events", 485, 15, 500);
    TRandom3 rng(0);

    float mu1_pt, mu2_pt, mass;
    int isSignal = 1;
    tree->Branch("mu1_pt", &mu1_pt, "mu1_pt/F");
    tree->Branch("mu2_pt", &mu2_pt, "mu2_pt/F");
    tree->Branch("mass", &mass, "mass/F");
    tree->Branch("isSignal", &isSignal, "isSignal/I");

    int totalEvents = 0;
    int triggeredEvents = 0;
    int ptPassed = 0, isoPassed = 0, massPassed = 0;

    for (int i = 0; i < 1000000; ++i) {
        if (!pythia.next()) continue;
        totalEvents++;


        std::vector<TLorentzVector> muons, pions;
        for (int j = 0; j < pythia.event.size(); ++j) {
            const auto& p = pythia.event[j];
            if (p.id() == 13 || p.id() == -13) {
                TLorentzVector mu; mu.SetPxPyPzE(p.px(), p.py(), p.pz(), p.e());
                muons.push_back(mu);
            }
            if (p.idAbs() == 211 && p.isFinal()) {
                TLorentzVector pi; pi.SetPxPyPzE(p.px(), p.py(), p.pz(), p.e());
                pions.push_back(pi);
            }
        }

        if (muons.size() < 2) continue;
        std::sort(muons.begin(), muons.end(), [](const TLorentzVector& a, const TLorentzVector& b) {
            return a.Pt() > b.Pt();
        });
        TLorentzVector mu1 = muons[0], mu2 = muons[1];
        if (!passesTrigger(mu1, mu2)) continue;
        triggeredEvents++;

        smearMuon(mu1, rng);
        smearMuon(mu2, rng);

        if (mu1.Pt() < 30 || mu2.Pt() < 30) continue;
        ptPassed++;

        if (!isIsolated(mu1, pions) || !isIsolated(mu2, pions)) continue;
        isoPassed++;

        mu1_pt = mu1.Pt(); mu2_pt = mu2.Pt();
        mass = (mu1 + mu2).M();

        tree->Fill();
        hist->Fill(mass);
    }

    // tree->Write();
    // hist->Write();
    // file->Close();
    // Write tree, histogram, and metadata
    tree->Write();
    hist->Write();
    double sigma_fb = pythia.info.sigmaGen() * 1e12;
    TNamed sigma("cross_section", std::to_string(sigma_fb).c_str());
    TNamed ngen("n_generated", std::to_string(totalEvents).c_str());
    sigma.Write();
    ngen.Write();
    file->Close();

    std::cout << "Total events: " << totalEvents << std::endl;
    std::cout << "Triggered events: " << triggeredEvents << std::endl;
    std::cout << "pT > 30 GeV passed: " << ptPassed << std::endl;
    std::cout << "Isolation passed: " << isoPassed << std::endl;
    std::cout << "Trigger efficiency: " << (float)triggeredEvents / totalEvents << std::endl;
    std::cout << "Cross section: " << sigma_fb << " fb" << std::endl;

    return 0;
}

#include "Pythia8/Pythia.h"
#include <fstream>
using namespace Pythia8;

// This is a file for simulating minimum bias events, from which
// we extract the pT and eta of each muon event

// Compile using make mymain12, run using ./mymain12 afterwards

int main() {
    int N_EVENTS = 100000;
    std::ofstream transverse_momentun_file("pT.dat");
    std::ofstream pseudorapidity_file("eta.dat");

    Pythia pythia;

    pythia.readFile("mymain12.cmnd");

    if (!pythia.init()) return 1;

    for (int iEvent = 0; iEvent < N_EVENTS; iEvent++) {
        if (!pythia.next()) continue;

        if (iEvent % 1000 == 1) {
            std::cout << "Simulating event number " << iEvent << " of " << N_EVENTS << std::endl;
        }

        for (int i = 0; i < pythia.event.size(); i++) {
            if (pythia.event[i].id() == 13) {
                double pT_muon = pythia.event[i].pT();
                double eta_muon = pythia.event[i].eta();
                transverse_momentun_file << pT_muon << "\n";
                pseudorapidity_file << eta_muon << "\n";
            }
        }
    }

    transverse_momentun_file.close();
    pseudorapidity_file.close();
    return 0;

}
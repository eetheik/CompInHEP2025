#include "Pythia8/Pythia.h"
#include <fstream>
using namespace Pythia8;

// This is the file for creating the data for exercise 2
// Compile using make mymain11, run using ./mymain11 afterwards

int main() {
    std::ofstream output_file("higgs_masses.dat");

    Pythia pythia;
    
    pythia.readFile("mymain11.cmnd");

    if (!pythia.init()) return 1;

    for (int n_event = 0; n_event < 1000; n_event++) {
        if (!pythia.next()) continue;

        if (n_event % 100 == 99) {
            std::cout << "Simulating event number " << n_event << " of 1000" << std::endl;
        }

        for (int i = 0; i < pythia.event.size(); i++) {
            if (pythia.event[i].id() == 25) {
                // For simulating just 1000 events I am quite surprised the 
                double higgs_mass = pythia.event[i].m();
                output_file << higgs_mass << "\n";
                break;
            }
        }
    }
    output_file.close();
    return 0;
}
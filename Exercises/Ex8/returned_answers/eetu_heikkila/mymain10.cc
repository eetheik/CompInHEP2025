#include "Pythia8/Pythia.h"
using namespace Pythia8;

// This file calculates the total width for the Higgs at m_H = 125 GeV (exercise 1)
// Compile using make mymain10, run using ./mymain10 afterwards

int main() {
    Pythia pythia;

    pythia.readFile("mymain10.cmnd");

    if (!pythia.init()) return 1;

    double higgs_mass = 125.0;
    pythia.particleData.m0(25, higgs_mass);

    double width = pythia.particleData.mWidth(25);

    printf("SM Higgs Width with m_H = 125 GeV: %.6f\n", width);
    // std::cout << "Mass = " << higgs_mass << ", Width = " << width << std::endl;

    return 0;
}

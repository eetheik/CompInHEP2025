#include <iostream>
#include "MET.h"

int main() {
    MET met(1.0, 2.0);

    std::cout << "MET: " << met.get_met() << std::endl;
    std::cout << "met_x: " << met.get_met_x() << std::endl;
    std::cout << "met_y: " << met.get_met_y() << std::endl;
    std::cout << "phi: " << met.get_phi() << std::endl;

    return 0;
}
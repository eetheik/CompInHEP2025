#ifndef MISSINGET_H
#define MISSINGET_H

#include <cmath>

class MET {
    private:
        // Hide the data
        double met_x;
        double met_y;
    
    public:
        // Constructor
        MET(double x = 0.0, double y = 0.0) {
            met_x = x;
            met_y = y;
        }

        // Getters are obviously public
        double get_met() const {
            return std::sqrt(std::pow(met_x, 2) + std::pow(met_y, 2));
        }

        double get_met_x() const {
            return met_x;
        }

        double get_met_y() const {
            return met_y;
        }

        double get_phi() const {
            // atan2 uses signs of arguments to determine correct angle
            return std::atan2(met_y, met_x); 
        }
};

#endif 
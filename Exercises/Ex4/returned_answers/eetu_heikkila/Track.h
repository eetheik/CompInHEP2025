#ifndef Track_h
#define Track_h

#include <cmath>

class Track {
    private: 
        double track_p_0;
        double track_p_x;
        double track_p_y;
        double track_p_z;

    public:
        // Constructor using initializer list
        Track(double p_0 = 0.0, double p_x = 0.0, double p_y = 0.0, double p_z = 0.0) :
        track_p_0(p_0),
        track_p_x(p_x),
        track_p_y(p_y),
        track_p_z(p_z) {}

        // Getters
        double get_pt() const {
            return std::sqrt(track_p_x*track_p_x + track_p_y*track_p_y);
        }

        double get_eta() const {
            double theta = std::acos(track_p_z / (std::sqrt(track_p_x*track_p_x + track_p_y*track_p_y + track_p_z*track_p_z)));
            return -std::log(std::tan(theta / 2.0));
        }

};


#endif 
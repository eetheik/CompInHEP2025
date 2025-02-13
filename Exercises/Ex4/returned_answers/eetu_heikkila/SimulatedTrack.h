#ifndef SimulatedTrack_h
#define SimulatedTrack_h

#include "Track.h"

class SimulatedTrack : public Track {
    private:
        int particle_id;
        int parent_particle_id;

    public:
        // Constructor
        SimulatedTrack(double p_0 = 0.0, double p_x = 0.0, double p_y = 0.0, double p_z = 0.0, int pid = -1, int ppid = -1) : 
        Track(p_0, p_x, p_y, p_z), 
        particle_id(pid), 
        parent_particle_id(ppid) {}

        // Getters
        int get_particle_id() const {
            return particle_id;
        }

        int get_parent_particle_id() const {
            return parent_particle_id;
        }

};


#endif
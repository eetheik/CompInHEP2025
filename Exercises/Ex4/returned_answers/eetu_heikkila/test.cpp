#include <iostream>
#include "Track.h"
#include "SimulatedTrack.h"

int main() {
    Track track(1.0, 2.0, 3.0, 4.0);
    SimulatedTrack sim_track(1.0, 2.0, 3.0, 4.0, 5, 6);

    std::cout << "track p_T " << track.get_pt() << std::endl;
    std::cout << "track eta " << track.get_eta() << std::endl;
    std::cout << "sim_track p_T " << sim_track.get_pt() << std::endl;
    std::cout << "sim_track eta " << sim_track.get_eta() << std::endl;
    std::cout << "sim_track particle_id " << sim_track.get_particle_id() << std::endl;
    std::cout << "sim_track parent_particle_id " << sim_track.get_parent_particle_id() << std::endl;

    return 0;
}
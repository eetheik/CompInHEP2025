### Quick comment
The `mymain12.cc` is the file doing the PYTHIA8 simulations. It generates two files: 

1) `eta.dat` for the pseudorapidity of minimum biased muons,
2) `pT.dat` for the transverse momenta of minimum biased muons.

These are picked out from 100 000 simulated events. You can change the number of simulated events in the `mymain12.cc` file using the `N_EVENTS` parameter. On my computer this runs for like half a minute, which is quite annoying to wait for. The `PLOT_muon_data.cxx` file uses ROOT to plot the histograms from these files and calculate the number of muons satisfying the "cuts" corresponding to exercise 2. This value is around 0.4%. 

The `make` command will compile the `mymain12.cc`, run the simulation, create the .dat files, plot them and calculate the probability of the muons being detected under the given detector setup.

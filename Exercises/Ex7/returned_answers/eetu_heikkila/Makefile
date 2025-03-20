# If the FeynHiggs part doesn't compile you should edit the path to FeynHiggs in
# generate_FEYNHIGGS_higgs_mass_vs_width.py

EXEC = plot_HDECAY_higgs_mass_vs_width generate_FEYNHIGGS_higgs_mass_vs_width plot_higgs_mass_vs_width

all: $(EXEC)

plot_HDECAY_higgs_mass_vs_width: plot_HDECAY_higgs_mass_vs_width.cxx
	root -l -q -e ".L plot_HDECAY_higgs_mass_vs_width.cxx" -e "plot_HDECAY_higgs_mass_vs_width();"

generate_FEYNHIGGS_higgs_mass_vs_width: generate_FEYNHIGGS_higgs_mass_vs_width.py
	python3 generate_FEYNHIGGS_higgs_mass_vs_width.py

plot_higgs_mass_vs_width: plot_higgs_mass_vs_width.cxx
	root -l -q -e ".L plot_higgs_mass_vs_width.cxx" -e "plot_higgs_mass_vs_width();"

clean:
	rm demo FEYNHIGGS_higgs_mass_vs_width.dat FEYNHIGGS_simulation_result_raw.dat *.png






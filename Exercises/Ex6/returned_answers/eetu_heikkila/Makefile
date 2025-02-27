ROOTCFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
CXX ?= g++
CXXFLAGS = -Wall -O2 $(ROOTCFLAGS)
MACROS := tree_macro histogram_macro
PYTHON = python3
ROOT_SETUP = $(shell root-config --prefix)/bin/thisroot.sh

all: $(MACROS) run_all

tree_macro: tree_macro.cpp
	$(CXX) $(CXXFLAGS) tree_macro.cpp -o tree_macro $(ROOTLIBS)

histogram_macro: histogram_macro.cpp
	$(CXX) $(CXXFLAGS) histogram_macro.cpp -o histogram_macro $(ROOTLIBS)

run_all: tree_macro histogram_macro
	./tree_macro
	./histogram_macro

run_python: tree_macro.py histogram_macro.py
	$(PYTHON) tree_macro.py
	$(PYTHON) histogram_macro.py

clean:
	rm -f $(MACROS) *.png

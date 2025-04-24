Example: https://root.cern/doc/master/h1analysis_8C.html

You can find the code from $ROOTSYS/tutorials/tree

First make the selector skeleton with 
yourTree->MakeSelector("your-analysis-name")

Compiled TSelector:

mv MyAnalysis.C MyAnalysis.cc # just for needing to check only .cc files in the Makefile

Then start writing code to member functions
your-analysis-name::Begin
your-analysis-name::Process
your-analysis-name::Terminate

Usage:
make
main.py

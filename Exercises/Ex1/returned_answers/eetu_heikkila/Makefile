MAIN = Feynman_and_Bib
BIB = bibliography
MP_FILES = diagram1.mp diagram2.mp
PDF = $(MAIN).pdf

all: $(PDF)

$(PDF): $(MAIN).tex $(BIB).bib 
	pdflatex $(MAIN).tex
	biber $(MAIN)
	mpost diagram1.mp
	mpost diagram2.mp
	pdflatex $(MAIN).tex
	pdflatex $(MAIN).tex

%.1: %.mp
	mpost $<

clean:
	rm -f $(MAIN).aux $(MAIN).blg $(MAIN).bcf $(MAIN).bbl $(MAIN).log $(MAIN).run.xml \
		$(MP_FILES:.mp=.1) $(MP_FILES:.mp=.t1) $(MP_FILES:.mp=.log) $(MAIN).pdf $(MP_FILES)

all: tree_macro histogram_macro

tree_macro:
	root -l -q -e ".L script_ex1.C" -e "tree_macro();"

histogram_macro:
	root -l -q -e ".L script_ex2.C" -e "histogram_macro();"

clean:
	rm -f "tree.root" "histogram.png"
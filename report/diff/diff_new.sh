#!/bin/sh
latexdiff  ../Text.tex new.tex > diff.tex
pdflatex diffmain.tex
open diffmain.pdf

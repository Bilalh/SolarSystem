#!/bin/sh
latexdiff old.tex ../Text.tex > diff.tex
pdflatex diffmain.tex
open diffmain.pdf

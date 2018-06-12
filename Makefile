all: main.pdf defence.pdf

main.pdf: main.tex *.tex *.bib images/*
	pdflatex main
	bibtex main
	pdflatex main
	pdflatex main

defence.pdf: defence.tex
	pdflatex defence

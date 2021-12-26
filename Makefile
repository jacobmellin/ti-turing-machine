cc = gcc -Wall
ti_turing: ti_turing.c ti_turing_band.c ti_turing_control.c ti_turing_parser.c ti_turing_graphviz.c
	$(cc) -o ti_turing ti_turing.c ti_turing_band.c ti_turing_control.c ti_turing_parser.c ti_turing_graphviz.c -I. -lcgraph -lgvc
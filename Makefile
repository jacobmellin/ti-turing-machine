cc = gcc
ti_turing: ti_turing.c ti_turing_band.c ti_turing_control.c ti_turing_parser.c
	$(cc) -o ti_turing ti_turing.c ti_turing_band.c ti_turing_control.c ti_turing_parser.c -I.
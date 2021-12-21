cc = gcc
ti_turing: ti_turing.c ti_turing_band.c
	$(cc) -o ti_turing ti_turing.c ti_turing_band.c -I.
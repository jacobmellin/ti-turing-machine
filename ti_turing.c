#include <stdlib.h>
#include <stdio.h>

#include "ti_turing_band.h"

int main() {
    printf("TI Deterministic Turing Machine Implementation\n");

    band_t * band = make_band();

    int data[] = {0,1,1,2,0,1};
    arr_to_band(band, data, 6);

    print_band(band);
}
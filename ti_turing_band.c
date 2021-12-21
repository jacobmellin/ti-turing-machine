#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ti_turing_band.h"

void arr_to_band(band_t * band, int input[], int len) {
    symbol_t * first = band->head;

    for (int i = 0; i < len; i++) {
        update_band(band, input[i], DIR_RIGHT);
    }

    band->head = first;
}

symbol_t * make_symbol(symbol_t * left_of, symbol_t * right_of) {
    symbol_t* symbol = (symbol_t *) malloc(sizeof(symbol_t));
    symbol->val = BLANK;
    symbol->left = right_of;
    symbol->right = left_of;
    return symbol;
}

struct band* make_band() {
    symbol_t * head = 0;
    head = (symbol_t *) malloc(sizeof(symbol_t));

    head->val = BLANK;
    head->right = 0;
    head->left = 0;

    band_t * band = 0;;
    band = (band_t *) malloc(sizeof(band_t));

    band->head = head;
    return band;
}

int check_band(band_t *band, int val) {
    return band->head->val == val;
}

void update_band(band_t *band, int val, int dir) {
    symbol_t * next_symbol;

    if (dir == DIR_LEFT) {
        if(!band->head->left) {
            band->head->left = make_symbol(band->head, 0);
        }
        next_symbol = band->head->left;
    } else if (dir == DIR_RIGHT) {
        if(!band->head->right) {
            band->head->right = make_symbol(0, band->head);
        }
        next_symbol = band->head->right;
    }

    band->head->val = val;
    band->head = next_symbol;
}

void print_band(band_t *band) {
    symbol_t * current = band->head;

    // Got to beginning of band
    while(current->left) {
        current = current->left;
    }

    // Print each symbol on the band, replacing BLANK with _
    while(current) {
        char symbol_output = current->val + 0;

        if(symbol_output == BLANK) {
            symbol_output = '_';
        } else {
            symbol_output += 48;
        }

        printf("%c", symbol_output);
        // printf("%d", current->val);
        current = current->right;
    }

    printf("\n");
}
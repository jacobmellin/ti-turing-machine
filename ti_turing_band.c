#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ti_turing_band.h"

void arr_to_band(band_t * band, int input[], int len) {
    cell_t * first = band->head;

    for (int i = 0; i < len; i++) {
        update_band(band, input[i], DIR_RIGHT);
    }

    band->head = first;
}

void string_to_band(band_t * band, char* input) {
    cell_t * first = band->head;
    for (int i = 0; i < strlen(input); i++) {
        update_band(band, input[i] - '0', DIR_RIGHT);
    }
    band->head = first;
}

cell_t * make_cell(cell_t * left_of, cell_t * right_of) {
    cell_t* cell = (cell_t *) malloc(sizeof(cell_t));
    cell->val = BLANK;
    cell->left = right_of;
    cell->right = left_of;
    return cell;
}

struct band* make_band() {
    cell_t * head = 0;
    head = (cell_t *) malloc(sizeof(cell_t));

    head->val = BLANK;
    head->right = 0;
    head->left = 0;

    band_t * band = 0;
    band = (band_t *) malloc(sizeof(band_t));

    band->head = head;
    return band;
}

int check_band(band_t *band, int val) {
    return band->head->val == val;
}

void update_band(band_t *band, int val, int dir) {
    cell_t * next_cell = band->head;

    if (dir == DIR_LEFT) {
        if(!band->head->left) {
            band->head->left = make_cell(band->head, 0);
        }
        next_cell = band->head->left;
    } else if (dir == DIR_RIGHT) {
        if(!band->head->right) {
            band->head->right = make_cell(0, band->head);
        }
        next_cell = band->head->right;
    }

    band->head->val = val;
    band->head = next_cell;
}

void print_band(band_t *band, int clean) {
    cell_t * current = band->head;

    // Go to beginning of band
    while(current->left) {
        current = current->left;
    }

    // Print each symbol on the band, replacing BLANK with _
    while(current) {
        char cell_output = current->val + 0;

        if(cell_output == BLANK) {
            cell_output = '_';
        } else {
            cell_output += 48;
        }

        if(!clean || cell_output != '_')
            printf("%c", cell_output);
        // printf("%d", current->val);
        current = current->right;
    }

    printf("\n");
}

void free_band(band_t * band) {
    // TODO
};
#pragma once

// A blank symbol on the band is represented by a value of 2
#define BLANK 2

// Definitions of head movement direction aliases
#define DIR_LEFT 0
#define DIR_RIGHT 1
#define DIR_NEUTRAL 2

typedef struct cell {
    int val;
    struct cell *right;
    struct cell *left;
} cell_t;

typedef struct band {
    struct cell *head;
} band_t;

struct band* make_band();
void free_band(band_t * band);
void arr_to_band(band_t * band, int input[], int len);
void string_to_band(band_t * band, char* input);
int check_band(band_t *band, int val);
void update_band(band_t *band, int val, int dir);
void print_band(band_t *band);
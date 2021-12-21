// A blank symbol on the band is represented by a value of 2
#define BLANK 2

// Definitions of head movement direction aliases
#define DIR_LEFT 0
#define DIR_RIGHT 1
#define DIR_NEUTRAL 2

typedef struct symbol {
    int val;
    struct symbol *right;
    struct symbol *left;
} symbol_t;

typedef struct band {
    struct symbol *head;
} band_t;

struct band* make_band();
void arr_to_band(band_t * band, int input[], int len);
int check_band(band_t *band, int val);
void update_band(band_t *band, int val, int dir);
void print_band(band_t *band);
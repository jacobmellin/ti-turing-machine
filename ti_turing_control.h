#include <stdlib.h>

#include "ti_turing_band.h"

typedef struct int_array {
    int size;
    int * data;
} int_array_t;

int_array_t * make_int_arr(size_t size);
int int_arr_get(int_array_t * int_arr, int index);
void int_arr_set(int_array_t * int_arr, int index, int value);
int int_arr_get_index(int_array_t * int_arr, int value);

typedef struct transition {
    int state;
    int symbol_condition;
    int state_target;
    int symbol_new;
    int dir;
    int active;
} transition_t;

typedef struct machine {
    int num_states;
    int num_accepting_states;
    int starting_state;
    int current_state;

    band_t * band;

    int_array_t * accepting_states;
    transition_t * transitions;
} machine_t;

machine_t * make_machine(
    int num_states,
    int num_accepting_states,
    int starting_state
    );

void machine_set_transition(
        machine_t * machine,
        int state,
        int condition,
        int target,
        int symbol_new,
        int dir
        );

void machine_set_accepting_state(
    machine_t * machine,
    int index, 
    int state
    );

int machine_step(machine_t * machine);

int machine_evaluate(machine_t * machine, char * input);
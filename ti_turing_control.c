#include <stdlib.h>
#include <stdio.h>

#include "ti_turing_control.h"
#include "ti_turing_band.h"

#define MAX_STEPS 10000

int_array_t * make_int_arr(size_t size) {
    int_array_t * int_arr = (int_array_t*) malloc(sizeof(int_array_t));
    int_arr->data = malloc(sizeof(int)*size);
    int_arr->size = size;
    return int_arr;
}

int int_arr_get(int_array_t * int_arr, int index) {
    return *(int_arr->data + index);
}

void int_arr_set(int_array_t * int_arr, int index, int value) {
    // printf("int_arr_set");
    *(int_arr->data + index) = value;
}

int int_arr_get_index(int_array_t * int_arr, int value) {
    for(int i = 0; i < int_arr->size; i++) {
        if(int_arr_get(int_arr, i) == value) {
            return i;
        }
    }
    return -1;
}

machine_t * make_machine(
    int num_states, int num_accepting_states, int starting_state) {
        machine_t * machine = (machine_t *) malloc(sizeof(machine_t));
        machine->num_states = num_states;
        machine->num_accepting_states = num_accepting_states;
        machine->starting_state = starting_state;

        machine->accepting_states = make_int_arr(num_accepting_states);

        // Make 3 transitions for each state, so we can implicitly
        // get the right transition for a specific symbol.
        machine->transitions = (transition_t*) malloc(sizeof(transition_t) * num_states * 3);
        return machine;
};

void machine_set_transition(
    machine_t * machine,
    int state,
    int condition,
    int target,
    int symbol_new,
    int dir) {
        *(machine->transitions + (state * 3) + condition) = (transition_t) {
            .state = state,
            .symbol_condition = condition,
            .state_target = target,
            .symbol_new = symbol_new,
            .dir = dir,
            .active = 1
        };
    };

void machine_set_accepting_state(
    machine_t * machine,
    int index,
    int state) {
        int_arr_set(machine->accepting_states, index, state);
    };

int machine_step(machine_t * machine) {
    transition_t * transition
        = (machine->transitions + (machine->current_state * 3) 
            + machine->band->head->val);
    
    // printf("-> current state: %d, cell value: %d, transition_index: %d\n", 
    //     machine->current_state, 
    //     machine->band->head->val,
    //     (machine->current_state * 3) + machine->band->head->val);
    
    if(transition->active) {
        update_band(machine->band, transition->symbol_new, transition->dir);
        machine->current_state = transition->state_target;
        // printf("replaced cell value: %d, new state: %d\n", transition->symbol_new, machine->current_state);
        return 1;
    }

    return 0;
}

int machine_evaluate(machine_t * machine, char * input, int max_steps) {
    machine->current_state = 0;
    machine->band = make_band();

    string_to_band(machine->band, input);

    printf("Input:  ");
    print_band(machine->band);


    if(!max_steps) max_steps = MAX_STEPS;
    int steps = 0;

    while(machine_step(machine)) {
        ++steps;
        if (steps >= max_steps) {
            printf("Stopped execution after %d steps.\n", max_steps);
            break;
        }
    };

    printf("Output: ");
    print_band(machine->band);
    
    if(steps < MAX_STEPS) printf("%d steps before halt.\n", steps);

    return int_arr_get_index(
        machine->accepting_states, 
        machine->current_state) > -1;
}
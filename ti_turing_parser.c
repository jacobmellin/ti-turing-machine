#include <string.h>
#include <stdio.h>
#include "ti_turing_parser.h"

void parse_machine(machine_t * machine, char * input, char ** word) {
    int num_states = 0;
    int num_band_symbols = 0;
    int num_accepting_states = 0;
    int starting_state = 0;

    int ones = 0;
    int delim_pos = 0;
    int current_pos = 0;

    // Read states, number of band symbols, number  of accepting states
    for (; ones < 3; current_pos++) {
        int v = input[current_pos] - '0';
        if(v == 1) {
            ++ones;
        } else if(v == 0) {
            switch (ones) {
                case 0:
                    ++num_states;
                    break;
                case 1:
                    ++num_band_symbols;
                    break;
                case 2:
                    ++num_accepting_states;
                default:
                    break;
            }
        }
    }

    machine = make_machine(num_states, num_accepting_states, starting_state);

    printf("Number of states: %d\n", num_states);
    printf("Number of band symbols: %d\n", num_band_symbols);
    printf("Number of accepting states: %d\n", num_accepting_states);

    // Read accepting states
    printf("Accepting states (zero based): ");
    int current_accepting = 0;
    while(ones-3 < num_accepting_states) {
        int v = input[current_pos] - '0';

        if(v == 0) {
            ++current_accepting;
        } else if(v == 1) {
            ++ones;
            machine_set_accepting_state(machine, ones-3, current_accepting-1);
            printf("%d, ", current_accepting-1);
            current_accepting = 0;
        }

        ++current_pos;
    }

    printf("\n");
    // printf("ones: %d, current: %c\n", ones, input[current_pos]);

    // Read transitions    
    int current_condition_state = 0;
    int current_condition_symbol = 0;
    int current_target_state = 0;
    int current_target_symbol = 0;
    int current_direction = 0;
    while(input[current_pos] != '#' && input[current_pos] != '\0') {
        int v = input[current_pos] - '0';

        if(v == 0) {
            switch ((ones-3-num_accepting_states) % 5) {
                case 0:
                    ++current_condition_state;
                    break;
                case 1:
                    ++current_condition_symbol;
                    break;
                case 2:
                    ++current_target_state;
                    break;
                case 3:
                    ++current_target_symbol;
                    break;
                case 4:
                    ++current_direction;
                    break;
                default:
                    break;
            }
        } else if (v == 1) {
            ones++;
            
            if((ones-3-num_accepting_states) % 5 == 0) {
                machine_set_transition(
                    machine,
                    current_condition_state-1,
                    current_condition_symbol-1,
                    current_target_state-1,
                    current_target_symbol-1,
                    current_direction-1
                );

                printf("Transition: delta(%d, %d) = (%d, %d, %d)\n",
                    current_condition_state-1,
                    current_condition_symbol-1,
                    current_target_state-1,
                    current_target_symbol-1,
                    current_direction-1
                );

                current_condition_state = 0;
                current_condition_symbol = 0;
                current_target_state = 0;
                current_target_symbol = 0;
                current_direction = 0;
            }
        }

        ++current_pos;
    }

    if(input[current_pos] == '\0') {
        printf("No input word!\n");
    }

    *word = (input + current_pos+1);
};
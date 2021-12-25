/* *
 * TI Deterministic Turing Machine Implementation
 * Jacob Mellin, 675891
 * */

#include <stdlib.h>
#include <stdio.h>

#include "ti_turing_band.h"
#include "ti_turing_control.h"
#include "ti_turing_parser.h"

int main(int argc, char *argv[]) {
    printf("TI Deterministic Turing Machine Implementation\n");

    // machine_t * machine = make_machine(3,1,0);

    // machine_set_accepting_state(machine, 0, 2);
    // machine_set_transition(machine, 0, 1,     1, 1,     DIR_RIGHT);
    // machine_set_transition(machine, 1, BLANK, 2, BLANK, DIR_RIGHT);
    // machine_set_transition(machine, 1, 0,     0, 0,     DIR_RIGHT);

    // char * input = argv[1];

    // int result = machine_evaluate(machine, input);

    char * input = argv[1];
    char * word;
    machine_t * machine;

    parse_machine(&machine, input, &word);
    int result = machine_evaluate(machine, word);

    printf("%d\n", result);
}
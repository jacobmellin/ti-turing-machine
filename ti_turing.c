/* *
 * TI Deterministic Turing Machine Implementation
 * Jacob Mellin, 675891
 * */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ti_turing_band.h"
#include "ti_turing_control.h"
#include "ti_turing_parser.h"
#include "ti_turing_graphviz.h"

int main(int argc, char *argv[]) {
    printf("TI Deterministic Turing Machine Implementation\n");

    int max_steps = 0;

    for (int i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-') {
            if(argv[i][1] == 't') {
                if(strlen(argv[i]+2)> 0) {
                    max_steps = atoi(argv[i]+2);
                } else {
                    max_steps = atoi(argv[i+1]);
                    i++;
                }
                if(max_steps != 0) {
                    printf("Set max steps to %d.\n", max_steps);
                }
            }
        } else {
            char * input = argv[i];
            char * word;
            machine_t * machine;

            parse_machine(&machine, input, &word);
            int result = machine_evaluate(machine, word, max_steps);

            printf("%d\n", result);

            graphviz_draw(machine, "machine.svg");
        }
    }
}
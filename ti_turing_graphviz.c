#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include "ti_turing_graphviz.h"
#include "ti_turing_control.h"
#include "util.h"

void graphviz_draw(machine_t * machine, char* filename) {
    Agraph_t* graph = agopen("dtm", Agdirected, 0);
    GVC_t* gvc = gvContext();

    // Style settings
    agattr(graph, AGNODE, "shape", "circle");
    agattr(graph, AGNODE, "fontname", "serif");
    agattr(graph, AGEDGE, "arrowhead", "open");
    agattr(graph, AGEDGE, "arrowsize", "0.5");
    agattr(graph, AGEDGE, "fontsize", "12");
    agattr(graph, AGRAPH, "rankdir", "LR"); // Prefer left to right placement of nodes

    // Draw nodes
    for (size_t i = 0; i < machine->num_states; i++)
    {
        char n[3];
        itoa(i, n, 10);
        Agnode_t * node = agnode(graph, n , 1);

        if(int_arr_get_index(machine->accepting_states, i) > -1) {
            agsafeset(node, "shape", "doublecircle", "");
        }
    }

    // Draw edges
    for(size_t i = 0; i < machine->num_states*3; i++) {
        transition_t * t = (machine->transitions+i);

        if(!t->active) continue;

        char n[3];
        itoa(t->state, n, 10);

        char m[3];
        itoa(t->state_target, m, 10);

        Agedge_t * edge = agedge(graph,
            agnode(graph, n, 0),
            agnode(graph, m, 0),
            "", 1);

        char * arr_right = "▷";
        char * arr_left = "◁";
        char * neutral = "◻︎";
        char * blank = "⎵";

        char edge_label[50];

        char * from = "?";
        if(t->symbol_condition == 2) {
            from = blank;
        } else {
            from = (t->symbol_condition == 1 ? "1" : "0");
        }

        char * to = "?";
        if(t->symbol_new == 2) {
            to = blank;
        } else {
            to = (t->symbol_new == 1 ? "1" : "0");
        }

        char * dir = "?";
        if(t->dir == 0) {
            dir = arr_left;
        } else if(t->dir == 1) {
            dir = arr_right;
        } else if(t->dir == 2) {
            dir = neutral;
        }

        snprintf(edge_label, 40, "%s / %s / %s", from, to, dir);
        agsafeset(edge, "label", edge_label, "");
    }

    char * format = "pdf";

    // Lay out and render
    gvLayout (gvc, graph, "dot");
    gvRenderFilename (gvc, graph, format, filename);
    
}
#include "graphs/graph.h"
#include <stdio.h>


int main (void)
{
    RCGraph * gc;
    initRCGraph( .graph_ptr = &gc,
                //  .name = "RandomUserCategories",
                 .vertices_count = 3
    );


    printf("Graph: %s \nGraph vertices count: %d\n", 
            gc->name, gc->vertices_count);

    return 0;
}
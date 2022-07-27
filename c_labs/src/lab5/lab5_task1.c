#include "graphs/graph.h"
#include <stdio.h>


int main (void)
{
    RCGraph * gc;
    initRCGraph( .graph_ptr = &gc,
                //  .name = "Categories",
                 .vertices_count = 3
    );


    printf("%s %d", gc->name, gc->vertices_count);

    return 0;
}
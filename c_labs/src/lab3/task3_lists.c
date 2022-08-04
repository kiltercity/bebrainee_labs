// #include "lists.h"



int main (void)
{
    // List_t * l = createList();
    List_t * list = malloc ( sizeof (List_t) );

    list->get = (node_t* (*)(void*)) __bind__(list, __get__);

    return 0;
}
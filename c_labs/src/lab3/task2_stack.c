#include "stack.h"


int main(void)
{
    // Initialization of two nodes and one Stack
    // """""""""""""""""""""""""""""""""""""
    Stack_t * stack = newStack();
    node_t * node1 = malloc( sizeof (node_t) );
    node_t * node2 = malloc( sizeof (node_t) );

    // Sample data
    // """""""""""""""""""""""""""""""""""""
    char * str1 = "This is first pushed to stack item (1)";
    char * str2 = "This is second pushed to stack item (2)";
    char * str3 = "This is third pushed to stack item (3)";

    // Assign sample data to nodes
    // """""""""""""""""""""""""""""""""""""
    node1->data = (char*)str1;
    node2->data = (char*)str2;


    printf("-----------------------------------------------\n");


    // Push nodes to stack
    // """""""""""""""""""""""""""""""""""""
    stack->push(stack, node1);
    printf("Pushed 1st item to the stack: %s\n", (char*)node1->data);

    stack->push(stack, node2);
    printf("Pushed 2nd item to the stack: %s\n", (char*)node2->data);

    // This node is created with the help of 
    // the special Stack helper function
    // """""""""""""""""""""""""""""""""""""
    node_t * node3 = stack->new_node( stack, str3, sizeof (str3) );
    printf("Pushed 3d item to the stack: %s\n", (char*)node3->data);


    // **********************************************************

    printf("-----------------------------------------------\n");

    // **********************************************************


    // Pop all the nodes from the stack
    // """""""""""""""""""""""""""""""""""""
    node_t * n1_out = stack->dash(stack);
    node_t * n2_out = stack->dash(stack);
    node_t * n3_out = stack->dash(stack);


    // Print results in the right order the were taken from stack
    // """""""""""""""""""""""""""""""""""""
    printf("This is 1st out: %s\n", (char*)n1_out->data);
    printf("This is 2nd out: %s\n", (char*)n2_out->data);
    printf("This is 3d out: %s\n", (char*)n3_out->data);


    // **********************************************************

    printf("-----------------------------------------------\n");

    // **********************************************************
    // EXPLANATION
    // """""""""""    
    printf(
        "So the stack works by the FIFO printiple.\n"
        "That is First IN is First OUT.\n"
        "As you can see: the program have worked out as it was expected\n"
    );
    printf("-----------------------------------------------\n");
    
    // **********************************************************

    return 0;
}
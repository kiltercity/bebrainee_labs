#ifndef __H_TASK_QUEUE__
#define __H_TASK_QUEUE__

// ===========================================================================

#include <stdlib.h>
#include <stdio.h>


// Stack list node type
// """"""""""""""""""""
struct stack_node
{
    void * data;
    struct stack_node * __prev__;
};
typedef struct stack_node node_t;

// Stack struct type
// """""""""""""""""
struct stack_list
{
    node_t * __first__,
           * __last__;
    node_t * (*push)();
    node_t * (*dash)();
    node_t * (*new_node)();
};
typedef struct stack_list Stack_t;


// Stack functions
// """""""""""""""
node_t * __stack_push__(Stack_t * stack, node_t * node);
node_t * __stack_dash__(Stack_t * stack);
node_t * __new_node__(Stack_t * q, void * data, size_t size);

Stack_t * newStack();


// ===========================================================================

#endif // __H_TASK_QUEUE__
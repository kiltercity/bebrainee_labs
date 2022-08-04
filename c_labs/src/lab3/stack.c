#include "stack.h"

node_t * __stack_push__(Stack_t * stack, node_t * node)
{
    if ( ! stack->__last__ )
    {
        stack->__last__ = node;
        node->__prev__ = 0;
        return node;
    }

    node->__prev__ = stack->__last__;
    stack->__last__ = node;
    return node;
}

node_t * __stack_dash__(Stack_t * stack)
{
    if ( ! stack->__last__ )
        return 0;

    // If no previous in the list
    // set the list last item to 0
    // and return last item that it has before
    // """""""""""""""""""""""""""""""""""""""
    if ( ! stack->__last__->__prev__ )
    {
        node_t * last = stack->__last__;
        stack->__last__ = 0;
        return last;
    }

    // Set last item to previous item in the list
    // and return current last item
    // """"""""""""""""""""""""""""""""""""""""""
    node_t * last = stack->__last__;
    stack->__last__ = last->__prev__;

    return last;
}


// Prepare new Stack node
// """"""""""""""""""""""
node_t * __new_node__(Stack_t * q, void * data, size_t size)
{
    node_t * _new = malloc( sizeof (node_t) );
    
    _new->data = malloc( size );
    _new->__prev__ = malloc ( sizeof (node_t) );
    _new->data = (void *) data;

    return q->push(q, _new);
}



Stack_t * newStack()
{
    Stack_t * stack = malloc( sizeof (Stack_t) );
    stack->push =
                (node_t * (*)(void*, void*)) __stack_push__;
    stack->dash =
                (node_t * (*)(void*, void*)) __stack_dash__;
    stack->new_node = 
                (node_t* (*)(void*, void*, size_t)) __new_node__;

    stack->__first__ = 0;
    stack->__last__ = 0; 
    return stack;
}
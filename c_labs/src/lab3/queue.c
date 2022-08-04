#include "queue.h"

node_t * __queue_push__(Queue_t * queue, node_t * node)
{
    if ( ! queue->__first__ )
    {
        queue->__first__ = node;
        queue->__last__ = node;
        node->__prev__ = 0;
        return node;
    }
    queue->__first__->__prev__ = node;
    queue->__first__ = node;

    return node;
}

node_t * __queue_dash__(Queue_t * queue)
{
    if ( ! queue->__last__ )
        return 0;

    // If this is the last node in list
    node_t * last_node = queue->__last__;

    if ( ! last_node->__prev__ )
    {
        queue->__last__ = 0;
        queue->__first__ = 0;
        return last_node;
    }

    queue->__last__ = last_node->__prev__;

    return last_node;
}


// Prepare new Queue node
// """"""""""""""""""""""
node_t * __new_node__(Queue_t * q, void * data, size_t size)
{
    node_t * _new = malloc( sizeof (node_t) );
    
    _new->data = malloc( size );
    _new->__prev__ = malloc ( sizeof (node_t) );
    _new->data = (void *) data;

    return q->push(q, _new);
}



Queue_t * newQueue()
{
    Queue_t * queue = malloc( sizeof (Queue_t) );
    queue->push =
                (node_t * (*)(void*, void*)) __queue_push__;
    queue->dash =
                (node_t * (*)(void*, void*)) __queue_dash__;
    queue->new_node = 
                (node_t* (*)(void*, void*, size_t)) __new_node__;

    queue->__first__ = 0;
    queue->__last__ = 0; 
    return queue;
}
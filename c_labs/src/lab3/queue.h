#ifndef __H_TASK_QUEUE__
#define __H_TASK_QUEUE__

// ===========================================================================


#include <stdlib.h>
#include <stdio.h>



// Queue list node type
// """"""""""""""""""""
struct queue_node
{
    void * data;
    struct queue_node * __prev__;
};
typedef struct queue_node node_t;

// Queue struct type
// """""""""""""""""
struct queue_list
{
    node_t * __first__,
           * __last__;
    node_t * (*push)();
    node_t * (*dash)();
    node_t * (*new_node)();
};
typedef struct queue_list Queue_t;


// Queue functions
// """""""""""""""
node_t * __queue_push__(Queue_t * queue, node_t * node);
node_t * __queue_dash__(Queue_t * queue);
node_t * __new_node__(Queue_t * q, void * data, size_t size);

Queue_t * newQueue();


// ===========================================================================

#endif // __H_TASK_QUEUE__
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
// ===========================================================================

#include <stdlib.h>



/* STRUCTURES AND TYPEDEFS
 * -------------------------------------------------------------------------*/
typedef unsigned int uint_t;


struct __2d_list_node__
{
    uint_t index;

    void * data;

    node_t * prev;
    node_t * next;

};
typedef struct __2d_list_node__ node_t;


struct __2d_linked_list__
{
    __2d_linked_list__ * self;
    node_t * head;
    node_t * tail;

    node_t * ( * push )();
    void * ( * dash )();

    void * ( * shift   )();
    void * ( * unshift )();

};
typedef struct __2d_linked_list__ List_t;


/* FUNCTION PROTOTYPES
 * -------------------------------------------------------------------------*/

 /* Add node at the end of the list
  * """"""""""""""""""""""""""""""*/
void __list_push ( List_t * l, node_t * node );
/* Get last node from the end of the list
 * """"""""""""""""""""""""""""""""""""""*/
node_t * __list_dash__ ( List_t * l );

/* Add item at the beggining of list 
 * """""""""""""""""""""""""""""""""*/
 void __list_unshift__ ( List_t * l, node_t * node );

/* GET first node from list
 * """"""""""""""""""""""""*/
node_t * __list_shift__ ( List_t * l );

void __list_insertbefore__ ( List_t * l, node_t * node );
void __list_insertaftere__ ( List_T * l, node_t * node );

node_t * __list_getnode__ ( List_t * l , uint_t idx );



/* Create new list
 * """""""""""""""*/
 List_t * createList ();






// ===========================================================================
#endif // __LINKED_LIST_H__
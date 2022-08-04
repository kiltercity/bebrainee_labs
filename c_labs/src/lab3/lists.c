#include "lists.h"


void __list_push__ ( List_t * list, node_t * node )
{
    if ( ! list->tail )
    {
        list->head = node;
        list->tail = node;
        
        return;
    }
    node->prev = 0;
    node->next = 0; 
    node->prev = l->tail;
    l->tail = node;
    node->index = l->count + 1;
}

void __list_unshift__ ( List_t * list, node_t * node)
{
    if ( ! list->head )
    {
        list->head = node;
        list->tail = node;
        return;
    }
    ++list->count;
    list->node->prev = 0;
    list->node->next = 0;
}

node_t * __list_dash__( List_t * list )
{
    if ( ! l->tail )
        return 0;
    --list->count;
    
    // Store list tail temporary util reassigning
    // """"""""""""""""""""""""""""""""""""""""""
    node_t * tmp_tail = list->tail;

    // If there is previous node
    // assign list head this node
    /// """""""""""""""""""""""""
    if ( tmp_tail->prev )
        list->tail = tmp_tail->prev;
    
    return tmp_tail;
}


node_t * __list_shift__ ( List_t * list )
{
    // Do not proceed if the head pointer is invalid
    // """""""""""""""""""""""""""""""""""""""""""""
    if ( ! list->head )
        return 0;
    --list->count;

    // Store list head before replacement
    // """"""""""""""""""""""""""""""""""
    node_t * tmp_head = list->head;

    // Replcae list head pointer with the next node
    // if there is one
    // """"""""""""""""""""""""""""""""""""""""""""
    if ( tmp_head->next )
        list->head = tmp_head->next;

    return tmp_head;
}



List_t * createList()
{
    List_t * list = malloc ( sizeof (List_t) );

    list->self = list;
    list->head = 0;
    list->tail = 0;

    list->push = (void   * (*)(void*)) __list_push__;
    list->push = (node_t * (*)(void*)) __list_dash__;

    list-> = (node_t * (*)(void*)) __list_dash__;


    return list;
}


#include "hashset.h"
#include <stdlib.h>
#include <stdio.h>


bool_t hashadd (HashSet * hs, char data[])
{
    void * has = (void *) hs-> ht->get (hs->ht, data);

    if ( has != 0 )
    {
        // if ( hs->debug )
        //     printf("This item is already in the set: %s\n", data);
        return 1; // error inseritng
    }

    hs-> ht->put (hs->ht, data, data);
    return 0;
}


char * hashget (HashSet * hs, char data[] )
{
    return (char*) hs-> ht-> get ( hs->ht, data );
}



char * __setiter_next__(SetIterator * si)
{
    Node * hitem = 0;
    si->hashiter->next(si->hashiter, &hitem);
    return hitem->name;
}

void __setiter_reset__(SetIterator * st)
{
    st->hashiter->start = 0;
    st->hashiter->end = 0;
    st->hashiter->pos = 0;
    st->hashiter->check_counters(st->hashiter);
}


/* */
SetIterator * createSetIterator (HashSet * hset)
{
    SetIterator * si = malloc ( sizeof ( SetIterator ) );
    HashIter * hit = newHashIter(&hset->ht, -1, -1);
    
    si->hashiter = hit;
    si->current = malloc ( sizeof (Node) );
    si->next = __setiter_next__;
    si->reset = __setiter_reset__;

    
    return si;
}


HashSet * newHashSet (int size)
{
    HashSet * hs = malloc ( sizeof (HashSet) );
    hs->ht = newHash(size);

    hs->add = (bool_t (*)(HashSet *, char[])) hashadd;
    hs->get = (char * (*)(HashSet *, char[])) hashget;

    SetIterator * si = createSetIterator(hs);
    hs->setiter = 0;


    return hs;
}

void dropHashSet (HashSet * hs)
{
    dropHashTable ( hs->ht );
}
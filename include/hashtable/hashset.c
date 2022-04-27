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


HashSet * newHashSet (int size)
{
    HashSet * hs = malloc ( sizeof (HashSet) );
    hs->ht = newHash(size);

    hs->add = (bool_t (*)(HashSet *, char[])) hashadd;
    hs->get = (char * (*)(HashSet *, char[])) hashget;



    return hs;
}

void dropHashSet (HashSet * hs)
{
    dropHashTable ( hs->ht );
}
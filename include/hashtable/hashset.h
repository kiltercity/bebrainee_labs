#ifndef __HASHSET_H1N1__
#define __HASHSET_H1N1__
// ---------------------------------------------------------------------------

    #include "hashtable.h"


    typedef struct hashset
    {
        HashTable * ht;


        bool_t (*add)(struct hashset *, char[] );
        char * (*get)(struct hashset *, char[] );

    } HashSet;

    HashSet * newHashSet(int size);
    void dropHashSet(HashSet *);



// ---------------------------------------------------------------------------
#endif //__HASHSET_H1N1__
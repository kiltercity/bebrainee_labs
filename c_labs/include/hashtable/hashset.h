#ifndef __HASHSET_H1N1__
#define __HASHSET_H1N1__
// ---------------------------------------------------------------------------

    #include "hashtable.h"

    // Forward declarations
    // -
    typedef struct hashset HashSet;
    typedef struct __set_iterator__ SetIterator;

    struct hashset
    {
        HashTable * ht;

        SetIterator * setiter;
        bool_t (*add)(struct hashset *, char[] );
        char * (*get)(struct hashset *, char[] );

    };


    struct __set_iterator__ 
    {
        char * (*next)();
        void (*reset)();

        Node * current;
        HashIter * hashiter;
    };
    SetIterator * createSetIterator(HashSet *);

    HashSet * newHashSet(int size);
    void dropHashSet(HashSet *);


// ---------------------------------------------------------------------------
#endif //__HASHSET_H1N1__
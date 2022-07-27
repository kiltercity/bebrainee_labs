#ifndef __HASHLIST_1__H__
#define __HASHLIST_1__H__
// ===========================================================================


    // Alias for unsigned char
    typedef unsigned char uchar_t; // cause of ASS CI
    typedef int bool_t; // int takes 4 bytes, char takes 1 
    typedef unsigned int uint_t; //un SING ed int

    // Prime numbers are good

    // Table's node
    typedef struct node
    {
        char name[256];
        void * data;
        struct node * next;
    } Node;

    // Hash table
    typedef struct hashtable
    {
        Node ** table;
        uint_t size;


        uint_t __salt_a;
        uint_t __salt_b;
        
        void (*put) (struct hashtable * ht, char * key, void * data);
        void * (*get) (struct hashtable * ht, char * key);
        void (*rem) (struct hashtable * ht, char * key );
    } HashTable;
    

    typedef struct htiter
    {
        int pos;
        uint_t start;
        uint_t end;
        Node * lastnode_ptr;

        void (*check_counters)(struct hiter*);
        HashTable ** ht;
        bool_t (*next)(struct htiter*, Node ** );
    } HashIter;

    HashIter * newHashIter(HashTable **, ...);

    // HashTable initialization function
    // '''''''''''''''''''''''''''''''''
    HashTable * newHash(int elements);
    void dropHashTable( HashTable * );

    uint_t keyhash(HashTable*, char *);

    
// ===========================================================================
#endif // __HASHLIST_1__H__
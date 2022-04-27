
// These headers are specific to this module
// they are not seen outside
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include "hashtable.h"


uint_t HASHD_PRIME = 1309401007;



/* Function: keyhash
 * -------------------------------------------------
 * > This function generates hashtable index from string and given range.
 * > The range is specified as hashtable size property.
 * > HowWorks:
 * > - until the end of the keystring is met
 * > - starting from value of thero hash number is modified in this way:
 * > --- hash = ( hash << 5 | hash >> 27
 * > --- hash += (unsigned int) current_key_char
 * > - after all this a compression function is applied to the hash
 * > - with a specific purpose to coerce resulting hash
 * > - to a more pseudo-randomized fixed value
 * > - and to reduce number of futher possible collisions
 * > - then the result is coerced to hashtable's defined range (size)
 * -------------------------------------------------
 * @param { HashTable ** } ht
 *  | pointer --> to to a specific hashtable
 * @param { char * } namekey
 *  | the desired string key to hash 
 * -------------------------------------------------
 * @RETURNS { unsigned int }
 *  | generated within the range of hashtable index 
 * -------------------------------------------------
 */
uint_t keyhash(HashTable * ht, char * namekey)
{
    uchar_t * s = (unsigned char *) namekey;
    uint_t char_counter = 0,
           hash = 0;

    // HashTable for a little
    while ( *s != 0 )
    {
        hash  = (hash << 5) | (hash >> 27);
        hash += (uint_t) *s;
        ++s;
    }

    // Use compress function to compress a little
    // ------------------------------------------
    uint_t compressed = ( ht->__salt_a * hash + ht->__salt_b ) % HASHD_PRIME;
    
    // Reduce to the given range (size of array)
    // -----------------------------------------
    return compressed % ht->size;
}

/* Function: hashtable_put
 * -------------------------------------------------
 * > This function stores given pointer to user's data
 * > handling collisions using Separate Chaining method
 * -------------------------------------------------
 * @param { HashTable ** } ht
 *  | a pointer to a specific hashtable structure
 * @param { char * } name
 *  | Named key of the hashtable (it is then implicitly translated to index)
 * @param ( void * } data
 *  | this is generic pointer to whatever the data user wants to store
 * -------------------------------------------------
 * @RETURNS void
 * -------------------------------------------------
 */
void hashtable_put(HashTable * ht, char name[], void * data)
{
    // hash index from name
    uint_t hindex = keyhash(ht, name);

    // temporary shortcut pointer to the table element
    // -----------------------------------------------
    Node * bucket = ht->table[hindex];
    
    // if no items were inserted before
    // --------------------------------
    if ( ! bucket->data && ! bucket->next )
    {
        strcpy(bucket->name, name);
        bucket->data = (void *) data;
        bucket->next = 0;

        printf("[SET]: table[%d] => %s\n", hindex, bucket->name);
        return;
    }
    
    bool_t name_match; // check if node name and provided name match
    Node * node = bucket; // points to last node before null

    // iterate through chained nodes in bucket
    do {
        name_match = ( strcmp(bucket->name, name) == 0 );
        if ( name_match )
        {
            bucket->data = (void *) data;
            printf("[CHANGE]: table[%d] => %s\n", hindex, bucket->name);
            return;
        }
        node = bucket; // this is needed to save
        bucket = bucket->next; // this can be null so above is needed
    }
    while ( bucket != 0 );
    
    // if no matches were found
    // then just create and append a new node to the chain
    // ---------------------------------------------------
    node->next = malloc ( sizeof (Node) );
    strcpy (node->next->name, name);
    node->next->data = (void *) data;
    node->next->next = 0;
    printf("[INSERT]: table[%d] => %s\n", hindex, node->next->name);
}


/* Function: hashtable_get_ptr
 * -------------------------------------------------
 * > Obrain the pointer to a specific (target hash pointer) placed at index
 * -------------------------------------------------
 * @param { HashTable * ht } ht
 *  | the pointer to a hashtable itsef
 * @param { char * } name
 *  | the string that holds the name of the in table
 * -------------------------------------------------
 * @RETURNS { HashNode ** }
 *  | pointer --> to a pointer of hashtable item
 * -------------------------------------------------
 */
Node * hashtable_get_ptr(HashTable * ht, char name[])
{
    uint_t hashindex = keyhash(ht, name);
    Node * node = ht->table[ hashindex ];
    // In case of collision use Separate Chaining method
    // '''''''''''''''''''''''''''''''''''''''''''''''''
    if ( node->next == 0 )
        return node;
    while ( node->next != 0 )
    {
        if ( strcmp ( node->name, name ) == 0 ) break;
        node = node->next;
    }
    return node;
}



/* Function: hashtable_get
 * -------------------------------------------------
 * > This one retrieves an item data from hashtable
 * > so to say
 * > -----------------------------------------------
 * @param { HashTable * } ht
 * @param { char []     } name
 * -------------------------------------------------
 * @RETURNS { void * }
 *  | pointer to the data
 */
void * hashtable_get(HashTable * ht, char name[])
{
    return hashtable_get_ptr(ht, name)->data;
}


/* Function: hashtable_del
 * -------------------------------------------------
 * > This one removes the pointer to the item
 * > it is responsibility of the user
 * > to handle memory management
 * > -----------------------------------------------
 * @param { HashTable * } ht
 * @param { char []     } name
 * -------------------------------------------------
 * @RETURNS { void }
 */
void hashtable_rem(HashTable * ht, char name[])
{
    ( hashtable_get_ptr(ht, name)->data ) = 0;
}


HashTable * newHash (int elements)
{
    HashTable * ht = malloc ( sizeof (HashTable) );
    ht->size = elements;
    // Allocate array of pointers to structures
    // ----------------------------------------
    Node ** tbl = malloc ( sizeof ( Node * ) * elements);
    while (elements--)
    {
        tbl[elements] = malloc ( sizeof ( Node ) );
    }
    ht->table = tbl;

    // Assign functions as hashtable asmethods
    // '''''''''''''''''''''''''''''''''''''''
    ht->put = (void   (*)(HashTable *, char *, void*)) hashtable_put;
    ht->get = (void * (*)(HashTable *, char *       )) hashtable_get;
    ht->rem = (void   (*)(HashTable *, char *       )) hashtable_rem;


    // Set pseudo-random *salt* values for a hash function
    // '''''''''''''''''''''''''''''''''''''''''''''''''''
    ht->__salt_a = rand() % (HASHD_PRIME - 1);
    ht->__salt_b = rand() % (HASHD_PRIME - 1);


    return ht;
}

// Free all the occupied by the hashtable memory
void dropHashTable(HashTable * ht)
{
    int els = ht->size;

    while (--els)
        free ( ht->table[els] );
    free ( ht->table );
}


/* = FUNCTION =: is_valid_hashiter_item
 * -------------------------------------------------------------------------
 * > Check if the current hashtable iterator item position
 * > is within allowed hashtable borders and hashtable item is not null
 * -------------------------------------------------------------------------
 * @param { HashIter * } hi
 *      hashtable iterator data structure
 * @param { Node * } bucket
 *      hashtable's node
 * -------------------------------------------------------------------------
 * @Returns { bool_t }
 *      bool_t is just an aliased (char)
 * -------------------------------------------------------------------------*/
bool_t is_valid_hashiter_item( HashIter * hi, Node * bucket )
{
    return (    (hi->pos) < (hi->end)
             && (hi->pos) >= (hi->start)
           )
        && ( ! bucket->data && ! bucket->next);
}


/* = FUNCTION: hitertext
 * -------------------------------------------------------------------------
 * > This function is used as a part of HashIter (hash iterator) struct.
 * > THE PURPOSE is to iterate through each item within given range.
 * > If no range provided, then it is from start to end of hashtable.
 * > It skips empty items.
 * > The resulting items order is undefined. Well... it's hashtable.
 * -------------------------------------------------------------------------
 * @param { HashIter * } hi
 *      hashtable iterator data structure (pointer to it)
 * @param { Node ** } item
 *      pointer to hashtable item.
 *      The indirection this pointer points to is changed on each call.
 *      Except when there is nothing to address.
 * -------------------------------------------------------------------------
 * @Returns { bool_t }
 *      0 - if the iteration is over
 *      1 - when there are items left to iterate
 * -------------------------------------------------------------------------*/
bool_t hiternext(HashIter * hi, Node** item)
{        
    HashTable * ht = *hi->ht;
    Node * bucket = ht->table[hi->pos];
    
    // Skip empty items
    // =
    while ( is_valid_hashiter_item (hi, bucket) )
    {
        ++hi->pos;
        bucket = ht->table[hi->pos];
    }
    
    // Array completely traversed no items left to iterate
    // =
    if ( hi->pos >= hi->end )
    {
        // *item = 0; // if we really need to null the item pointer
        return 0;
    }

    // Walk a Separate Chain if there is one
    // =
    if ( bucket->next )
    {
        if ( ! hi->lastnode_ptr )
            hi->lastnode_ptr = bucket;
        *item = hi->lastnode_ptr;
        // printf("%s\n", hi->lastnode_ptr->name);
        hi->lastnode_ptr = hi->lastnode_ptr->next;
        
        if ( ! hi->lastnode_ptr ) ++hi->pos;
        
        return 1;
    }
    ++hi->pos;
    *item = bucket;
    return 1;
}



/* = FUNCTION =: newHashIter
 * -------------------------------------------------------------------------
 * > This function intializes the hash iterator structure.
 * > WARNING:
 * >    it is responsibility of the user 
 * >    to release memory occupied by the iterator structure
 * -------------------------------------------------------------------------
 * @param { HashTable * } ht
 *      hashtable which is subject for iteration
 * @vararg [ uint_t ] startFrom
 *      this POSITIONAL parameter is actually unsigned int
 *      which is [OPTIONAL] and specifies the starting iteration position
 * @vararg [ uint_t ] stopAt
 *      this POSITIONAL parameter is actually unsigned int
 *      which is [OPTIONAL] and specifies the starting iteration position
 * -------------------------------------------------------------------------
 * @Returns { HashIter * }
 *      pointer to hash iterator structure
 * -------------------------------------------------------------------------*/
HashIter * newHashIter(HashTable ** ht, ...)
{
    va_list args;
    va_start (args, *ht);


    // Parse additional arguments
    uint_t startFrom = va_arg(args, uint_t);
    uint_t stopAt    = va_arg(args, uint_t);

    // position guards
    if ( stopAt >= (*ht)->size || stopAt < 0 ) { stopAt = (*ht)->size; }
    if ( startFrom < 0 || startFrom >= stopAt ) { startFrom = 0; }
    
    // create on heap to avoid destruction on exit
    HashIter * hi = malloc ( sizeof ( HashIter ));
    hi->start = startFrom;
    hi->end   = stopAt;
    hi->pos = 0;
    hi->lastnode_ptr = 0;
    hi->ht = ht;
    hi->next = (bool_t (*)(HashIter*, Node**)) hiternext;

    va_end(args);

    return hi;
}
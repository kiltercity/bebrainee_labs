#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "hashtable/hashtable.h"
#include "lab4/lab4_utils.h"

#define BUS_ROUTES_COUNT 8
#define ROUTE_BUS_COUNT_MIN 5
#define ROUTE_BUS_COUNT_MAX 20




int main (void)
{
    // Randomize even more
    // ===
    // srand ( time(0) );

    HashTable * routes = newHash(BUS_ROUTES_COUNT);

    /* Generate random bus count for each route
     * save all the shit to the hashtable under keys in form of <route_X>
     *----------------------------------------------------------------------*/  
    printf ("\n\nFilling the hash table with bus routes data\n");
    uint_t * tranitive_data_storage = distribute_random_bus_numbers( routes,
            BUS_ROUTES_COUNT,
            ROUTE_BUS_COUNT_MIN,
            ROUTE_BUS_COUNT_MAX
    );


    /* Print some region from assigned routes bus counts
     * usign our brand new uncompleted and error-PRONE 
     *-----------------------------------------------------------------------*/
     // Starting and ending positions for hashiterator
    uint_t startFrom = 54;
    uint_t stopAt = 70;

    // Create HashTable iterator
    HashIter * hashiter = newHashIter(&routes, startFrom, stopAt); // hash iterator item
    Node * hitem = 0; // transitive pointer holding current hash item


    printf ("\nPrint part of hash table using hash iterator: \n");
    int c = -1;
    while (hashiter->next(hashiter, &hitem))
    {
        printf("|%s ===> %d |\n", hitem->name, *(uint_t*)hitem->data);
    }


    // printf("%s DJFKLJSDKLFJKLSDJFKLJDSKLFJ", );
    /* Save allocated route table to the file
     * ---------------------------------------------------------------------*/
    printf ("\n\nSave hashtable to the file\n"); 
    FILE_STATUS st_write = save_routes_to_file(routes, BUS_ROUTES_COUNT);

    
    /* Read route table from the file
     * ---------------------------------------------------------------------*/
    HashTable * newTable; 
    FILE_STATUS st = read_routes_from_file(&newTable);

    

    /* RELEASE MEMORY
     -----------------------------------------------------------------------*/
    printf ("\n\nFreeing memory...\n");
    free (hashiter);
    dropHashTable( routes );
    dropTransitiveStorage ( tranitive_data_storage, BUS_ROUTES_COUNT );
    return 0;
}
#ifndef __TASK4_UTILS__H__
#define __TASK4_UTILS__H__
// ===========================================================================

    #include "hashtable/hashtable.h"

    

    typedef enum __file_statuses__ {
        FILE_OPEN_ERROR = 1
        
    } FILE_STATUS;



    /* = FUNCTION =: distribute_random_bus_numbers
    * ---------------------------------------------------------------------
    * > This function fills the hash with randomly generated amount of buses
    * > for each route.
    * > It creates a list of integer values and returns the pointer to it.
    * > The pointer has to be freed later on.
    * > The hash is filled then with those values from the list,
    * > and stored under unique route key name (route_1, route_2...)
    * ---------------------------------------------------------------------
    * @param { HashTable * } ht
    *      pointer to the hash table
    * @param { int } routes_count
    *      ...
    * @param { int } route_bus_count_min
    *      bottom limit for the amount of buses on the route
    * @param { int } route_bus_count_max
    *      same as previous, but it it the top limit
    * ---------------------------------------------------------------------
    * @Returns { uint_t * }
    *      this is the pointer to the allocated list of the bus numbers
    *      it has to be freed later by another funcion
    * ---------------------------------------------------------------------*/
    uint_t * distribute_random_bus_numbers(
        HashTable * ht, // target storage that keeps assigned buses count
        int routes_count,
        int route_bus_count_min, // minimum buses on route
        int route_bus_count_max // maximum buses on route
    );
    void dropTransitiveStorage(uint_t * ts, int count);

    FILE_STATUS save_routes_to_file (HashTable* ht, uint_t count);
    FILE_STATUS read_routes_from_file (HashTable **);

// ===========================================================================
#endif // __TASK4_UTILS__H__



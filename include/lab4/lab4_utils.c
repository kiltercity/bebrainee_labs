#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lab4_utils.h"



uint_t * distribute_random_bus_numbers (
        HashTable * ht, // target storage that keeps assigned buses count
        int routes_count,
        int route_bus_count_min, // minimum buses on route
        int route_bus_count_max // maximum buses on route
    )
{
    uint_t * number_stack; // store array of numbers
    char keyname[256]; // store the hash key

    // this is the bias correction for random number top border
    // that lower random border limit introduces
    // --------------------------------------------------------
    uint_t random_upper_limit = (route_bus_count_max - route_bus_count_min);


    /*  The name describes the way of item placement not memory type.
    | * Allocate memory for array of numbers of buses for each route
    \ * ------------------------------------------------------------ */
    number_stack = mmap(NULL, routes_count * sizeof (uint_t),
                                PROT_WRITE | PROT_READ,
                                MAP_ANONYMOUS | MAP_PRIVATE, -1, NULL);

    /*  Populate the allocated array with random data.
    | * That is:
    | * - generate random number of buses for each route
    | * - save them to allocated number stack
    | * - save the pointer to the hashtable under specific name of route
    \ * ---------------------------------------------------------------*/
    int pos = -1;
    while ( ++pos < routes_count )
    {
        number_stack[ pos ] = route_bus_count_min
                            + rand() % random_upper_limit;
        sprintf ( keyname, "route_%d", pos );
        ht->put ( ht, keyname, &number_stack[pos] );
    }

    // Return the pointer to the allocated data for releasing later
    // ------------------------------------------------------------
    return number_stack;
}


void dropTransitiveStorage( uint_t * ts, int count )
{
    munmap (ts, count * sizeof (uint_t));
}


FILE_STATUS save_routes_to_file (HashTable* ht, uint_t count)
{

    FILE * _file = fopen ( "routes.txt", "w" );

    // Ensure no action is taken when creating file failed
    if ( ! _file )
        return 0;


    char route_name[1024];

    // must be enough to hold all route string + space + \0 char
    // char * buses_buffer_str = malloc ( sizeof (char) * 8192); 

    int route = 0;
    uint_t bus =0, buscount = -1;
    while (route < count)
    {
        if ( bus >= buscount || buscount == -1 )
        {
            sprintf(route_name, "route_%d", route); 
            buscount = *(uint_t *) ht->get(ht, route_name);
            printf("| Saving Route: %s ==> Buses: %d \n", route_name, buscount);
            
            bus = 0; // reset buses counter
            ++route; // increase route counter
            continue;
        }
        ++bus;
        fprintf ( _file, "%d ", route );
        
    }

    fclose(_file);
}



FILE_STATUS read_routes_from_file(HashTable ** ht_ptr)
{
    FILE * _file = fopen("routes.txt", "r");

    // If we couldn't open the file there is actually nothing to do
    // OFCOURSE we could do retry again, but nobody cares
    if ( ! _file )
        return 0;


    // Common buses on all routes together
    unsigned int buscount = 0,
                 route_buses = 0,
                 routes_count = 1;

    // Current route number
    int route_number = 0;
    int prev_route_number = 0;


    printf("\n\nReading and calculating buses for each route from file\n");

    while ( fscanf (_file, "%d", &route_number ) != EOF )
    {
        if (route_number != prev_route_number && route_buses != 0)
        {
            printf("Route [ %d ] has %d buses\n", 
                   prev_route_number, route_buses);

            buscount += route_buses;
            route_buses = 0;
            ++routes_count;
        }
        ++route_buses;
        prev_route_number = route_number;
    }
    
    /* The loop is composed in such way
     * that the first iteration route_num check is thrown to the blackhole
     * so no 0-item gets printed (route_num -1 ++ = 0)
     * still the counted buses amount is being recorded
     * -
     * but the time the next different route gets recorded to <route_number>
     * it is already late to print its counter
     * cause the buses count now refers to the previous route
     * -
     * and so when the last route is read 
     * it in fact still remains a current route
     * -
     * and when the next different route is to be read
     * the EOF is met and the loop exits without the last <route_num> check
     * and no printing of the last route is done
     * -
     * So we compensate this by this "custom" last print operation
     * ---------------------------------------------------------------------*/   
    printf("Route [ %d ] has %d buses\n", 
                   prev_route_number, route_buses);

    
    // Print counted amount of bubses on all routes alltogether
    printf("On the whole there are: [ %d ] buses on [ %d ] routes\n",
            buscount,
            routes_count);

    fclose (_file);
}
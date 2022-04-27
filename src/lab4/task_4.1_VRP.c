#include "hashtable/hashset.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER 0x30
#define HIGHR 0x39



char get_rnum()
{
    // 
    return (48 + (rand() % 9));
}


int main (void)
{
    srand ( time(0) );
    
    uint_t test_items_count = 100, first_short_count = 50,
           current = 0;
    // Vehicle registration plate
    // ===
    HashSet * vrps = newHashSet(test_items_count);


    printf("\n\n---------------------------------------------\n");
    printf("Filling random car numbers: \n");
    printf("--------------------------------------------- \n");
    while ( current++ < first_short_count )
    {
        char vn[3];
        sprintf ( vn, "%c%c", get_rnum(), get_rnum() );
        
        // printf("INSERTING GENERATED : [ %s ]\n", (char*)vrps->get(vrps, vn));
        vrps->add(vrps, vn);
    }

    printf("\n\n---------------------------------------------\n");
    printf("Generating second set and see if exists: \n");
    printf("--------------------------------------------- \n");
    current = 0;
    while ( current++ < first_short_count )
    {
        char vn[3];
        sprintf ( vn, "%c%c", get_rnum(), get_rnum() );
        
        char b_exists = vrps->add(vrps, vn);
        if ( b_exists )
            printf("| * --> ITEM EXISTS : [ %s ]\n", (char*)vrps->get(vrps, vn));
    }


    return 0;
}
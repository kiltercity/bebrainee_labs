#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable/hashtable.h"


void handler (HashTable * ht, Node * buck);

int main ()
{
    HashTable * ht = newHash(5);
    
    ht->table[0] = malloc ( sizeof (Node) );

    Node * bucket = ht->table[0];

    int sm = 213;
    int sm2 = 214;
    int sm3 = 215;
    int sm4 = 216;
    int sm5 = 217;
    int sm6 = 218;
    int sm7 = 219;
    int sm8 = 220;
    char sm9[] = "hello , world";
    int sm10 = 222;

    ht->put ( ht, "name_1", &sm  );
    ht->put ( ht, "name_2", &sm2 );
    ht->put ( ht, "name_3", &sm3 );
    ht->put ( ht, "name_4", &sm4 );
    ht->put ( ht, "name_5", &sm5 );
    ht->put ( ht, "name_6", &"sdkjfk fuck1" );
    ht->put ( ht, "name_7", &sm7 );
    ht->put ( ht, "name_8", &sm8 );
    ht->put ( ht, "integer_data_key", &(int){32} );
    ht->put ( ht, "name_9", &"sdkjfk fuck1" );
    ht->put ( ht, "name_9", &sm10 );


    ht->put ( ht, "name_6", &"sdkfuck1" );
    strcpy ( ht->table[1]->name, "name_2" );

    bucket = ht->table[1];
    strcpy (bucket->name, "after ptr");


    handler (ht, ht->table[3]);
    handler (ht, ht->table[0]);
    handler (ht, ht->table[2]);
    handler (ht, ht->table[2]->next);
    handler (ht, ht->table[4]);
    handler (ht, ht->table[1]);
    handler (ht, ht->table[1]->next);
    handler (ht, ht->table[3]->next);
    // handler (ht, ht->table[3]->next->next);
    printf("\n\n");
    handler (ht, ht->table[3]->next->next);
    handler (ht, ht->table[3]->next);
    handler (ht, ht->table[1]->next);
    handler (ht, ht->table[1]);
    handler (ht, ht->table[4]);
    handler (ht, ht->table[2]->next);
    handler (ht, ht->table[2]);
    handler (ht, ht->table[0]);
    handler (ht, ht->table[3]);
    
    strcpy( sm9, "dfsdf");
    ht->put ( ht, "string_data_key", &"some string" );
    ht->put ( ht, "integer_data_key", &(int){32} );
    ht->put ( ht, "integer_data", &(int){762} );
    printf("integer_data_key ---> %d \n", *(int*)(ht->get(ht, "integer_data")));

    // printf("%s\n", ht->table[0]->name);
    // // printf("%s\n", ht->table[1]->name);
    return 0;
}


void handler (HashTable * ht, Node * buck)
{
    printf("INSIDE: %s : %d \n", buck->name, *(int*)buck->data);

    // strcpy ( buck->name, "this is after handler");

    buck = 0;
}
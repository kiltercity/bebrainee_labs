#include <stdio.h>
#include <stdlib.h>


#include <unity/unity.h>
#include "hashtable/hashtable.h"


HashTable * ht;


void setUp(void) {
    ht = newHash ( 5 );
}

void tearDown(void) {
    // dropHash ( ht );
}

void test_hashtable_items_data(void) {
    ht->put ( ht, "string_data_key", &"some string" );
    ht->put ( ht, "integer_data_key", &(int){32} );
    ht->put ( ht, "integer_data", &(int){32} );

    // Assert all assignations went properly
    // and table contains values that were assigned
    // ===
    TEST_ASSERT_EQUAL_STRING("some string", (char*)ht->get(ht, "string_data_key"));
    TEST_ASSERT_EQUAL_INT(32, *(int*)ht->get(ht, "integer_data_key"));
    TEST_ASSERT_EQUAL_INT(32, *(int*)ht->get(ht, "integer_data"));

    // Delete or otherwise null the data pointer at the specified index
    // ===
    ht->rem ( ht, "string_data_key" );

    // Assert that the pointer for data is now null
    // ===
    TEST_ASSERT_NULL ( ht->get( ht, "string_data_key" ));
}



int main ()
{
    UNITY_BEGIN();

    RUN_TEST(test_hashtable_items_data);

    return UNITY_END();
}
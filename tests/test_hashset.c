#include <unity/unity.h>
#include "hashtable/hashset.h"


HashSet * hs;


void setUp(void) {
    hs = newHashSet ( 5 );
}

void tearDown(void) {
    dropHashSet ( hs );
}

void test_hashset_items(void) {
    char test_item[] = "Apple";

    hs->add (hs, test_item);
    bool_t exists = hs->add (hs, test_item);
    
    // Item already exists
    // ===
    TEST_ASSERT_TRUE ( exists );

    // Test if set value is the same returned from hashset
    // ===
    char * result_item = hs->get (hs, test_item);
    TEST_ASSERT_EQUAL_STRING ( test_item, result_item );
}



int main ()
{
    UNITY_BEGIN();

    RUN_TEST(test_hashset_items);

    return UNITY_END();
}
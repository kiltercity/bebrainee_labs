#include "queue.h"



/* > QUEUEs work by FIFO principle
 * > so the first item that added
 * > will be the first taken from queue
 */

int main()
{

    // Initialization
    // """"""""""""""
    Queue_t * queue = newQueue();
    node_t * node1 = malloc ( sizeof (node_t) );
    node_t * node2 = malloc ( sizeof (node_t) );


    // Sample data
    // """""""""""
    char * n1data = "this is node 1 data";
    char * n2data = "this is node 2 data";
    char * n3data = "this item was added last "
                    "and was created by new_node func";
    
    // Compound literal int
    // """"""""""""""""""""
    node1->data = n1data;
    node2->data = n2data;

    printf("---------------------------------------------------\n");

    // Add (push) to queue
    // """""""""""""""""""
    queue->push(queue, node1);
    printf("Pushed first item: %s\n", (char*)node1->data);

    queue->push(queue, node2);
    printf("Pushed second item: %s\n", (char*)node2->data);

    node_t * node3 = queue->new_node(queue, n3data, sizeof(n3data));
    printf("Pushed third item: %s\n", (char*)node3->data);

    printf("---------------------------------------------------\n");

    // Get (dash) from queue
    // """""""""""""""""""""
    node_t * first_in  = queue->dash(queue);
    node_t * second_in = queue->dash(queue);
    node_t * third_in  = queue->dash(queue);

    // Print results
    printf("%s\n",  (char*) first_in->data);
    printf("%s\n",  (char*) second_in->data);
    printf("%s\n",  (char*) third_in->data);


    // Explanation
    // """""""""""
    printf(
        "---------------------------------------------------\n"
        "So we see how the first added item comes out first.\n"
        "and last added item is last out\n"
        "This is called a QUEUE\n"
        "---------------------------------------------------\n"
    );

    return 0;
}
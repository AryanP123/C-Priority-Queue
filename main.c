#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main(int argc, char* argv[]) {
    
    PRIORITY_QUEUE hQueue = NULL;
    
    hQueue = priority_queue_init_default();

    if (hQueue == NULL) {
        printf("Failed to allocate space for Queue\n");
        exit(1);
    }
    
    //insert values
    priority_queue_insert(hQueue, 13, 10);
    priority_queue_insert(hQueue, 49, 4);
    priority_queue_insert(hQueue, 35, 7);
    
    printf("%d\n", priority_queue_front(hQueue, NULL));
    priority_queue_service(hQueue);
    
    printf("%d\n", priority_queue_front(hQueue, NULL));
    priority_queue_service(hQueue);
    
    printf("%d\n", priority_queue_front(hQueue, NULL));
    priority_queue_service(hQueue);
    
    priority_queue_insert(hQueue, 23, 9);
    priority_queue_insert(hQueue, 37, 3);
    printf("%d\n", priority_queue_front(hQueue, NULL));
    priority_queue_service(hQueue);
    
    priority_queue_destroy(&hQueue);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

struct queue_pair
{
    int top;
    int value;
};
typedef struct queue_pair Queue_pair;


struct priority_queue
{
    Queue_pair* data;
    int size;
    int capacity;
    int head;
    int end;
};
typedef struct priority_queue Priority_queue;

PRIORITY_QUEUE priority_queue_init_default(void)
{
    Priority_queue* pPQ;
    pPQ = (Priority_queue*)malloc(sizeof(Priority_queue));
 
    if (pPQ != NULL)
    {
        pPQ->head = 0;
        pPQ->end = 0;
        pPQ->size = 0;
        pPQ->capacity = 1;
        pPQ->data = (Queue_pair*)malloc(sizeof(Queue_pair)*pPQ->capacity);
        
        if (pPQ->data == NULL)
        {
            free(pPQ);
            pPQ = NULL;
        }
    }
    return pPQ;
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* status)
{
    Priority_queue* pPQ= (Priority_queue*)hQueue;
    if (priority_queue_is_empty(pPQ))
    {
        if (status != NULL)
        {
            *status = FAILURE;
        }
        return 0;
    }
    if (status != NULL)
    {
        *status = SUCCESS;
    }
    return (pPQ->data[pPQ->head]).value;
}


Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
    Priority_queue* pPQ = (Priority_queue*)hQueue;
    Queue_pair* temp, temp2;
    int i;
    int parent;

    if (pPQ->size >= pPQ->capacity)
    {
        temp = (Queue_pair*)malloc(sizeof(Queue_pair) * pPQ->capacity * 2);
        if (temp == NULL)
        {
            return FAILURE;
        }
        for (i = 0; i < pPQ->size; i++)
        {
            temp[i] = pPQ->data[i];
        }
        free(pPQ->data);
        pPQ->capacity *= 2;
        pPQ->data = temp;
    }
    i = pPQ->size;
    (pPQ->data[i]).top = priority_level;
    (pPQ->data[i]).value = data_item;
    parent = (i - 1) / 2;
    while (i >= 1 && ((pPQ->data[i]).top > (pPQ->data[parent]).top))
    {
        temp2 = pPQ->data[parent];
        pPQ->data[parent] = pPQ->data[i];
        pPQ->data[i] = temp2;
        i = parent;
        parent = (i - 1) / 2;
    }
    pPQ->size++;
    pPQ->head = 0;
    pPQ->end = pPQ->size-1;
    return SUCCESS;
}


Status priority_queue_service(PRIORITY_QUEUE hQueue) {
    Priority_queue* pPQ = (Priority_queue*)hQueue;
    Queue_pair* temp;
    Queue_pair* temp2;
    int x = 1;
    int i = 0;
    int left_child = (2 * i) + 1;
    int right_child = (2 * i) + 2;
    temp = (Queue_pair*)malloc(sizeof(Queue_pair));
    temp2 = (Queue_pair*)malloc(sizeof(Queue_pair));
    if (priority_queue_is_empty(pPQ))
    {
        return FAILURE;
    }
    *temp = pPQ->data[0];
    pPQ->data[0] = pPQ->data[pPQ->end];
    pPQ->data[pPQ->end] = *temp;
    pPQ->size--;
    while (left_child < pPQ->size && x==1)
    {
        x = 0;
        if (right_child < pPQ->size && (pPQ->data[right_child]).top>(pPQ->data[left_child]).top)
        {
            if ((pPQ->data[right_child]).top > (pPQ->data[i]).top)
            {
                *temp2 = pPQ->data[i];
                pPQ->data[i] = pPQ->data[right_child];
                pPQ->data[right_child] = *temp2;
                i = right_child;
                x = 1;
                right_child = (2 * i) + 2;
                left_child = (2 * i) + 1;
            }
        }
        else
        {
            if ((pPQ->data[left_child]).top > (pPQ->data[i]).top)
            {
                *temp2 = pPQ->data[i];
                pPQ->data[i] = pPQ->data[left_child];
                i = left_child;
                pPQ->data[left_child] = *temp2;
                x = 1;
                right_child = (2 * i) + 2;
                left_child = (2 * i) + 1;
            }
        }
    }

    pPQ->end = pPQ->size - 1;

    return SUCCESS;
}


Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
    Priority_queue* pPQ = (Priority_queue*)hQueue;
    return (Boolean)(pPQ->size <= 0);
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
    Priority_queue* pPQ = (Priority_queue*)*phQueue;
    free(pPQ->data);
    free(*phQueue);
    *phQueue = NULL;
    return;
}

#include "queue.h"

/* creates a new queue with a given size */
queue_t* create_queue(int capacity)
{
    // Alloc memory for queue and memory allocation check
    queue_t * queue = malloc(sizeof(queue_t));
    queue_lenght_check(queue);

    // Set maximum and current capacity
    queue->capacity_max = capacity;
    queue->capacity_current = 0;

    // Alloc memory for data and memory allocation check
    queue->data = (void **)malloc(capacity * sizeof(void *));
    if (queue->data == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        free(queue);
        exit(100);
    }

    // Fill queue with nuls
    for (unsigned int counter = 0; counter < capacity; counter++)
    {
        queue->data[counter] = NULL;
    }

    queue->head_index = 0;
    queue->tail_index = 0;

    return queue;
}

/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue)
{
    if (queue != NULL)
    {
        free(queue->data);
        free(queue);
    }
}

/*
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data)
{
    queue_lenght_check(queue);

    // Increase queue capacity
    if (queue->capacity_current >= queue->capacity_max)
    {
        // Create temporary array with 2x capacity
        void **tmp = (void **)malloc(queue->capacity_max * 2 * sizeof(void *));

        // Memory error check
        if (tmp == NULL) {fprintf(stderr, "Memory allocation error!\n");
        exit(100);}

        // Fill temporary array by data
        for (unsigned int i = 0; i < queue->capacity_current; i++)
        {
            tmp[i] = queue->data[(queue->head_index + i) % queue->capacity_max];
        }

        free(queue->data);

        // Update data, capacity, indexes
        queue->data = tmp;
        queue->capacity_max = queue->capacity_max * 2;
        queue->head_index = 0;
        queue->tail_index = queue->capacity_current - 1;
    }

    int current_cap = queue->capacity_current;
    int max_cap = queue->capacity_max;
    int head = queue->head_index;

    // Add new data to queue and update current capacity
    queue->tail_index = (head + current_cap) % max_cap;

    queue->data[queue->tail_index] = data;

    queue->capacity_current += 1;
    return true;
}

/*
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue)
{
    queue_lenght_check(queue);

    if (queue->capacity_current < (queue->capacity_max / 3))
    {
        // Create temporary array with 0.3x capacity
        void **tmp = (void **)malloc((queue->capacity_max / 3) * sizeof(void *));

        // Memory error check
        if (tmp == NULL) {fprintf(stderr, "Memory allocation error!\n");
        exit(100);}

        // Fill temporary array by data
        for (unsigned int i = 0; i < queue->capacity_current; i++)
        {
            tmp[i] = queue->data[(queue->head_index + i) % queue->capacity_max]; 
        }

        free(queue->data);

        // Update data, capacity, indexes
        queue->data = tmp;
        queue->head_index = 0;
        queue->capacity_max = queue->capacity_max / 3;

        if (queue->capacity_current != 0) 
            queue->tail_index = queue->capacity_current - 1;        
    }

    if (queue->capacity_current == 0) return NULL;

    int start = queue->head_index;

    queue->head_index = (start + 1) % queue->capacity_max;
    queue->capacity_current -= 1;

    void *pointer = queue->data[start];
    return pointer;
}

/*
 * gets idx-th element from the queue, i.e., it returns the element that 
 * will be popped after idx calls of the pop_from_queue()
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx)
{
    queue_lenght_check(queue);

    // Check if index is in right range
    if (idx >= queue->capacity_current || idx < 0) return NULL;

    else
    {
        void *pointer;
        int head = queue->head_index;
        int max_cap = queue->capacity_max;

        // Create pointer to the needed index
        pointer = queue->data[(idx + head) % max_cap];

        return pointer;
    }
    
}

/* gets number of stored elements */
int get_queue_size(queue_t *queue)
{
    return queue->capacity_current;
}

void queue_lenght_check(queue_t *queue)
{
    if (queue == NULL)
    {
        fprintf(stderr, "Queue is empty!\n");
        exit(100);
    }
}

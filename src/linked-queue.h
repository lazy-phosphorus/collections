#ifndef __COLLECTIONS_LINKED_QUEUE__
#define __COLLECTIONS_LINKED_QUEUE__

typedef struct __LinkedQueueNode {
    void* value;
    struct __LinkedQueueNode* next;
} LinkedQueueNode;

typedef struct {
    LinkedQueueNode* head;
    LinkedQueueNode* tail;
    unsigned int elementSize;

    unsigned int Size;
} LinkedQueue;

int LinkedQueueNodeConstruct(LinkedQueueNode* const restrict node,
                             const void* const restrict value,
                             const unsigned int elementSize);

LinkedQueueNode* LinkedQueueNodeNew(const void* const restrict value,
                                    const unsigned int elementSize);

void LinkedQueueNodeDestruct(LinkedQueueNode* const restrict node);

void LinkedQueueNodeDelete(LinkedQueueNode** const restrict node);

int LinkedQueueConstruct(LinkedQueue* const restrict queue,
                         const unsigned int elementSize);

LinkedQueue* LinkedQueueNew(const unsigned int elementSize);

void LinkedQueueDestruct(LinkedQueue* const restrict queue);

void LinkedQueueDelete(LinkedQueue** const restrict queue);

void* LinkedQueueFront(const LinkedQueue* const restrict queue);

int LinkedQueuePush(LinkedQueue* const restrict queue,
                    const void* const restrict value);

int LinkedQueuePop(LinkedQueue* const restrict queue);

#endif  // __COLLECTIONS_LINKED_QUEUE__
#ifndef __COLLECTIONS_STACK__
#define __COLLECTIONS_STACK__

typedef struct __StackNode {
    struct __StackNode* previous;
    void* value;
} StackNode;

typedef struct {
    StackNode* tail;
    unsigned long elementSize;

    unsigned int Size;
} Stack;

int StackNodeConstruct(StackNode* const restrict node,
                       const void* const restrict value,
                       const unsigned int elementSize);

StackNode* StackNodeNew(const void* const restrict value,
                        const unsigned int elementSize);

void StackNodeDestruct(StackNode* const restrict node);

void StackNodeDelete(StackNode** const restrict node);

int StackConstruct(Stack* const restrict stack, const unsigned int elementSize);

Stack* StackNew(const unsigned int elementSize);

void StackDestruct(Stack* const restrict stack);

void StackDelete(Stack** const restrict stack);

void* StackTop(const Stack* const restrict stack);

int StackPush(Stack* const restrict stack);

int StackPop(Stack* const restrict stack);

#endif  // __COLLECTIONS_STACK__
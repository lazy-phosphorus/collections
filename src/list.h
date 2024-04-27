#ifndef __COLLECTIONS_LIST__
#define __COLLECTIONS_LIST__

typedef struct __ListNode {
    void *value;
    struct __ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    unsigned int Size;
} List;

int ListNodeConstruct(const void *const value);

#endif  // __COLLECTIONS_LIST__

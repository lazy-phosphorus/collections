#include "common.h"

int main() {
    ArrayHeap *heap = ArrayHeapNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayHeapPush(heap, &test);
    }
    ArrayHeapIterator iterator = ArrayHeapGetIterator(heap);
    for (unsigned int i = 0; i < heap->Size; i++) {
        Test *temp = (Test *)ArrayHeapIteratorGetValue(iterator);
        if (temp->a > 24 || temp->b > 25 || temp->c > 26) error(&heap, i);
        iterator = ArrayHeapIteratorNext(iterator);
    }
    iterator = ArrayHeapGetReverseIterator(heap);
    for (unsigned int i = 0; i < heap->Size; i++) {
        Test *temp = (Test *)ArrayHeapIteratorGetValue(iterator);
        if (temp->a > 24 || temp->b > 25 || temp->c > 26) error(&heap, i);
        iterator = ArrayHeapIteratorPrevious(iterator);
    }
    ArrayHeapDelete(&heap);
    return 0;
}

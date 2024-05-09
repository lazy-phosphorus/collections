#include "common.h"

int main() {
    LinkedHeap *heap = LinkedHeapNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedHeapPush(heap, &test);
    }
    for (unsigned int i = 0; i < heap->Size; i++) {
        Test *temp = (Test *)LinkedHeapTop(heap);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&heap, i);
        LinkedHeapPop(heap);
    }
    LinkedHeapDelete(&heap);
    return 0;
}

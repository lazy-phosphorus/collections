#include "common.h"

int main() {
    ArrayHeap *heap = ArrayHeapNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayHeapPush(heap, &test);
    }
    for (unsigned int i = 0; i < heap->Size; i++) {
        Test *temp = (Test *)ArrayHeapTop(heap);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&heap, i);
        ArrayHeapPop(heap);
    }
    ArrayHeapDelete(&heap);
    return 0;
}

#include "common.h"

int main() {
    LinkedList *list = LinkedListNew(sizeof(Test), compare), *slice = NULL;
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedListPushBack(list, &test);
    }
    slice = LinkedListSlice(list, 10, list->Size - 10);
    for (unsigned int i = 0; i < slice->Size; i++) {
        Test *temp = (Test *)LinkedListGet(slice, i);
        if (temp->a != i + 10 || temp->b != i + 11 || temp->c != i + 12) {
            LinkedListDelete(&list);
            error(&slice, i);
        }
    }
    LinkedListDelete(&slice);
    LinkedListDelete(&list);
    return 0;
}

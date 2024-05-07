#include "common.h"

int main() {
    ArrayList *list = ArrayListNew(10, sizeof(Test), compare), *slice = NULL;
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayListPushBack(list, &test);
    }
    slice = ArrayListSlice(list, 10, list->Size - 10);
    for (unsigned int i = 0; i < slice->Size; i++) {
        Test *temp = (Test *)ArrayListGet(slice, i);
        if (temp->a != i + 10 || temp->b != i + 11 || temp->c != i + 12) {
            ArrayListDelete(&list);
            error(&slice, i);
        }
    }
    ArrayListDelete(&slice);
    ArrayListDelete(&list);
    return 0;
}

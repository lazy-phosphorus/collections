#include "common.h"

int main() {
    ArrayList *list = ArrayListNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayListInsert(list, list->Size / 2, &test);
    }
    for (unsigned int i = 0; i < list->Size; i += 2) {
        Test *temp = (Test *)ArrayListGet(list, list->Size - 1 - i / 2);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, list->Size - 1 - i / 2);
        if (i == list->Size - 1) break;
        temp = (Test *)ArrayListGet(list, i / 2);
        if (temp->a != i + 1 || temp->b != i + 2 || temp->c != i + 3)
            error(&list, i / 2);
    }
    ArrayListDelete(&list);
    return 0;
}

#include "common.h"

int main() {
    ArrayList *list = ArrayListNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayListPushBack(list, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test test = *(Test *)ArrayListGet(list, i);
        test.a *= 2;
        test.b *= 2;
        test.c *= 2;
        ArrayListSet(list, i, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)ArrayListGet(list, i);
        if (temp->a != i * 2 || temp->b != (i + 1) * 2 ||
            temp->c != (i + 2) * 2)
            error(&list, i);
    }
    ArrayListDelete(&list);
    return 0;
}

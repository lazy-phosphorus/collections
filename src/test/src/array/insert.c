#include "common.h"

int main() {
    Array *array = ArrayNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayInsert(array, array->Size / 2, &test);
    }
    for (unsigned int i = 0; i < array->Size; i += 2) {
        Test *temp = (Test *)ArrayGet(array, array->Size - 1 - i / 2);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&array, array->Size - 1 - i / 2);
        if (i == array->Size - 1) break;
        temp = (Test *)ArrayGet(array, i / 2);
        if (temp->a != i + 1 || temp->b != i + 2 || temp->c != i + 3)
            error(&array, i / 2);
    }
    ArrayDelete(&array);
    return 0;
}
#include "common.h"

int main() {
    Array *array = ArrayNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayPushBack(array, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test test = *(Test *)ArrayGet(array, i);
        test.a *= 2;
        test.b *= 2;
        test.c *= 2;
        ArraySet(array, i, &test);
    }
    for (unsigned int i = 0; i < array->Size; i++) {
        Test *temp = (Test *)ArrayGet(array, i);
        if (temp->a != i * 2 || temp->b != (i + 1) * 2 ||
            temp->c != (i + 2) * 2)
            error(&array, i);
    }
    ArrayDelete(&array);
}
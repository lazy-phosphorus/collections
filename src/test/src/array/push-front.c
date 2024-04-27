#include "common.h"

int main() {
    Array *array = ArrayNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayPushFront(array, &test);
    }
    for (unsigned int i = 0; i < array->Size; i++) {
        Test *temp = (Test *)ArrayGet(array, i);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&array, i);
    }
    ArrayDelete(&array);
    return 0;
}
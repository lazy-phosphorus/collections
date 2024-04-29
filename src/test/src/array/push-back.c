#include "array.h"
#include "common.h"

int main() {
    Array *array = ArrayNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayPushBack(array, &test);
    }
    for (unsigned int i = 0; i < array->Size; i++) {
        Test *temp = (Test *)ArrayGet(array, i);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&array, i);
    }
    ArrayDelete(&array);
    return 0;
}
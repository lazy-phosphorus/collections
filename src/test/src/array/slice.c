#include "common.h"

int main() {
    Array *array = ArrayNew(10, sizeof(Test), compare), *slice = NULL;
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayPushBack(array, &test);
    }
    slice = ArraySlice(array, 10, array->Size - 10);
    for (unsigned int i = 0; i < slice->Size; i++) {
        Test *temp = (Test *)ArrayGet(slice, i);
        if (temp->a != i + 10 || temp->b != i + 11 || temp->c != i + 12) {
            ArrayDelete(&array);
            error(&slice, i);
        }
    }
    ArrayDelete(&slice);
    ArrayDelete(&array);
    return 0;
}
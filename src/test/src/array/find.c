#include "common.h"

int main() {
    Array *array = ArrayNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayPushBack(array, &test);
    }
    for (unsigned int i = 0; i < array->Size; i++) {
        Test temp = {i, i + 1, i + 2};

        if (ArrayFind(array, &temp) != i) error(&array, i);
    }
    ArrayDelete(&array);
    return 0;
}
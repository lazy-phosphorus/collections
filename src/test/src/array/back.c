#include "common.h"

int main() {
    Array* array = ArrayNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayPushBack(array, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)ArrayBack(array);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&array, i);
        ArrayPopBack(array);
    }
    ArrayDelete(&array);
    return 0;
}
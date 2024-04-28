#include "common.h"

int main() {
    Array* array = ArrayNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayPushBack(array, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)ArrayFront(array);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&array, 0);
        ArrayPopFront(array);
    }
    ArrayDelete(&array);
}
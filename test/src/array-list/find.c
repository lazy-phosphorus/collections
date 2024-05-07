#include "common.h"

int main() {
    ArrayList *list = ArrayListNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayListPushBack(list, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test temp = {i, i + 1, i + 2};
        if (ArrayListFind(list, &temp) != i) error(&list, i);
    }
    ArrayListDelete(&list);
    return 0;
}

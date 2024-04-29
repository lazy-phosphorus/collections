#include "common.h"

int main() {
    ArrayList* list = ArrayListNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayListPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)ArrayListFront(list);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, 0);
        ArrayListPopFront(list);
    }
    ArrayListDelete(&list);
    return 0;
}

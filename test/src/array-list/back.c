#include "common.h"

int main() {
    ArrayList* list = ArrayListNew(10, sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayListPushBack(list, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test* temp = (Test*)ArrayListBack(list);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&list, i);
        ArrayListPopBack(list);
    }
    ArrayListDelete(&list);
    return 0;
}

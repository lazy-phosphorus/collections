#include "common.h"
#include "delist.h"

int main() {
    Delist *list = DelistNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        DelistPushBack(list, &test);
    }
    for (unsigned int i = 0; i < list->Size; i++) {
        Test *temp = (Test *)DelistGet(list, i);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&list, i);
    }
    DelistDelete(&list);
    return 0;
}
#include "common.h"

int main() {
    AvlTree *tree = AvlTreeNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        AvlTreeInsert(tree, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test test = {i, 0, 0};
        Test *temp = AvlTreeFind(tree, &test);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&tree, i);
    }
    AvlTreeDelete(&tree);
    return 0;
}
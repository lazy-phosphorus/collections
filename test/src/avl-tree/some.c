#include "common.h"

static Bool test(const void *value) {
    Test *temp = (Test *)value;
    return temp->a == 0;
}

int main() {
    AvlTree *tree = AvlTreeNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        AvlTreeInsert(tree, &test);
    }
    if (AvlTreeSome(tree, test) != TRUE) error(&tree, 0);
    AvlTreeDelete(&tree);
    return 0;
}

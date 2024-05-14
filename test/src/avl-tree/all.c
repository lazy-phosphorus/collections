#include "common.h"

static Bool test(const void *value) {
    Test *test = (Test *)value;
    return test->a > 0;
}

int main() {
    AvlTree *tree = AvlTreeNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        AvlTreeInsert(tree, &test);
    }
    if (AvlTreeAll(tree, test) != FALSE) error(&tree, 0);
    AvlTreeDelete(&tree);
    return 0;
}

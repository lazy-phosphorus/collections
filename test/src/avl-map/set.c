#include "avl-map.h"
#include "common.h"

int main() {
    AvlMap *map = AvlMapNew(sizeof(int), sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        AvlMapSet(map, &i, &test);
    }
    for (int i = 0; i < 25; i++) {
        Test *test = AvlMapGet(map, &i);
        if (test->a != i || test->b != i + 1 || test->c != i + 2)
            error(&map, i);
    }
    AvlMapDelete(&map);
    return 0;
}
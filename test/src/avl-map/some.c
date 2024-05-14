#include "common.h"

static Bool test(const void *value) {
    AvlMapPair *pair = (AvlMapPair *)value;
    return ((Test *)pair->value)->a == 24;
}

int main() {
    AvlMap *map = AvlMapNew(sizeof(int), sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        AvlMapSet(map, &i, &test);
    }
    if (AvlMapSome(map, test) != TRUE) error(&map, 0);
    AvlMapDelete(&map);
    return 0;
}

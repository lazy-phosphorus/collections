#include "common.h"

int main() {
    AvlMap *map = AvlMapNew(sizeof(int), sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        AvlMapSet(map, &i, &test);
    }

    for (int i = 0; i < 25; i++) {
        Test test = {i, i, i};
        AvlMapRemove(map, &test);
    }
    AvlMapDelete(&map);
    return 0;
}
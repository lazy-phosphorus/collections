#include "common.h"

int main() {
    ArrayStack *stack = ArrayStackNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayStackPush(stack, &test);
    }
    ArrayStackIterator iterator = ArrayStackGetIterator(stack);
    for (unsigned int i = 0; i < stack->Size; i++) {
        Test *temp = (Test *)ArrayStackIteratorGetValue(iterator);
        if (temp->a != i || temp->b != i + 1 || temp->c != i + 2)
            error(&stack, i);
        iterator = ArrayStackIteratorNext(iterator);
    }
    iterator = ArrayStackGetReverseIterator(stack);
    for (unsigned int i = 0; i < stack->Size; i++) {
        Test *temp = (Test *)ArrayStackIteratorGetValue(iterator);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&stack, i);
        iterator = ArrayStackIteratorPrevious(iterator);
    }
    ArrayStackDelete(&stack);
    return 0;
}

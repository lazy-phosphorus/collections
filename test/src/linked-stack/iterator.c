#include "common.h"

int main() {
    LinkedStack *stack = LinkedStackNew(sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedStackPush(stack, &test);
    }
    LinkedStackIterator iterator = LinkedStackGetIterator(stack);
    for (unsigned int i = 0; i < stack->Size; i++) {
        Test *temp = (Test *)LinkedStackIteratorGetValue(iterator);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&stack, i);
        iterator = LinkedStackIteratorPrevious(iterator);
    }
    LinkedStackDelete(&stack);
    return 0;
}

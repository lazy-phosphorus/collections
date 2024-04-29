#include <stdio.h>

#include "common.h"

int main() {
    LinkedStack *stack = LinkedStackNew(sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        LinkedStackPush(stack, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test *temp = (Test *)LinkedStackTop(stack);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&stack, i);
        LinkedStackPop(stack);
    }
    LinkedStackDelete(&stack);
    return 0;
}

#include "common.h"

int main() {
    ArrayStack *stack = ArrayStackNew(10, sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        ArrayStackPush(stack, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test *temp = (Test *)ArrayStackTop(stack);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&stack, i);
        ArrayStackPop(stack);
    }
    ArrayStackDelete(&stack);
    return 0;
}

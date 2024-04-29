#include <stdio.h>

#include "common.h"
#include "stack.h"

typedef enum { NUMBER, OPERATOR } OperatorType;

typedef struct {
    int value;
    OperatorType type;
} Operator;

int main() {
    Stack *stack = StackNew(sizeof(Test));
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        StackPush(stack, &test);
    }
    for (unsigned int i = 0; i < 25; i++) {
        Test *temp = (Test *)StackTop(stack);
        if (temp->a != 24 - i || temp->b != 25 - i || temp->c != 26 - i)
            error(&stack, i);
        StackPop(stack);
    }
    StackDelete(&stack);
    return 0;
}
#include "common.h"

static int inorder(AvlTree **const restrict tree,
                   AvlTreeNode *const restrict node, const unsigned int i) {
    unsigned int index = 0;
    if (node == NULL) return i;

    index = inorder(tree, node->left, i);
    Test *temp = (Test *)node->value;
    if (node->parent != NULL && node->parent->left != node &&
        node->parent->right != node)
        error(tree, temp->a);
    if (temp->a != index || temp->b != index + 1 || temp->c != index + 2)
        error(tree, index);

    return inorder(tree, node->right, index + 1);
}

int main() {
    AvlTree *tree = AvlTreeNew(sizeof(Test), compare);
    for (int i = 0; i < 25; i++) {
        Test test = {i, i + 1, i + 2};
        AvlTreeInsert(tree, &test);
    }
    inorder(&tree, tree->root, 0);
    AvlTreeDelete(&tree);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

static int deepness(tree_node *tree)
{
    if (tree == NULL) return 0;

    int left = 1 + deepness(tree->left);
    int right = 1 + deepness(tree->right);

    return (left > right) ? left : right;
}
int is_avl_tree(tree_node *tree)
{
    if (tree == NULL) return 1;
    int left = 1 + is_avl_tree(tree->left);
    int right = 1 + is_avl_tree(tree->right);

    int diff = left - right;

    if (left == 1 || right == 1 || diff > 1 || diff < -1) return 0;

    return (left > right) ? left : right;
}

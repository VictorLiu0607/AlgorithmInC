#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

tree_node *make_empty(tree_node *T)
{
    if (T != NULL)
    {
        make_empty(T->left);
        make_empty(T->right);
        free(T);
    }
    return NULL;
}

tree_node *insert(tree_node *T, void *element, compare_func compare)
{
    if (T == NULL)
    {
        T = malloc(sizeof(tree_node));
        if (T == NULL)
        {
            printf("Out of memory!\n");
            exit(-1);
        }
        T->left = NULL;
        T->right = NULL;
        T->element = element;
    }
    else
    {
        int bigger = compare(element, T->element);
        if (bigger > 0)
        {
            T->right = insert(T->right, element, compare);
        }
        else if (bigger < 0)
        {
            T->left = insert(T->left, element , compare);
        }
        else
        {
            //TODO: Same value, use counter or just ignore this element?
        }
    }
    return T;
}

tree_node *find(tree_node *search_tree, void * element, compare_func compare)
{
    if (search_tree == NULL)
    {
        return NULL;
    }
    int bigger = compare(element, search_tree->element);
    if (bigger > 0)
    {
        return find(search_tree->right, element, compare);
    }
    else if (bigger < 0)
    {
        return find (search_tree->left, element, compare);
    }
    else
    {
        return search_tree;
    }
}

static int is_binary_search_tree_with_range(tree_node *T, int has_max, void* max,
        int has_min, void *min, compare_func compare)
{
    if (T == NULL)
    {
        return 1;
    }
    if (T->left != NULL
            && !(compare(T->element, T->left->element) > 0
                && (!has_min || compare(T->left->element, min) > 0 ) ) )
    {
        return 0;
    }
    if (T->right != NULL
            && !(compare(T->right->element, T->element) > 0
                && (!has_max || compare(max, T->right->element) > 0 ) ) )
    {
        return 0;
    }
    return is_binary_search_tree_with_range(T->left, 1, T->element, has_min, min, compare)
        && is_binary_search_tree_with_range(T->right, has_max, max, 1, T->element, compare);

}

int get_deep(tree_node *root)
{
    static int i = 0;
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        int left = get_deep(root->left);
        int right = get_deep(root->right);
        return max(left, right) + 1;
    }
}

int is_binary_search_tree(tree_node *T, compare_func compare)
{
    return is_binary_search_tree_with_range(T, 0, NULL, 0, NULL, compare);
}

static tree_node *get_min_node(tree_node *T)
{
    if (T == NULL || T->left == NULL)
    {
        return T;
    }
    else
    {
        return get_min_node(T->left);
    }
}

static tree_node *get_max_node(tree_node *T)
{
    if (T == NULL || T->right == NULL)
    {
        return T;
    }
    else
    {
        return get_max_node(T->right);
    }
}

tree_node *delete(void *element, tree_node *root, compare_func compare)
{
    tree_node *node_to_delete;
    static int left_tree = 0;
    if (root == NULL)
    {
        //printf("Empty search tree while delete! Element(0x%X) not found?\n", element);
    }
    else if ( compare(element, root->element) > 0)
    {
        root->right = delete(element, root->right, compare);
    }
    else if ( compare(element, root->element) < 0)
    {
        root->left = delete(element, root->left, compare);
    }
    else if ( root->left && root->right)
    {
        node_to_delete = left_tree ? get_max_node(root->left) : get_min_node(root->right);
        root->element = node_to_delete->element;
        if (left_tree)
        {
            root->left = delete(root->element, root->left, compare);
        }
        else
        {
            root->right = delete(root->element, root->right, compare);
        }
        left_tree = !left_tree;
    }
    else
    {
        node_to_delete = root;
        root = root->left ? root->left : root->right;
        free(node_to_delete);
    }
    return root;
}

static int count_node(tree_node *T)
{
    if (T != NULL)
    {
        return 1 + count_node(T->left) + count_node(T->right);
    }
    return 0;
}

tree_node **level_order(tree_node *root, int *length)
{
    int count = count_node(root);
    tree_node **heap;
    tree_node **front;
    tree_node **end;
    if (length) *length = count;
    if (count == 0) return NULL;

    heap = malloc(count*sizeof(tree_node*));
    memset(heap, 0, count*sizeof(tree_node*));
    front = end = heap;

    *end = root;
    end++;

    while(end != front)
    {

        if ((*front)->left)
        {
            *end = (*front)->left;
            end++;
        }
        if ((*front)->right)
        {
            *end = (*front)->right;
            end++;
        }

        front++;
    }
    return heap;
}

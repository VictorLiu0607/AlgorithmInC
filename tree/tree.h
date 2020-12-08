#ifndef TREE_H
#define TREE_H
typedef struct tree_node {
    struct tree_node * left;
    struct tree_node * right;
    void *element;
} tree_node;

typedef int (*compare_func)(void *element1, void *element2);
extern tree_node *make_empty(tree_node *T);
extern tree_node *find(tree_node *search_tree, void * element, compare_func compare);
extern int is_binary_search_tree(tree_node *T, compare_func compare);
extern tree_node *insert(tree_node *T, void *element, compare_func compare);
extern tree_node *delete(void *element, tree_node *root, compare_func compare);
extern int is_avl_tree(tree_node *T);
extern int get_deep(tree_node *T);
extern tree_node **level_order(tree_node *root, int *length);
#endif

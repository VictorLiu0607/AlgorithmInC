#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "sha1.h"

int compare(void *element1, void *element2)
{
    return (int)element1 - (int)element2;
}

static tree_node * make_random_tree(int how_many, int mask)
{
    tree_node *root = malloc(sizeof(tree_node));
    root->left = NULL;
    root->right = NULL;
    root->element = (void *)(rand() & mask);
    for (;how_many > 0; how_many--)
    {
        int value = rand() & mask;
        root = insert(root, (void*)value, compare);
    }
    return root;
}

int node_count(tree_node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return node_count(root->left) + node_count(root->right) + 1;
    }
}

void print_tree_info(tree_node *root)
{
    if (root == NULL)
    {
        printf("==== Tree Infomations: ====\n");
        printf("empty root\n");
        printf("===========================\n");
        return;
    }

    printf("==== Tree Infomations: ====\n");
    printf("with deepness: %d\n", get_deep(root));
    printf(" which left deepness is: %d\n", get_deep(root->left));
    printf(" which right deepness is: %d\n", get_deep(root->right));
    printf("with total %d node(s)\n", node_count(root));
    printf(" which left have %d node(s)\n", node_count(root->left));
    printf(" which right have %d node(s)\n", node_count(root->right));
    printf("===========================\n");
}

void print_tree(tree_node *root, int stair, char * prefix)
{
    int i = 0;
    for (i = 0; i < stair; i++)
    {
        if (i == stair - 1)
            printf("--|-");
        else
            printf("----");
    }
    printf("%s", prefix);
    if (root == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("(%X)\n", root->element);
        if (root->left != NULL)
        {
            print_tree(root->left, stair+1, "LEFT---");
        }
        if (root->right != NULL)
        {
            print_tree(root->right, stair+1, "RIGHT--");
        }
    }
}


int main (int argc, char* argv[])
{
    tree_node * root = make_random_tree(60000, 0xFFFF);
    if (is_binary_search_tree(root, compare) )
    {
        printf("is binary search tree\n");
    }
    else
    {
        printf("is NOT binary search tree\n");
    }
    printf("initialized a tree:\n");
    print_tree_info(root);

    int deep;
    tree_node** heap= level_order(root, &deep);
    int i;
    for (i=0; i < deep; i++)
    {
        printf("->%x",heap[i]->element);
    }
    printf("\n");

    //printf("delete some element!\n");
    //int i;
    //for (i = 0; i < 0xF23451; i++)
    //{
    //    delete((void *)((i * 1000 + 5555) & 0xFFFF), root, compare);
    //}

    //printf("is avl tree: %d\n", is_avl_tree(root));

    //print_tree_info(root);
    return 0;
}


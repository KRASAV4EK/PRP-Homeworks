#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"

int main()
{
    node_t *tree = NULL;
    tree = graph_fill(tree);

    printf("Printing all tree:\n");
    graph_print(tree);

    int counter = graph_size(tree, 0);
    printf("Number of tree nodes: %d\n", counter);

    int depth = graph_depth(tree);
    printf("Max tree depth: %d\n", depth);

    int max = get_max(tree, tree->value);
    printf("Max number: %d\n", max);

    int min = get_min(tree, tree->value);
    printf("Min number: %d\n", min);

    printf("Print tree by depth row:\n");
    graph_tree_print(tree);

    return 0;
}

node_t *graph_fill(node_t *node)
{
    FILE *f = fopen("input.txt", "r");
    file_check(f);

    while (!feof(f))
    {
        int number;
        int ret = fscanf(f, "%d", &number);

        if (ret == -1 && !feof(f))
        {
            fprintf(stderr, "Wrong number!\n");
            exit(1);
        }
        else if (ret == -1 && feof(f))
            break;

        if (node == NULL)
            node = graph_insert(number, NULL);

        else
            graph_insert(number, node);
    }

    return node;

    fclose(f);
}

node_t *graph_insert(int value, node_t *node)
{
    if (node == NULL)
        return new_node(value);

    else
    {
        if (value <= node->value)
            node->left = graph_insert(value, node->left);

        else
            node->right = graph_insert(value, node->right);

        return node;
    }
}

node_t *new_node(int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (!node)
    {
        fprintf(stderr, "Error while alloc memory!\n");
        exit(1);
    }

    node->value = value;
    node->left = node->right = NULL;
    return node;
}

void graph_print(node_t *node)
{
    if (node)
    {
        graph_print(node->left);
        printf("%d\n", node->value);
        graph_print(node->right);
    }
}

int graph_size(node_t *node, int counter)
{
    if (node)
    {
        counter += 1;
        counter = graph_size(node->left, counter);
        counter = graph_size(node->right, counter);
    }

    return counter;
}

int graph_depth(node_t *node)
{
    if (node)
    {
        int left = graph_depth(node->left);
        int right = graph_depth(node->right);
        return left > right ? left + 1 : right + 1;
    }
    else
        return 0;
}

int get_max(node_t *node, int max)
{
    if (node)
    {
        node->value > max ? max = node->value : max;
        max = get_max(node->left, max);
        max = get_max(node->right, max);
    }

    return max;
}

int get_min(node_t *node, int min)
{
    if (node)
    {
        node->value < min ? min = node->value : min;
        min = get_min(node->left, min);
        min = get_min(node->right, min);
    }

    return min;
}

void graph_tree_print(node_t *node)
{
    const int depth = graph_depth(node);

    for (int i = 0; i <= depth; ++i)
    {
        graph_line_print(i, 0, node);
        printf("\n");
    }
}

void graph_line_print(unsigned depth, unsigned cur_depth, node_t *node)
{
    if (cur_depth == depth)
    {
        if (node)
            printf("%2d ", node->value);
        else
            printf(" - ");
    }
    else if (node)
    {
        graph_line_print(depth, cur_depth + 1, node->left);
        graph_line_print(depth, cur_depth + 1, node->right);
    }
}

void file_check(FILE *f)
{
    if (!f)
    {
        fprintf(stderr, "Wrong file!\n");
        exit(1);
    }
}

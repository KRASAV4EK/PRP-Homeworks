#ifndef _TREE_H_
#define _TREE_H_

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} node_t;

void file_check(FILE *);

node_t *new_node(int);
node_t *graph_insert(int, node_t *);
node_t *graph_fill(node_t *);

void graph_print(node_t *);
int graph_size(node_t *, int);
int graph_depth(node_t *);
void graph_bst(node_t *);

int get_max(node_t *, int);
int get_min(node_t *, int);

void graph_tree_print(node_t *node);
void graph_line_print(unsigned depth, unsigned cur_depth, node_t *node);

#endif

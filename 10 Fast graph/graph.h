#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct {
   int from;
   int to;
   int cost;
} edge_t;

typedef struct {
   edge_t *edges;
   int num_edges;  
   int capacity;
} graph_t;

void print_graph(graph_t *graph);

/* Allocate a new graph and return a reference to it. */
graph_t* allocate_graph(void);

graph_t* enlarge_graph(graph_t *graph);

void print_graph(graph_t *graph);

/* Free all allocated memory and set reference to the graph to NULL. */
void free_graph(graph_t **graph);

/* Load a graph from the text file. */
void load_txt(const char *fname, graph_t *graph);
/* Load a graph from the binary file. */
void load_bin(const char *fname, graph_t *graph);

/* Save the graph to the text file. */
void save_txt(const graph_t * const graph, const char *fname);
/* Save the graph to the binary file. */
void save_bin(const graph_t * const graph, const char *fname);

/* Memory allocation check */
void graph_alloc_check(graph_t *graph);
void edge_alloc_check(edge_t *edges);

/* File check */
void file_open_check(FILE *f);

#endif // __GRAPH_H__

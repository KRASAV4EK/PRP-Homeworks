#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "graph.h"

#ifndef INIT_SIZE 
#define INIT_SIZE 10
#endif

graph_t* allocate_graph(void) 
{
   graph_t *graph = (graph_t*) malloc(sizeof(graph_t));
   assert(graph != NULL);
   graph->edges = NULL;
   graph->num_edges = 0;
   graph->capacity = 0;
   /* or we can call calloc */
   return graph;
}

void free_graph(graph_t **graph) 
{
   assert(graph != NULL && *graph != NULL);
   if ((*graph)->capacity > 0) {
      free((*graph)->edges);
   }
   free(*graph);
   *graph = NULL;
}

graph_t* enlarge_graph(graph_t *graph) 
{
   assert(graph != NULL);
   int n = graph->capacity == 0 ? INIT_SIZE : graph->capacity * 2; /* double the memory */

   edge_t *e = (edge_t*)malloc(n * sizeof(edge_t));
   assert(e != NULL);
   memcpy(e, graph->edges, graph->num_edges * sizeof(edge_t));
   free(graph->edges);
   graph->edges = e;
   graph->capacity = n;
   return graph;
}

void print_graph(graph_t *graph) 
{
   assert(graph != NULL);
   fprintf(stderr, "Graph has %d edges and %d edges are allocated\n", graph->num_edges, graph->capacity);
   edge_t *e = graph->edges;
   for (int i = 0; i < graph->num_edges; ++i, ++e) {
      printf("%d %d %d\n", e->from, e->to, e->cost);
   }
}

// Read from nonbinary file
static int read_func(FILE *f)
{
	char number[10];
	char get_char = fgetc(f);
	int idx = -1;

	while(get_char != ' ') 
   {
      idx++;
		number[idx] = get_char;
		get_char = fgetc(f);

		if(get_char == EOF) return -1;
		
		if(get_char == 10 || get_char == -1) break;
	}

	number[idx + 1] = '\0';
   
   // Create a string from input
   char *str = number;
	int final_number = 0;

   // Convert string into integer
   while (*str)
   {
      final_number = final_number * 10 + (*str++ - '0');
   }
   
	return final_number;
}

// - function faster reading input
void load_txt(const char *fname, graph_t *graph)
{
   FILE *file_txt = fopen(fname, "r");
   file_open_check(file_txt);

   int output = 0;

   // Go trhough every string in the file
   while (!feof(file_txt) && !output)
   {
      // Enlarge capacity of graph if it's needed
      if (graph->num_edges == graph->capacity)
         enlarge_graph(graph);
   
      edge_t *e = graph->edges + graph->num_edges;

      int from = 0;
      int to = 0;
      int price = 0;
      
      // Read info from the string
      while (!feof(file_txt) && graph->num_edges < graph->capacity)
      {
         from = read_func(file_txt);
         to = read_func(file_txt);
         price = read_func(file_txt);

         // Check on end of file
         if (from < 0 || to < 0 || price < 0)
         {
            output = 1;
            break;
         }

         e->from = from;
         e->to = to;
         e->cost = price;

         graph->num_edges += 1;

         e += 1;
      }
   }

   fclose(file_txt);
}

static void bin_txt_print(int current_number, FILE *f)
{
	if (current_number > 9)
   { 
		int number = current_number / 10;

		current_number -= 10 * number;
		bin_txt_print(number, f);
	}
	fputc('0'+current_number, f);
}

// - function -----------------------------------------------------------------
void save_txt(const graph_t * const graph, const char *fname)
{
   FILE *saved_txt = fopen(fname, "w");
   file_open_check(saved_txt);

	edge_t *e = graph->edges;

   for (int i = 0; i < graph->num_edges; i++, e++)
   {
      bin_txt_print(e->from, saved_txt);
      fputc(' ', saved_txt);

      bin_txt_print(e->to, saved_txt);
      fputc(' ', saved_txt);

      bin_txt_print(e->cost, saved_txt);
      fputc('\n', saved_txt);
	}

   fclose(saved_txt);
}

static int load_big_endian(FILE *f) 
{
   uint32_t a;

   if(fread(&a, sizeof(uint32_t), 1, f) != 1 ) return -1;

   return ntohl(a);
}

// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *graph)
{
   FILE *f = fopen(fname, "rb");
   file_open_check(f);

   if (graph->num_edges == graph->capacity)
      enlarge_graph(graph);

   while(!feof(f)) 
   {
      edge_t *e = graph->edges + graph->num_edges;

      if(graph->num_edges < graph->capacity) 
      {
         int from = load_big_endian(f);
         int to = load_big_endian(f);
         int cost = load_big_endian(f);

         if(from < 0 || to < 0 || cost < 0) break;

         e->from = from;
         e->to = to;
         e->cost = cost;

         graph->num_edges += 1;
         e++;
      } 
      
      else enlarge_graph(graph);
   }
   fclose(f);
}

static void save_big_endian(int a, FILE *f)
{
   int *p1 = &a;
   char *p2 = (char *)p1; 
   char byte1 = *(p2); 
   char byte2 = *(p2+1);
   char byte3 = *(p2+2);
   char byte4 = *(p2+3);

   fputc(byte4,f);
   fputc(byte3,f);
   fputc(byte2,f);
   fputc(byte1,f);
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname)
{
   FILE *f = fopen(fname, "wb");
   file_open_check(f);

   edge_t *e = graph->edges;

      for (int i = 0; i < graph->num_edges; ++i, ++e) 
      {
         save_big_endian(e->from ,f);
         save_big_endian(e->to ,f);
         save_big_endian(e->cost ,f);
      }

   fclose(f);
}

void graph_alloc_check(graph_t *graph)
{
   if (!graph)
   {
      fprintf(stderr, "Error: Graph memory allocation!\n");
      exit(1);
   }
}

void edge_alloc_check(edge_t *edges)
{
   if (!edges) 
   {
      fprintf(stderr, "Error: Edges memory allocation!\n");
      exit(1);
   }
}

void file_open_check(FILE *f)
{
   if (!f)
   {
      fprintf(stderr, "Error: Wrong file!\n");
      exit(1);
   }
}

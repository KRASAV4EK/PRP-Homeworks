#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"

/* This is a testing file just to be able to compile the 
 * examples of binary files to convert graph from txt->bin
 * and bin -> txt
 */

// 2x Enlarge capacity of graph
static void enlarge_graph(graph_t *graph)
{
   graph->capacity = graph->capacity * 2;

   edge_t *e = realloc(graph->edges, graph->capacity * sizeof(edge_t));
   edge_alloc_check(e);

   graph->edges = e;
}

// - function -----------------------------------------------------------------
graph_t* allocate_graph() 
{
   graph_t *graph = (graph_t*)malloc(sizeof(graph_t));
   graph_alloc_check(graph);

   graph->capacity = 100;
   graph->num_edges = 0;

   edge_t *e = (edge_t*)malloc(graph->capacity * sizeof(edge_t));
   edge_alloc_check(e);

   graph->edges = e;
   return graph;
}

// - function -----------------------------------------------------------------
void free_graph(graph_t **graph)
{
   if ((*graph)->capacity > 0)
      free((*graph)->edges);

   free(*graph);
   *graph = NULL;
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

// - function -----------------------------------------------------------------
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
         e->price = price;

         graph->num_edges += 1;

         e += 1;
      }
   }

   fclose(file_txt);
}

// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *graph)
{
   FILE *file_bin = fopen(fname, "r");
   file_open_check(file_bin);

   // Enlarge capacity of graph if it's needed
   if (graph->num_edges == graph->capacity)
      enlarge_graph(graph);

   // Go trhough every string in the file
   while (!feof(file_bin))
   {
      edge_t *e = graph->edges + graph->num_edges;

      if (graph->num_edges < graph->capacity)
      {
         if (fread(e, sizeof(edge_t), 1, file_bin) != 1) break;

         graph->num_edges += 1;
         e++;
      }

      else
         enlarge_graph(graph);
   }
   
   fclose(file_bin);
}

// Save info from binary file to txt
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

   for (unsigned i = 0; i < graph->num_edges; i++, e++)
   {
      bin_txt_print(e->from, saved_txt);
      fputc(' ', saved_txt);

      bin_txt_print(e->to, saved_txt);
      fputc(' ', saved_txt);

      bin_txt_print(e->price, saved_txt);
      fputc('\n', saved_txt);
	}

   fclose(saved_txt);
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname)
{
   FILE *saved_bin = fopen(fname, "wb");
   file_open_check(saved_bin);

   edge_t *e = graph->edges;

   for (unsigned i = 0; i < graph->num_edges; i++, e++)
   {
      fwrite(&e->from, sizeof(e->from), 1, saved_bin);
      fwrite(&e->to, sizeof(e->to), 1, saved_bin);
      fwrite(&e->price, sizeof(e->price), 1 , saved_bin);
   }
   
   fclose(saved_bin);
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

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int from;
    int to;
    int price;
} graph_t;


int main(int argc, char const *argv[])
{
    graph_t graph;
    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        fprintf(stderr, "ffff\n");
        exit(1);
    }

    int r;
    r = fscanf(f, "%d %d %d", &graph.from, &graph.to, &graph.price);
    if (r == -1)
    {
        fprintf(stderr, "rrrr\n");
        exit(1);
    }
    fclose(f);

    FILE *file = fopen(argv[2], "w");
    if (!file)
    {
        fprintf(stderr, "ffff2222\n");
        exit(1);
    }

    fwrite(&graph.from, sizeof(int), 1, file);
    fputc(' ', file);
    fwrite(&graph.to, sizeof(int), 1, file);
    fputc(' ', file);
    fwrite(&graph.price, sizeof(int), 1, file);
    fputc('\n', file);

    fclose(file);

    return 0;
}

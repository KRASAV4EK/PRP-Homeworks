#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef LENGHT
#define LENGHT 20
#endif

#ifndef MAX
#define MAX 100
#endif

void fill_arr(int *, int, int);
void save_txt(int *);

int main(int argc, char *argv[])
{   
    int array[LENGHT];

    srand(time(NULL));
    fill_arr(array, MAX, 0);

    save_txt(array);

    printf("\033[01;32m\033[KInput created succesfully!\033[m\033[K\n");

    return 0;
}

void fill_arr(int *array, int max, int counter)
{
    if (counter != LENGHT)
    {
        array[counter] = rand() % max;
        for (unsigned i = 0; i < counter; i++)
        {
            if (array[counter] == array[i])
                fill_arr(array, max, counter);
        }

        counter += 1;

        fill_arr(array, max, counter);
    }
}

void save_txt(int *array)
{
    FILE *f = fopen("input.txt", "w");

    for (unsigned i = 0; i < LENGHT; i++)
        fprintf(f, "%d\n", array[i]);
    
    fclose(f);
}

#include <stdio.h>
#include <stdlib.h>

#define MIN 3
#define MAX 69
#define ERROR_INPUT 100
#define ERROR_RANGE 101
#define ERROR_HOUSE_RANGE 102
#define ERROR_FENCE_RANGE 103

int input_check();
int range_check(int, int);
int width_size_check(int);
int fence_size_check(int, int);
void roof(int);
void basement_without_fence(int, int);
void basement_with_fence(int, int, int);

int main()
{
    // Input
    int house_width = input_check();
    int house_height = input_check();
    int fence_size = 1;

    if (house_width == house_height)
    {
        fence_size = input_check();
    }
    
    // Control
    range_check(house_width, house_height);
    width_size_check(house_width);
    fence_size_check(fence_size, house_width);

    // Roof
    roof(house_width);

    // Basement
    if (house_width == house_height)
    {
        basement_with_fence(house_width, house_height, fence_size);
    }
    else
    {
        basement_without_fence(house_width, house_height);
    }
    return EXIT_SUCCESS;
}

int input_check()
{
    // Checking, if input is integer
    int amount;
    if (scanf("%i", &amount) != 1)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(ERROR_INPUT);
    }
    return amount;
}

int range_check(int house_width, int house_height)
{
    // Checking right range
    if (house_width < MIN || house_width > MAX || 
        house_height < MIN || house_height > MAX)
    {
        fprintf(stderr, "Error: Vstup mimo interval!\n");
        exit(ERROR_RANGE);
    }
    return EXIT_SUCCESS;
}

int width_size_check(int house_width)
{
    // Checking, if width is odd
    if (house_width % 2 != 1)
    {
        fprintf(stderr, "Error: Sirka neni liche cislo!\n");
        exit(ERROR_HOUSE_RANGE);
    }
    return EXIT_SUCCESS;
}

int fence_size_check(int fence_size,int house_width)
{
    if (fence_size >= house_width || fence_size <= 0)
    {
        fprintf(stderr, "Error: Neplatna velikost plotu!\n");
        exit(ERROR_FENCE_RANGE);
    }
    return EXIT_SUCCESS;
}

void roof(int house_width)
{
    for (int row = house_width / 2 + 1; row < house_width; row++)
    {
        for (int col = 1; col <= house_width; col++)
        {
            // Building right roof side
            if (row == col && row > house_width / 2)
            {
                putchar('X');
                break;
            }

            // Building left roof side
            else if (row == house_width + 1 - col)
            {
                putchar('X');
            }

            else
            {
                putchar(' ');
            }
        }
        putchar('\n');
    }
}

void basement_without_fence(int house_width, int house_height)
{
    for (int row = 1; row <= house_height; row++)
    {
        for (int col = 1; col <= house_width; col++)
        {
            // Building floor, ceiling and walls
            if (row == 1 || row == house_height ||
                col == 1 || col == house_width)
            {
                putchar('X');
            }           
            else {putchar(' ');}
        }
        putchar('\n');
    }
}

void basement_with_fence(int house_width, int house_height, int fence_size)
{
    // If fence size is even, then
    char floor_odd_symbol = '-';
    char floor_even_symbol = '|';
    char walls_odd_symbol = ' ';
    char walls_even_symbol = '|';
    int number = 0;

    if (fence_size % 2 == 1)
    {
        floor_odd_symbol = '|';
        floor_even_symbol = '-';
        walls_odd_symbol = '|';
        walls_even_symbol = ' ';
    }

    for (int row = 1; row <= house_height; row++)
    {
        // Building floor and ceiling
        if (row == 1 || row == house_height)
        {
            for (int col = 1; col <= house_width; col++)
            {
                putchar('X');
            }
        }

        // Building walls
        if (row != 1 && row != house_height)
        {
            putchar('X');
            for (int col = 2; col < house_width; col++)
            {
                if (number == 0)
                {
                    number = 1;
                    putchar('o');
                }
                else
                {
                    number = 0;
                    putchar('*');
                }
            }
            putchar('X');
        }

        // Building first and last fence rows
        if (row == house_height - fence_size + 1 || row == house_height)            
        {
            for (int col = 1; col <= fence_size; col++)
            {
                if (col % 2 == 0)
                {
                    putchar(floor_even_symbol);
                }
                else
                {
                    putchar(floor_odd_symbol);
                }
            }
        }

        // Building fence rows
        else if (row > house_height - fence_size + 1)
        {
            for (int col = 1; col <= fence_size; col++)
            {
                if (col % 2 == 0)
                {
                    putchar(walls_even_symbol);
                }
                else
                {
                    putchar(walls_odd_symbol);
                }
            }
        }
        putchar('\n');
    }
}

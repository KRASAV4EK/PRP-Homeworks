/*
sign2 = 'A'
while sign_2 != \0 && sign1 != '+'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void array_filling(int ***, int *, int *, char *);
void memory_check(int **);

void action_and_print(int **, int, int, int **, int, int, char, int ***);
void plus_minus(char, int **, int, int, int **, int, int);
void multiplication(int **, int, int, int **, int, int, int ***);

void printing(int **, int, int);
void cleaning(int **, int**);
void error_exit();

int main()
{
    // Creating the pointer to the first matrix
    int **matrix_1 = NULL;
    int rows_1, cols_1;
    char sign_1;

    // Creating the pointer to the second matrix
    int **matrix_2 = NULL;
    int rows_2, cols_2;
    char sign_2;
    
    array_filling(&matrix_1, &rows_1, &cols_1, &sign_1);

    array_filling(&matrix_2, &rows_2, &cols_2, &sign_2);

    if (sign_2 == '+' || sign_2 == '-' || sign_2 == '*')
    {
        
    }

    int **matrix_3 = NULL;

    action_and_print(matrix_1, rows_1, cols_1, \
                     matrix_2, rows_2, cols_2, sign_1, &matrix_3);

    cleaning(matrix_1, matrix_2);

    return 0;
}

void array_filling(int ***matrix_pointer, int *rows_amount, int *cols_amount, \
                   char *sign1)
{
    char *input_string = malloc(sizeof(int)); // Array for input
    if (input_string == NULL) exit(1);

    int **matrix = NULL; // Points on matrix
    int *start = NULL; // Points at the beginning of the strings

    int matrix_number_counter = 0; // Counter all numbers in matrix

    int counter = -3; // Number counter in string
    int rows, cols;
    char sign = '\0';
    int input_lenght = 1; // Default lenght of input string
    int rows_counter = 0; // Counter for matrix strings

    while (scanf("%s", input_string) != EOF)
    {
        if (atoi(input_string) == 0 && input_string[0] != '0' && \
            input_string[1] != '\0')
        {
            free(input_string);
            free(matrix);
            error_exit();
        }        
        
        // Saving matrix row and col
        if (counter == -3 || counter == -2)
        {
            if (counter == -3)
            {
                rows = atoi(input_string);
                counter += 1;
                continue;
            }
            cols = atoi(input_string);
            counter += 1;
            continue;
        }

        // Saving sign
        if ((input_string[0] == '-' || input_string[0] == '+' || \
             input_string[0] == '*') && input_string[1] == '\0') 
        {
            // Exit from program if amount of numbers is smaller than matrix size
            if (matrix_number_counter < rows * cols) 
            {
                free(matrix);
                free(input_string);
                error_exit();
            }

            sign = input_string[0];
            break;
        }
        
        // Updating size of input array
        if (input_lenght < strlen(input_string))
        {
            input_lenght = strlen(input_string);
            input_string = realloc(input_string, sizeof(int) * input_lenght);
            if (input_string == NULL) exit(1);
        }

        // Memory allocation for matrix
        if (counter == -1)
        {
            // Allocation memory for each string and column
            matrix = (int **)calloc(rows * cols, sizeof(int *) * rows + \
                                    rows * cols * sizeof(int));
            memory_check(matrix);
            start = (int *)((char *)matrix + rows * sizeof(int *));
            for (int col = 0; col < rows; col++)
                matrix[col] = start + col * cols;
            counter = 0;
        }

        // Exit from program if amount of numbers is bigger than size of matrix
        if (rows * cols == matrix_number_counter) 
        {
            free(input_string);
            free(matrix);
            error_exit();
        }

        // Start filling next string, if was full
        if (counter == cols) {counter = 0; rows_counter += 1;}

        // Filling matrix with input numbers
        matrix[rows_counter][counter] = atoi(input_string);
        matrix_number_counter += 1;
        counter += 1;
    }

    free(input_string);

    // Saving 
    *rows_amount = rows;
    *cols_amount = cols;
    *sign1 = sign;
    *matrix_pointer = matrix;
}

void action_and_print(int **matrix_1, int rows_1, int cols_1, \
       int **matrix_2, int rows_2, int cols_2, char sign_1, int ***matrix_3)
{
    if (sign_1 == '+' || sign_1 == '-')
    {
        plus_minus(sign_1, matrix_1, rows_1, cols_1, matrix_2, rows_2, cols_2);
        printing(matrix_1, rows_1, cols_1);
    }

    else if (sign_1 == '*')
    {
        multiplication(matrix_1, rows_1, cols_1, matrix_2, rows_2, cols_2, 
                       matrix_3);
        printing(*matrix_3, rows_1, cols_2);
        free(*matrix_3);
    }
}

void plus_minus(char sign, int **matrix_1, int rows_1, int cols_1, \
                int **matrix_2, int rows_2, int cols_2)
{
    // Checking if operations '+' or '-' can be done
    if (rows_1 != rows_2 || cols_1 != cols_2) 
    {
        cleaning(matrix_1, matrix_2);
        error_exit();
    }

    for (int row = 0; row < rows_1; row++)
    {
        for (int col = 0; col < cols_1; col++)
        {
            if (sign == '+') matrix_1[row][col] += matrix_2[row][col];
            else matrix_1[row][col] -= matrix_2[row][col];
        }
    }
}

void multiplication(int **matrix_1, int rows_1, int cols_1, \
                    int **matrix_2, int rows_2, int cols_2, \
                    int ***matrix_pointer)
{
    if (cols_1 != rows_2) {cleaning(matrix_1, matrix_2); error_exit();}

    int **matrix = NULL; // Pointer on matrix
    int *start = NULL; // Points at the beginning of the strings

    // Allocation memory for each string and column
    matrix = (int **)calloc(rows_1 * cols_2, sizeof(int *) * rows_1 + \
                            rows_1 * cols_2 * sizeof(int));
    memory_check(matrix);
    start = (int *)((char *)matrix + rows_1 * sizeof(int *));
    for (int col = 0; col < rows_1; col++)
        matrix[col] = start + col * cols_2;
    
    // Filling the array
    for (int row = 0; row < rows_1; row++)
    {
        for (int col = 0; col < cols_2; col++)
        {
            for (int k = 0; k < rows_2; k++)
                matrix[row][col] += matrix_1[row][k] * matrix_2[k][col];
        }
    }    

    *matrix_pointer = matrix;
}

void error_exit()
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    exit(100);
}

void printing(int **matrix, int rows, int cols)
{
    printf("%d %d\n", rows, cols);

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            printf("%d", matrix[row][col]);
            if (col != cols - 1) printf(" ");
        }
        printf("\n");
    }
}

void memory_check(int **matrix)
{
    if (matrix == NULL) exit(1);
}

void cleaning(int **matrix_1, int **matrix_2)
{
    free(matrix_1);
    free(matrix_2);
}

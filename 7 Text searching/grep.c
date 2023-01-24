#include <stdlib.h>
#include <stdio.h>
#include <regex.h>

void file_input(int, const char *, const char *);
void text_search(int, const char *, FILE *, int);

int arg_find(const char *);

int colored_print(const char *, char *, int);

void mem_alloc_check(char *);

int main(int argc, const char *argv[])
{
    if (argc == 4) 
    {
        int arg = arg_find(argv[1]);
        file_input(arg, argv[2], argv[3]);
    }

    else if (argc > 1 && argc < 4) file_input(0, argv[1], argv[2]);

    else if (argc > 4) 
    {
        fprintf(stderr, "Too many arguments!\n");
        return 1;
    }

    else
    {
        fprintf(stderr, "At least one argument required!\n");
        return 1;
    }
}

void file_input(int first_arg, const char *pattern, const char *filename)
{
    // Check if is some input file, if isn't then reading from normal input
    if (filename == NULL) text_search(first_arg, pattern, stdin, 0);
    else
    {
        FILE *f = fopen(filename, "r");

        if (f == NULL) {fprintf(stderr, "Wrong input file!\n"); exit(1);}

        else {text_search(first_arg, pattern, f, 1);}
    }
}

void text_search(int first_arg, const char *pattern, FILE *f, int input_flag)
{
    int pattern_size = 0; // Count pattern size
    for (int i = 0; pattern[i] != '\0'; i++) pattern_size += 1;

    int file_size = 1000; // Amount of memory to alloc for input

    // Memory alloc for file or standard input
    if (input_flag == 1)
    {
        // Count file size
        fseek(f, 0, SEEK_END);
        file_size = ftell(f);
        rewind(f);
    }

    int printed_str = 0; // Flag for exit code
    char *array = malloc(file_size);
    mem_alloc_check(array);
    char *estr;
    while (1)
    {
        // Scan string from input
        estr = fgets(array, file_size, f);

        // Check on error or input is over
        if (estr == NULL)
        {
            if ( feof (f) != 0) break;

            if ( feof (f) == 0) {fprintf(stderr, "\nReading error!\n"); break;}
        }

        // Search regular expression if is argument "-E"
        if (first_arg == 1) {continue;}

        // Function for argument "--color=always"
        if (first_arg == 2)
        {
            int str_flag;
            str_flag = colored_print(pattern, array, pattern_size);
            if (str_flag == 1) printf("\n");
            printed_str += str_flag;
            continue;
        }

        // Going through the input and searching pattern
        int pattern_counter = 0;
        for (int counter = 0; array[counter] != '\n'; counter++)
        {
            if (array[counter] == pattern[pattern_counter])
            {
                pattern_counter += 1;

                if (pattern_size == pattern_counter)
                {
                    printf ("%s", array);
                    printed_str = 1;
                    break;
                }
            }
            else pattern_counter = 0;
        }
    }
    fclose(f);

    if (printed_str >= 1) {free(array); exit(0);}
    else {free(array); exit(1);}
}

/* 
Example how colored_print is working

pattern = "eeeel"
"Abcdfg          heeeello"
 |---------------||---|
 text_arr    -    temp_arr
*/

/*
Nevim proc, ale Brute neprijima vystipni text colored_print
Vsechny moje testy mam spravne
*/

// Print text with red pattern
int colored_print(const char *pattern, char *array, int pattern_size)
{
    int temp = 100; // Amount of bytes for allocating memory
    char *temp_arr = malloc(temp); // Array with letters that can be in pattern
    mem_alloc_check(temp_arr);

    int text = 100; // Amount of bytes for allocating memory
    char *text_arr = malloc(text); // Array with letters before finded pattern
    mem_alloc_check(text_arr);

    int text_counter = 0; // Counts letters in text_arr
    int pattern_counter = 0; // Counts letters in pattern
    int temp_counter = 0; // Counts letters in temp
    int pattern_flag = 0; // If pattern found in text, then 1

    // Going trhough every letter in string
    for (int counter = 0; array[counter] != '\n'; counter++)
    {
        // Letter from text is in pattern
        if (array[counter] == pattern[pattern_counter])
        {
            // Control allocated memory
            if (pattern_counter == temp - 1)
            {
                temp *= 2;
                temp_arr = realloc(temp_arr, temp);
                mem_alloc_check(temp_arr);
            }

            // Fill temp.array with letter from text
            temp_arr[pattern_counter] = array[counter];
            pattern_counter += 1;
            temp_counter += 1;

            // Pattern finded!
            if (pattern_counter == pattern_size)
            {
                // Print all text before pattern
                if (text_counter != 0 && pattern_flag == 0)
                {
                    for (int i = 0; i < text_counter - 1; i++)
                    {
                        printf("%c", text_arr[i]);
                    }

                    // Create new clear text array
                    free(text_arr);
                    text = 100;
                    text_arr = malloc(text);
                    mem_alloc_check(text_arr);
                    text_counter = 0;
                }

                // Print colored pattern
                printf("\033[01;31m\033[K%s\033[m\033[K", pattern);

                // Create new clear temp array
                free(temp_arr);
                temp = 100;
                temp_arr = malloc(temp);
                mem_alloc_check(temp_arr);
                pattern_counter = 0;
                temp_counter = 0;

                pattern_flag = 1;
            }
        }

        // Letter from text isn't in pattern and buffer isn't empty
        else if (temp_counter != 0 && pattern_flag == 1) 
        {
            // Print buffer array
            for (int counter = 0; counter < temp_counter; counter++)
            {
                printf("%c", temp_arr[counter]);
            }
            printf("%c", array[counter]);

            // Create new clear buffer
            free(temp_arr);
            temp = 100;
            temp_arr = malloc(temp);
            mem_alloc_check(temp_arr);
            temp_counter = 0;
            pattern_counter = 0;
        }

        // Letter from text isn't in pattern and buffer is empty
        else if (pattern_flag == 1)
        {
            printf("%c", array[counter]); 
            pattern_counter = 0;
        }

        // Zeroing counter if pattern don't finded
        else pattern_counter = 0;
        
        // Filling array with text before first finded pattern
        if (pattern_flag == 0)
        {
            // Control allocated memory
            if (text_counter == text - 1)
            {
                text *= 2;
                text_arr = realloc(text_arr, text);
                mem_alloc_check(text_arr);
            }
            text_arr[text_counter] = array[counter];
            text_counter += 1;
        }


        // Buffer isn't empty and string is over
        if (array[counter + 1] == '\n' && temp_counter != 0 &&\
            pattern_flag == 1)
        {
            // Print buffer array
            for (int counter = 0; counter < temp_counter; counter++)
            {
                printf("%c", temp_arr[counter]);
            }
        }
    }
    free(text_arr);
    free(temp_arr);
    return pattern_flag;
}

int arg_find(const char *arg)
{
    char *regular = "-E";
    char *color  = "--color=always";
    
    int counter_e = 0;
    int counter_color = 0;

    for (int i = 0; arg[i] != arg[-1]; i++)
    {
        if (regular[i] != arg[i]) counter_e = 1;

        if (color[i] != arg[i]) counter_color = 1;
    }

    // If argument was "-E", then return 1
    if (counter_e == 0) return 1;

    // If argument was "--color=always", then return 2
    else if (counter_color == 0) return 2;

    return 0;
}

void mem_alloc_check(char *array)
{
    if (array == NULL) 
    {
        fprintf(stderr, "Memory allocation error!\n"); 
        exit(1);
    }
}

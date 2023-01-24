#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_ERROR 100
#define LENGHT_ERROR 101
#define ENG 52

void input_check(char);
void lenght_check(int, int);
void right_decoding(char *, char *, char *, int);
void letters_changing(char *, int);
void printing_answer(char *, int);
void cleaning(char *, char *, char *);

int main()
{
    char *coded_str = malloc(sizeof(char));
    char *decoded_str = malloc(sizeof(char));

    // Mockrat se omlouvam, nezapsal jsem ten cyklus do nejake funkce, 
    // protoze nevim, jak to mam udelat, mockrat jsem to vyskousel. 
    // Dival jsem se na hodne videa, ale nenasel jsem spravne reseni. 
    // Bylo by fajn, kdybyste jeste jednou ukazal, 
    // jak muzeme udelat dinamicke pole v nejake funkci.

    // Filling arrays with input
    char letter;
    bool end_flag = false; // Flag is true, when the first string is over
    int len_coded = 0;
    int len_decoded = 0;

    // Filling 2 arrays by input
    while ((letter = getchar()) != EOF)
    {
        // If first string is over, then start filling the second array
        if (letter == '\n') {end_flag = true; continue;}

        input_check(letter);

        if (end_flag == false)
        {
            coded_str = realloc(coded_str, (len_coded + 1) * sizeof(char));
            coded_str[len_coded] = letter;
            len_coded += 1;
            continue;
        }

        decoded_str = realloc(decoded_str, (len_decoded + 1) * sizeof(char));
        decoded_str[len_decoded] = letter;
        len_decoded += 1;
    }
    
    lenght_check(len_coded, len_decoded);

    // Creating third array, which will have right answer
    char *right_decoded_str = malloc(len_coded * sizeof(char));
    right_decoding(coded_str, decoded_str, right_decoded_str, len_coded);

    printing_answer(right_decoded_str, len_coded);
    
    cleaning(coded_str, decoded_str, right_decoded_str);

    return 0;
}

void input_check(char letter)
{
    if (!(letter >= 'a' && letter <= 'z') && 
        !(letter >= 'A' && letter <= 'Z'))
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(INPUT_ERROR);
    }
}

void lenght_check(int len_coded, int len_decoded)
{
    if (len_coded != len_decoded)
    {
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        exit(LENGHT_ERROR);
    }
}


void right_decoding(char *coded_str, char *decoded_str, \
                    char *right_decoded_str, int len_coded)
{
    int greatest_match = 0;

    // Going through all small and big letters in english alphabet
    for (int counter = 0; counter < ENG; counter++)
    {
        letters_changing(coded_str, len_coded);

        // Searching matches and saving the array with the greatest match
        int match_counter = 0;
        for (int i = 0; i < len_coded; i++)
        {
            if (coded_str[i] == decoded_str[i]) {match_counter += 1;}
        }

        if (match_counter > greatest_match) 
        {
            greatest_match = match_counter; 
            for (int n = 0; n < len_coded; n++)
            {
                right_decoded_str[n] = coded_str[n];
            }
        }
    }
}

void letters_changing(char *coded_str, int len_coded)
{
    // Going through the coded array, changing letters
    for (int number = 0; number < len_coded; number++)
    {
        char letter = coded_str[number];

        /* Changing the letter to the next one and checking 
           if its also an english letter, if not, then starting from a/A */
        if (letter >= 'A' && letter <= 'Z')
        {
            coded_str[number] = letter + 1;
            if (coded_str[number] > 'Z') coded_str[number] = 'a';
            continue;
        }

        if (letter >= 'a' && letter <= 'z')
        {
            coded_str[number] = letter + 1;
            if (coded_str[number] > 'z') coded_str[number] = 'A';
        }
    }
}

void printing_answer(char *right_decoded_str, int len_coded)
{
    for (int i = 0; i < len_coded; i++)
    {
        printf("%c", right_decoded_str[i]);
    }
    printf("\n");
}

void cleaning(char *coded_str, char *decoded_str, char *right_decoded_str)
{
    free(coded_str);
    free(decoded_str);
    free(right_decoded_str);
    coded_str = decoded_str = right_decoded_str = NULL;
}

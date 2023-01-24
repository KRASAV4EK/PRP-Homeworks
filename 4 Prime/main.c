#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 
#define MAX_PRIME 1000000
 
#define ERROR_INPUT 100
 
long input_check();
 
int main()
{
    // Creating array full of true values
    bool array_of_primes[MAX_PRIME];
    memset(array_of_primes, true, sizeof(array_of_primes));
 
    // Checking if number is prime, then true, else false
    for (int p = 2; p * p <= MAX_PRIME; p++) 
    {
        if (array_of_primes[p] == true) 
        {
            for (int i = p * p; i <= MAX_PRIME; i += p)
                array_of_primes[i] = false;
        }
    }
 
    while (true)
    {
        long number = input_check();
 
        printf("Prvociselny rozklad cisla %li je:\n", number);
 
        if (number == 1)
        {
            printf("1\n");
            continue;
        }
 
        // Going throuhgt the array of primes
        for (int prime = 2; prime < MAX_PRIME; prime++)
        {
            if (array_of_primes[prime] == true)
            {
                int amount_of_multipliers = 0;
                int multiplication_flag = 0;
                 
                if (number == prime && amount_of_multipliers == 0)
                {
                    printf("%d\n", prime);
                    break;
                }
 
                int counter = 0;
                while (number % prime == 0)
                {
                    number /= prime;
                    multiplication_flag = 0;
                    counter += 1;
                }
 
                if (counter == 1)
                {
                    printf("%d", prime);
                    amount_of_multipliers = 1;
                }
 
                if (counter > 1)
                {
                    printf("%d^%d", prime, counter);
                    amount_of_multipliers = 1;
                }
 
                if (amount_of_multipliers != 0 && (number == 0 || number == 1))
                {
                    printf("\n");
                    break;
                }
 
                if (amount_of_multipliers != 0 && multiplication_flag == 0)
                {
                    multiplication_flag = 1;
                    printf(" x ");
                }
            }
        }
    }
    return EXIT_SUCCESS;
}
 
long input_check()
{
    // Checking if input is integer and positive
    long input;
    if (scanf("%li\n", &input) == 1 && input >= 0)
    {
        if (input == 0) {exit(EXIT_SUCCESS);}
 
        return input;
    }
 
    else
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        exit(ERROR_INPUT);
    }
}

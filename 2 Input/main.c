#include <stdio.h>
#include <stdlib.h>

int main()
{
  int number, last_number;
  int amount_of_numbers = 0;
  int positive = 0;
  int negative = 0;
  int even = 0;
  int odd = 0;
  float sum = 0;
  int max = -10000;
  int min = 10000;

  //Scanning first number
  last_number = scanf("%d", &number);

  do {
    //Checking range
    if (number < -10000 || number > 10000)
    {
      printf("\nError: Vstup je mimo interval!\n");
      return 100;
    }

    //Writing number
    if (amount_of_numbers >= 1) printf(", %d", number);
    else printf("%d", number);
    
    //Scanning if number is positive or negative
    if (number > 0) positive += 1;
    else if (number != 0) negative += 1;

    //Scanning if number even or odd
    if (number == 0 || number % 2 == 0) even += 1;
    else odd += 1;

    //Searching max and min number
    if (number > max) max = number;
    if (number < min) min = number;

    amount_of_numbers += 1;
    sum += number;

    //Scanning next number & checking eof
    last_number = scanf("%d", &number);
    if (last_number == -1) printf("\n");

  } while (last_number == 1);

  //Printing all needed information
  printf("Pocet cisel: %d\n", amount_of_numbers);
  printf("Pocet kladnych: %d\n", positive);
  printf("Pocet zapornych: %d\n", negative);
  printf("Procento kladnych: %.2f\n", positive * 100.00 / amount_of_numbers);
  printf("Procento zapornych: %.2f\n", negative * 100.00 / amount_of_numbers);
  printf("Pocet sudych: %d\n", even);
  printf("Pocet lichych: %d\n", odd);
  printf("Procento sudych: %.2f\n", even * 100.00 / amount_of_numbers); 
  printf("Procento lichych: %.2f\n", odd * 100.00 / amount_of_numbers); 
  printf("Prumer: %.2f\n", sum / amount_of_numbers);
  printf("Maximum: %d\n", max);
  printf("Minimum: %d\n", min);

  return 0;
}

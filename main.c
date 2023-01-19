#include <stdio.h>
#include <stdlib.h>

int main()
{
    //Entering and scanning numbers.
    //printf("Enter 2 numbers in amount of -10.000 to 10.000!\n");  
    int number_1, number_2;
    scanf("%d %d\n", &number_1, &number_2);

    //Conrolling amounts.
    if((number_1 > 10000) | (number_2 > 10000) | (number_1 < -10000) | (number_2 < -10000))
    {
        fprintf(stderr, "Error: Vstup je mimo interval!\n");
        return(100);
    }

    //Printing operations with numbers.
    printf("Desitkova soustava: %d %d\n", number_1, number_2);

    printf("Sestnactkova soustava: %x %x\n", number_1, number_2);

    int soucet = number_1 + number_2;   
    printf("Soucet: %d + %d = %d\n", number_1, number_2, soucet);

    int rozdil = number_1 - number_2;
    printf("Rozdil: %d - %d = %d\n", number_1, number_2, rozdil);

    int soucin = number_1 * number_2;
    printf("Soucin: %d * %d = %d\n", number_1, number_2, soucin); 

    int podil = number_1 / number_2;
    if(number_2 == 0)
    {
        printf("Podil: %d / %d = NaN\n", number_1, number_2);
    }
    else
    {
        printf("Podil: %d / %d = %d\n", number_1, number_2, podil);
    }

    float summa = number_1 + number_2;
    float prumer = summa / 2;
    printf("Prumer: %.1f\n", prumer);

    if(number_2 == 0)
    {
        fprintf(stderr, "Error: Nedefinovany vysledek!\n");
        return 101;
    }
   
    return 0;
}

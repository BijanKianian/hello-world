#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
void reverse_array (char*, int);

int main()
{
    int size,length,sizeofelement;
    char src[] = "University of Colorado Boulder";

    size = sizeof(src);
    sizeofelement=sizeof(src[0]);                       // Size of array in bytes=
    length = (size/sizeofelement) - 1;          // Number of elements minus '\0'
    //length = strlen(src);
    reverse_array (src, length);


   // char temp;


   //printf("\nOriginal array: array[%d] = { %c, %c, %c, %c, %c }\n", length, *array, *(array+1), *(array+2), *(array+3), *(array+4));
   //printf("Reversed array: reverse[%d] = { %c, %c, %c, %c, %c }\n\n", length, *reverse, *(reverse+1), *(reverse+2), *(reverse+3), *(reverse+4));
   printf("\nOriginal array: array = %s\n", src);
 // printf("Reversed array: reverse = %s\n\n", reverse);
printf("%d   %d   %d\n", size, length, sizeofelement);
    return 0;

}

void reverse_array(char* str, int length)

{
        int i;
        char *temp, reverse[length];
        temp = str + length - 1;

        reverse [length]= '\0';
       for(i = 0; i < length; i++)
       {
         reverse[i] = *temp;
         temp--;
    }
    printf("\nreversed %s",reverse);

}

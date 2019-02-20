#include <stdio.h>
#include <stdint.h>

void swap(char **str1, char **str2)
{
    // insert your code here
    char* temp;
    temp = *str1;
    *str1 = *str2;
    *str2 = temp;
  return;
}

void reverse(char *src, size_t length)
{
    // insert your code here
        char *firstP, *lastP;
        char temp;

        if (src == NULL)
            return;

        firstP = src;
        lastP = src + (length -1);

        do
        {
            temp = *firstP;
            *firstP = *lastP;
            *lastP = temp;
            firstP++;
            lastP--;

        }while (firstP <lastP);

    return;
}


int main(void)
{
    char *str1 = "Embedded System";
    char *str2 = "Principles of";

    // Call swap function here and pass "str1" and "str2" as a arguments
    swap(&str1, &str2);
    printf("Result of swap function -> %s %s\n", str1, str2);

    char src[] = "University of Colorado Boulder";

    // Call the reverse function here and pass "src" variable as an argument
    int length = (sizeof(src)/sizeof(*src))-1;

    reverse (src, length);
    printf("Result of reverse function -> %s\n", src);

    return 0;
}

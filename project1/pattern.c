/**
* @file allocate.c
* @brief This source file contains code that provides the allocate() function definition
* and frees the space allocated in the memory pointed by ptr.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 26 2019
* @version 1.0
*
*/

#include "memtest.h"
#include "pattern.h"

void pattern (int* start, int index, unsigned int seed) /* start represents begining address
                                                of memory cells to be written by random # */
    {
        unsigned int next = generate_random(seed);


        for (int i = 0 ; i <= index-1 ; i++)
            {
                unsigned int num = generate_random(next);
                *(start + i) = num;             /* Writing the generated number into memory block */
                next = num;
            }
        printf("\n\t##########################\n");
        printf("\t#     Random numbers     #\n") ;
        printf("\t##########################\n");
        display(start, index);

    }

    /**             "Linear Congruential Generator (LCG)."

       In this method, the seed (start point) will be deployed in LCG algorithm as follows:

                        Seed = (Multiplier X Seed + increment) % modulus

        The multiplier (a), increment (c) and mudulue (m) are specified by different
        sources listed on the wikipedia page:

                    https://en.wikipedia.org/wiki/Linear_congruential_generator

        According to an experiment shown in a video tutorial with the title:

                "Coding Math: Episode 51 - Pseudo Random Number Generators Part I"

        one of the sets of parameters to get an acceptable result without any duplicating loop,
        is from the following source:

            "Numerical Recipes" <https://en.wikipedia.org/wiki/Numerical_Recipes>

        using these parameters in the algorithm will produce a reasonable set of numbers
        with a very low chance of duplication ad shown in the video tutorial.
        with the parameters being: a = 1664525, c = 1013904223, m = 2^32
        the number won't go beyond 32 bits which is desired for 32 bit designs such as FRDM.

        Note:
            In random number generation techniques using the same seed each time will yeild
            the same set of numbers, which is expected. **/

    int generate_random(unsigned int Seed)
       {

           /* Choosing unsigned interger type to get the values 0 to 2^32 */

            unsigned int a = 1664525;    /* Multiplier */
            unsigned int c = 1013904223; /* Increment */
            unsigned long int m = pow(2,32);       /* Modulus */

            Seed = (a * Seed + c) % m;

            return Seed;

        }

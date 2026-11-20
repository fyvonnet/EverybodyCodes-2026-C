#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"

#define BUFLEN  64
#define MAXWIDTH 50
#define MAXHEIGHT 20
#define NLAYERS 2
#define NBASECOLORS 4
#define NCOLORS 7


typedef enum { cyan, magenta, yellow, black, red, green, blue } Color;
typedef struct { char c; Color v; } Chars;


int compar_chars(const void *a, const void *b)
{
        return ((Chars *)a)->c - ((Chars *)b)->c;
}


int compar_ints(const void *a, const void *b)
{
        return *((int *)b) - *((int *)a);
}


int main() 
{
        Chars chars[NBASECOLORS] = { {'C', cyan}, {'M', magenta}, {'Y', yellow}, {'K', black}};
        char buffer[BUFLEN];
        FILE *fp = fopen("inputs/everybody_codes_e2026_q19_p1.txt", "r");
        Color layers[MAXWIDTH][MAXHEIGHT][NLAYERS];
        int width, height = 0;
        Color mixes[NBASECOLORS][NBASECOLORS];

        qsort(chars, NBASECOLORS, sizeof(Chars), compar_chars);

        for (int i = 0; i < NBASECOLORS; i++) {
                mixes[black][i] = black;
                mixes[i][black] = black;
                mixes[i][i] = i;
        }

        mixes[cyan][magenta]   = mixes[magenta][cyan]   = blue;
        mixes[cyan][yellow]    = mixes[yellow][cyan]    = green;
        mixes[magenta][yellow] = mixes[yellow][magenta] = red;

        fgets(buffer, BUFLEN, fp);
        width = strlen(buffer) - 1;
        for (int l = 0; l < NLAYERS; l++) {
                int r = 0;
                while (strlen(buffer) > 1) {
                        for (int c = 0; c < width; c++) {
                                Chars target = { buffer[c], -1 };
                                Chars *found = binsearch(chars, NBASECOLORS, sizeof(Chars), compar_chars, &target);
                                layers[c][r][l] = found->v;
                        }
                        r++;
                        buffer[0] = '\0';
                        fgets(buffer, BUFLEN, fp);
                }
                fgets(buffer, BUFLEN, fp);
                if (height == 0) height = r;
        }

        int counters[NCOLORS];
        for (int c = 0; c < NCOLORS; c++)
                counters[c] = 0;

        for (int r = 0; r < height; r++)
                for (int c = 0; c < width; c++)
                        counters[mixes[layers[c][r][0]][layers[c][r][1]]]++;

        qsort(counters, NCOLORS, sizeof(int), compar_ints);

        int product = 1;
        for (int i = 0; i < 3; i++)
                product *= counters[i];

        printf("%d\n", product);

        exit(EXIT_SUCCESS);
}


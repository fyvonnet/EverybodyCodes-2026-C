#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"

#define BUFLEN  300
#define MAXWIDTH 300
#define MAXHEIGHT 150
#define NLAYERS 2
#define NBASECOLORS 4
#define NCOLORS 7


typedef enum { CYAN, MAGENTA, YELLOW, BLACK, RED, GREEN, BLUE } Color;
typedef struct { char c; Color v; } Chars;


Color layers[MAXWIDTH][MAXHEIGHT][NLAYERS];
Color mixes[NBASECOLORS][NBASECOLORS];
int numbers[MAXWIDTH][MAXHEIGHT];
int width, height;
long long maxpoints = 0;


int compar_ints(const void *a, const void *b)
{
        return *((int *)b) - *((int *)a);
}


int compar_chars(const void *a, const void *b)
{
        return ((Chars *)a)->c - ((Chars *)b)->c;
}


void permutations(int k, int basecolors[NBASECOLORS])
{
        if (k == 1) {
                for (int r = 0; r < height; r++)
                        for (int c = 0; c < width; c++)
                                layers[c][r][1] = basecolors[numbers[c][r]];

                int counters[NCOLORS];
                for (int c = 0; c < NCOLORS; c++)
                        counters[c] = 0;

                for (int r = 0; r < height; r++)
                        for (int c = 0; c < width; c++)
                                counters[mixes[layers[c][r][0]][layers[c][r][1]]]++;

                qsort(counters, NCOLORS, sizeof(int), compar_ints);

                long long product = 1;
                for (int i = 0; i < 3; i++)
                        product *= counters[i];

                if (product > maxpoints) maxpoints = product;

                return;
        }

        permutations(k - 1, basecolors);

        for (int i = 0; i < k - 1; i++) {
                if (k % 2 == 0) {
                        int t = basecolors[i];
                        basecolors[i] = basecolors[k - 1];
                        basecolors[k - 1] = t;
                }
                else {
                        int t = basecolors[0];
                        basecolors[0] = basecolors[k - 1];
                        basecolors[k - 1] = t;
                }
                permutations(k - 1, basecolors);
        }
}


int main() 
{
        Chars chars[NBASECOLORS] = { {'C', CYAN}, {'M', MAGENTA}, {'Y', YELLOW}, {'K', BLACK}};
        char buffer[BUFLEN];
        FILE *fp = fopen("inputs/everybody_codes_e2026_q19_p2.txt", "r");

        qsort(chars, NBASECOLORS, sizeof(Chars), compar_chars);

        for (int i = 0; i < NBASECOLORS; i++) {
                mixes[BLACK][i] = BLACK;
                mixes[i][BLACK] = BLACK;
                mixes[i][i] = i;
        }

        mixes[CYAN][MAGENTA]   = mixes[MAGENTA][CYAN]   = BLUE;
        mixes[CYAN][YELLOW]    = mixes[YELLOW][CYAN]    = GREEN;
        mixes[MAGENTA][YELLOW] = mixes[YELLOW][MAGENTA] = RED;

        fgets(buffer, BUFLEN, fp);
        width = strlen(buffer) - 1;
        height = 0;
        while (strlen(buffer) > 1) {
                for (int c = 0; c < width; c++) {
                        Chars target = { buffer[c], -1 };
                        Chars *found = binsearch(chars, NBASECOLORS, sizeof(Chars), compar_chars, &target);
                        layers[c][height][0] = found->v;
                }
                height++;
                buffer[0] = '\0';
                fgets(buffer, BUFLEN, fp);
        }

        for (int r = 0; r < height; r++) {
                fgets(buffer, BUFLEN, fp);
                for (int c = 0; c < width; c++) 
                        numbers[c][r] = buffer[c] - '1';
        }

        int basecolors[NBASECOLORS] = { CYAN, MAGENTA, YELLOW, BLACK };
        permutations(NBASECOLORS, basecolors);

        printf("%lld\n", maxpoints);

        exit(EXIT_SUCCESS);
}


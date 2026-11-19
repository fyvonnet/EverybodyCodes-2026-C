#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFLEN 32
#define MAXWIDTH        100
#define MAXHEIGHT       30
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q18_p1.txt", "r");
        char buffer[BUFLEN];
        char grid[100][30];

        for (int r = 0; r < MAXHEIGHT; r++)
                for (int c = 0; c < MAXWIDTH; c++)
                        grid[c][r] = '.';

        int width  = 0;
        int height = 0;
        int count  = 0;

        char *ret = fgets(buffer, BUFLEN, fp);
        while (ret) {
                char *tokx = strtok(buffer, " ");
                char *toky = strtok(NULL,   " ");
                int x = atoi(tokx + 2);
                int y = atoi(toky + 2);
                for (int r = 0; r < y; r++) {
                        grid[x][r] = '#';
                        count++;
                }
                width  = MAX(width,  x);
                height = MAX(height, y);
                ret = fgets(buffer, BUFLEN, fp);
        }

        width++; 

        for (int r = 0; r < height; r++) {
                int cb = 0;
                int ce = width - 1;
                while (grid[cb++][r] != '#');
                while (grid[ce--][r] != '#');
                for (int c = cb; c <= ce; c++)
                        if (grid[c][r] == '.') {
                                count++;
                                grid[c][r] = '=';
                        }
        }

        printf("%d\n", count);

        exit(EXIT_SUCCESS);
}

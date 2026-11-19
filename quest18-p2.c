#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFLEN 32
#define MAXWIDTH        9200
#define MAXHEIGHT       510


int main()
{
        char buffer[BUFLEN];
        bool grid[MAXWIDTH][MAXHEIGHT];

        for (int r = 0; r < MAXHEIGHT; r++)
                for (int c = 0; c < MAXWIDTH; c++)
                        grid[c][r] = false;

        int width  = 0;
        int height = 0;
        int count  = 0;
        int x, y, w;

        FILE *fp = fopen("inputs/everybody_codes_e2026_q18_p2.txt", "r");
        char *ret = fgets(buffer, BUFLEN, fp);
        while (ret) {
                char *tokx = strtok(buffer, " ");
                char *toky = strtok(NULL,   " ");
                char *tokw = strtok(NULL,   " ");
                x = atoi(tokx + 2);
                y = atoi(toky + 2);
                w = tokw[6] - '0';
                count += y * w;
                height = height > y ? height : y;
                for (int r = 0; r < y; r++)
                        for (int c = 0; c < w; c++)
                                grid[x + c][r] = true;
                ret = fgets(buffer, BUFLEN, fp);
        }

        width = x + w;

        for (int r = 0; r < height; r++) {
                int cb = 0;
                int ce = width - 1;
                while (!grid[cb++][r]);
                while (!grid[ce--][r]);
                for (int c = cb; c <= ce; c++)
                        if (!grid[c][r])
                                count++;
        }

        printf("%d\n", count);

        exit(EXIT_SUCCESS);
}

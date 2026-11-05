#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAXWIDTH        50
#define MAXHEIGHT       30
#define BUFLEN          50

char field[MAXWIDTH][MAXHEIGHT];
int field_width, field_height;

int energy(int c, int r)
{
        int count = 0;
        int max = 0;
        int val = field[c++][r++];

        while (val) {
                if (val >= max) {
                        max = val;
                        count++;
                }
                else if (max != 0) max--;
                val = field[c++][r++];
        }

        return count;
}

int main()
{
        //FILE *fp = fopen("inputs/everybody_codes_e2026_q08_p1_sample.txt", "r");
        FILE *fp = fopen("inputs/everybody_codes_e2026_q08_p1.txt", "r");
        char buffer[BUFLEN];

        char *ret = fgets(buffer, BUFLEN, fp);
        int field_width = strlen(buffer) - 1;
        int field_height = 0;
        while (ret) {
                for (int col = 0; col < field_width; col++) {
                        char c = buffer[col];
                        if (c == '.')
                                field[col][field_height] = 0;
                        else
                                field[col][field_height] = c - '0';
                }
                field_height++;
                ret = fgets(buffer, BUFLEN, fp);
        }

        int row = 0;
        int val = field[0][row];
        while (!val) {
                row++;
                val = field[0][row];
        }
        int col = 0;
        int sum = 0;

        while (row != 0)
                sum += energy(col++, row--);

        val = field[col][row];
        while (val != 0) {
                sum += energy(col, row);
                col += 2;
                val = field[col][row];
        }

        printf("%d\n", sum);

        exit(EXIT_SUCCESS);
}

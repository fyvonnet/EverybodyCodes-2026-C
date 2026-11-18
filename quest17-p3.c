#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

#define MAXWIDTH 128
#define MAXHEIGHT 64
#define BUFLEN  128
#define NMOVES  4


typedef enum { NORTH, EAST, SOUTH, WEST } Direction;
typedef enum { LEFT, FRONT, RIGHT, BACK } Turn;

typedef struct {
        int col, row;
        Direction dir;
} QElm;

char field[MAXWIDTH][MAXHEIGHT];
int width, height;


int navigate(Direction dir, Turn turns[4])
{
        Direction newdir[4][4];
        int col_moves[NMOVES];
        int row_moves[NMOVES];
        int col = 1, row = 1;
        int count = 0;


        newdir[LEFT][NORTH]  = WEST;
        newdir[LEFT][EAST]   = NORTH;
        newdir[LEFT][SOUTH]  = EAST;
        newdir[LEFT][WEST]   = SOUTH;

        newdir[FRONT][NORTH] = NORTH;
        newdir[FRONT][EAST]  = EAST;
        newdir[FRONT][SOUTH] = SOUTH;
        newdir[FRONT][WEST]  = WEST;

        newdir[RIGHT][NORTH] = EAST;
        newdir[RIGHT][EAST]  = SOUTH;
        newdir[RIGHT][SOUTH] = WEST;
        newdir[RIGHT][WEST]  = NORTH;

        newdir[BACK][NORTH]  = SOUTH;
        newdir[BACK][EAST]   = WEST;
        newdir[BACK][SOUTH]  = NORTH;
        newdir[BACK][WEST]   = EAST;


        col_moves[NORTH] =  0;
        col_moves[EAST]  =  1;
        col_moves[SOUTH] =  0;
        col_moves[WEST]  = -1;

        row_moves[NORTH] = -1;
        row_moves[EAST]  =  0;
        row_moves[SOUTH] =  1;
        row_moves[WEST]  =  0;


        while (true) {
                Direction ndir;
                int ncol, nrow;
                for (int t = 0; t < 4; t++) {
                        ndir = newdir[turns[t]][dir];
                        ncol = col + col_moves[ndir];
                        nrow = row + row_moves[ndir];
                        if (field[ncol][nrow] == '#') break;
                        else count++;

                }
                dir = ndir;
                col = ncol;
                row = nrow;
                if ((col > width) || (row > height))
                        break;
        }

        return count;
}


int main()
{
        char buffer[BUFLEN];
        FILE *fp = fopen("inputs/everybody_codes_e2026_q17_p3.txt", "r");

        char *ret = fgets(buffer, BUFLEN, fp);
        width = strlen(buffer) - 1;
        height = 0;

        while (ret) {
                height++;
                for (int c = 0; c < width; c++)
                        field[c + 1][height] = buffer[c];
                ret = fgets(buffer, BUFLEN, fp);
        }


        for (int c = 0; c < width + 2; c++) {
                field[c][0] = '.';
                field[c][height + 1] = '.';
        }

        for (int r = 0; r < height + 2; r++) {
                field[0][r] = '.';
                field[width + 1][r] = '.';
        }

        int a, b;

        {
                Turn turns_array[] = { RIGHT, FRONT, LEFT, BACK };
                field[width + 1][height] = '#';
                a = navigate(SOUTH, turns_array);
                field[width + 1][height] = '.';
        }

        {
                Turn turns_array[] = { LEFT, FRONT, RIGHT, BACK };
                field[width][height + 1] = '#';
                b = navigate(EAST, turns_array);
                field[width][height + 1] = '.';
        }

        printf("%d\n", a < b ? a : b);

        exit(EXIT_SUCCESS);
}


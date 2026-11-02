#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "queue.h"

#define MAXWIDTH        128
#define MAXHEIGHT       32
#define MAXPATCHES      MAXWIDTH * MAXHEIGHT


struct {
        int width, height;
        char patches[MAXPATCHES];
} map;

typedef struct { int col, row; } Coord;


int getindex(int col, int row) {
        if (col < 0) return -1;
        if (row < 0) return -1;
        if (col >= map.width) return -1;
        if (row >= map.height) return -1;

        return col + (row * map.width);
}


char getpatch(int col, int row)
{
        int index = getindex(col, row);
        if (index == -1) return '0';
        return map.patches[index];
}


void setland(int col, int row)
{
        int index = getindex(col, row);
        map.patches[index] = '#';
}


Coord *coordcreate(int col, int row)
{
        Coord *newcoord = (Coord *)malloc(sizeof(Coord));
        newcoord->col = col;
        newcoord->row = row; 
        return newcoord;
}


int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q05_p1.txt", "r");
        char *patptr = map.patches;
        Queue *queue = queue_create();

        int ncols[] = { -1,  0,  1, -1,  1, -1,  0,  1 };
        int nrows[] = { -1, -1, -1,  0,  0,  1,  1,  1 };

        char *ret = fgets(patptr, MAXWIDTH, fp);
        map.width = strlen(patptr) - 1;
        map.height = 0;
        while (ret) {
                map.height++;
                patptr += map.width;
                ret = fgets(patptr, MAXWIDTH, fp);
        }

        int center_c = map.width  / 2;
        int center_r = map.height / 2;
        int landcount = 1;
        setland(center_c, center_r);

        Coord *coord = coordcreate(center_c, center_r);
        while (coord) {
                int col = coord->col;
                int row = coord->row;
                free(coord);

                for (int i = 0; i < 8; i++) {
                        int ncol = col + ncols[i];
                        int nrow = row + nrows[i];
                        if (getpatch(ncol, nrow) != '#') {
                                int count = 0;
                                for (int j = 0; j < 8; j++) {
                                        int nncol = ncol + ncols[j];
                                        int nnrow = nrow + nrows[j];
                                        char c = getpatch(nncol, nnrow);
                                        if ((c == '1') || (c == '#') || (c == '@'))
                                                count++;
                                }
                                if (count >= 5) {
                                        landcount++;
                                        setland(ncol, nrow);
                                        queue_enqueue(queue, coordcreate(ncol, nrow));
                                }
                        }
                }
                coord = queue_dequeue(queue);
        }

        printf("%d\n", landcount);

        exit(EXIT_SUCCESS);
}


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "misc.h"
#include "queue.h"

#define BUFLEN 40
#define MAXWIDTH 32
#define MAXHEIGHT 12
#define NNEIGHBS 4

typedef struct {
        char window[MAXWIDTH][MAXHEIGHT];
        bool ticks[MAXWIDTH][MAXHEIGHT];
        int width, height;
} Grid;

typedef struct { int c, r; } QElm;


int count_bindings(Grid *grid, int c, int r)
{
        int count = 0;
        int neighbs_r[NNEIGHBS] = {  0,  0,  1, -1 };
        int neighbs_c[NNEIGHBS] = {  1, -1,  0,  0 };
        char piece = grid->window[c][r];
        Queue *queue = queue_create();

        QElm *qelm = malloc(sizeof(QElm));
        qelm->c = c;
        qelm->r = r;
        grid->ticks[c][r] = true;
        while (qelm) {
                c = qelm->c;
                r = qelm->r;
                free(qelm);
                for (int n = 0; n < NNEIGHBS; n++) {
                        int nc = c + neighbs_c[n];
                        int nr = r + neighbs_r[n];
                        if (grid->window[nc][nr] != piece) {
                                if (!grid->ticks[nc][nr])
                                        count++;
                        }
                        else if (!grid->ticks[nc][nr]) {
                                qelm = malloc(sizeof(QElm));
                                qelm->c = nc;
                                qelm->r = nr;
                                grid->ticks[nc][nr] = true;
                                queue_enqueue(queue, qelm);
                        }
                }
                qelm = queue_dequeue(queue);
        }

        free(queue);
        return count;
}


int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q14_p1.txt", "r");
        char buffer[BUFLEN];
        Grid grid;

        for (int r = 0; r < MAXHEIGHT; r++)
                for (int c = 0; c < MAXWIDTH; c++) {
                        grid.window[c][r] = '\0';
                        grid.ticks[c][r]  = false;
                }

        char *ret = fgets(buffer, BUFLEN, fp);
        grid.height = 0;
        grid.width = strlen(buffer) - 1;
        while (ret) {
                grid.height++;
                for (int c = 0; c < grid.width; c++)
                        grid.window[c + 1][grid.height] = buffer[c];
                ret = fgets(buffer, BUFLEN, fp);
        }

        int sum = 0;
        for (int r = 1; r <= grid.height; r++)
                for (int c = 1; c <= grid.width; c++)
                        if (!grid.ticks[c][r])
                                sum += count_bindings(&grid, c, r);

        printf("%d\n", sum);
        exit(EXIT_SUCCESS);
}



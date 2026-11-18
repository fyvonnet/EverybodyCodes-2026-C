#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

#define MAXIDTH 101
#define MAXHIGH 25
#define BUFLEN  128
#define NMOVES  4


typedef struct { int col, row, nsteps; } QElm;


int main()
{
        int col_moves[NMOVES] = {  1, -1,  0,  0 };
        int row_moves[NMOVES] = {  0,  0,  1, -1 };
        char buffer[BUFLEN];
        char field[MAXIDTH][MAXHIGH];
        FILE *fp = fopen("inputs/everybody_codes_e2026_q17_p1.txt", "r");

        char *ret = fgets(buffer, BUFLEN, fp);
        int width = strlen(buffer) - 1;
        int height = 0;
        while (ret) {
                for (int c = 0; c < width; c++)
                        field[c][height] = buffer[c];
                height++;
                ret = fgets(buffer, BUFLEN, fp);
        }

        int col_e = width  - 1;
        int row_e = height - 1;

        Queue *queue = queue_create();
        QElm *qelm = malloc(sizeof(QElm));
        qelm->col    = 0;
        qelm->row    = 0;
        qelm->nsteps = 0;
        queue_enqueue(queue, qelm);

        while ((qelm = queue_dequeue(queue))) {
                int col    = qelm->col;
                int row    = qelm->row;
                int nsteps = qelm->nsteps;
                free(qelm);

                if ((col == col_e) && (row == row_e)) {
                        printf("%d\n", nsteps);
                        exit(EXIT_SUCCESS);
                }

                for (int m = 0; m < NMOVES; m++) {
                        int ncol = col + col_moves[m];
                        if (ncol < 0) continue;
                        if (ncol >= width) continue;
                        int nrow = row + row_moves[m];
                        if (nrow < 0) continue;
                        if (nrow >= height) continue;
                        if (field[ncol][nrow] == '#') {
                                field[ncol][nrow] = '.';
                                qelm = malloc(sizeof(QElm));
                                qelm->col    = ncol;
                                qelm->row    = nrow;
                                qelm->nsteps = nsteps + 1;
                                queue_enqueue(queue, qelm);
                        }
                }
        }

        // shouldn't reach here
        exit(EXIT_FAILURE);
}


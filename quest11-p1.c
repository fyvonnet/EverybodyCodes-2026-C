#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"
#include "queue.h"

#define BUFSIZE 32
#define MAXPORTALS 32


typedef struct {
        bool tick;
        int ndests, dests[4];
} Portal;

typedef struct { int distance, portal; } QueueElm;


int nportals;
Portal portals[MAXPORTALS];


int distances_from_port(int p)
{
        for (int i = 0; i < nportals; i++) portals[i].tick = false;
        Queue *queue = queue_create();
        QueueElm *qelm = malloc(sizeof(QueueElm));
        qelm->portal   = p;
        qelm->distance = 0;
        portals[p].tick = true;
        int sum = 0;

        while (qelm) {
                Portal *ptr = portals + qelm->portal;
                sum += qelm->distance;
                for (int d = 0; d < ptr->ndests; d++) {
                        Portal *dptr = portals + ptr->dests[d];
                        if (!dptr->tick) {
                                dptr->tick = true;
                                QueueElm *nqelm = malloc(sizeof(QueueElm));
                                nqelm->portal   = ptr->dests[d];
                                nqelm->distance = qelm->distance + 1;
                                queue_enqueue(queue, nqelm);
                        }
                }

                free(qelm);
                qelm = queue_dequeue(queue);
        }

        free(queue);
        return sum;
}

int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q11_p1.txt", "r");
        char buffer[BUFSIZE];

        fgets(buffer, BUFSIZE, fp);
        nportals = atoi(buffer + 9);

        for (int p = 0; p < nportals; p++) {
                Portal *ptr = portals + p;
                ptr->ndests = 2;
                ptr->dests[0] = modulo((p - 1), nportals);
                ptr->dests[1] = modulo((p + 1), nportals);
        }

        int sum = 0;
        for (int p = 0; p < nportals; p++)
                sum += distances_from_port(p);

        // skip empty line
        fgets(buffer, BUFSIZE, fp);

        char *ret = fgets(buffer, BUFSIZE, fp);
        while(ret) {
                int a = atoi(strtok(buffer, " ")) - 1;
                int b = atoi(strtok(NULL,   " ")) - 1;
                Portal *ptr;

                ptr = portals + a;
                ptr->dests[ptr->ndests++] = b;
                ptr = portals + b;
                ptr->dests[ptr->ndests++] = a;
                ret = fgets(buffer, BUFSIZE, fp);
        }

        for (int p = 0; p < nportals; p++)
                sum -= distances_from_port(p);

        printf("%d\n", sum);
        exit(EXIT_SUCCESS);
}


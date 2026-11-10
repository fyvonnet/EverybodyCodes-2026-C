#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "misc.h"
#include "queue.h"
#include "redblacktree.h"

#define BUFSIZE 32


typedef struct {
        bool tick;
        int ndests, dests[8];
} Portal;

typedef struct { int distance, portal; } QueueElm;


int nportals;
Portal *portals;
RedBlackTree *conns;


int compar_conns(const void *a, const void *b)
{
        return a - b;
}


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


void conn_insert(int a, int b)
{
        uint64_t key = (1000 * (a + 1)) + b + 1;
        redblacktree_insert(conns, (void *)key);
}


bool conn_exist(int a, int b)
{
        uint64_t key = (1000 * (a + 1)) + b + 1;
        return (redblacktree_query(conns, (void *)key) != 0);
}


void conn_print(void *c, void *ptr)
{
        uint64_t conn = (uint64_t)c;
        printf("%2lu %2lu\n", (conn / 1000), (conn % 1000));
}


int strain_with_crystals(int a, int b)
{
        if (a == b) return 0;
        if (conn_exist(a, b)) return 0;

        Portal *ptra = portals + a;
        Portal *ptrb = portals + b;

        ptra->dests[ptra->ndests++] = b;
        ptrb->dests[ptrb->ndests++] = a;

        int strain = 0;
        for (int p = 0; p < nportals; p++)
                strain += distances_from_port(p);

        ptra->ndests--;
        ptrb->ndests--;
        return strain;
}



int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q11_p2.txt", "r");
        char buffer[BUFSIZE];

        fgets(buffer, BUFSIZE, fp);
        nportals = atoi(buffer + 9);
        portals = malloc(nportals * sizeof(Portal));
        conns = redblacktree_init(compar_conns);

        for (int p = 0; p < nportals; p++) {
                Portal *ptr = portals + p;
                ptr->ndests = 0;
                for (int d = 1; d <= 3; d++) {
                        int da = modulo((p - d), nportals);
                        int db = modulo((p + d), nportals);

                        ptr->dests[ptr->ndests++] = da;
                        ptr->dests[ptr->ndests++] = db;

                        conn_insert(p, da);
                        conn_insert(p, db);
                }
        }

        int initial_strain = 0;
        for (int p = 0; p < nportals; p++)
                initial_strain += distances_from_port(p);

        fgets(buffer, BUFSIZE, fp); // skip empty line

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

                conn_insert(a, b);
                conn_insert(b, a);
        }

        int maxres = 0;
        for (int a = 0; a < nportals; a++)
                for (int  b= 0; b < nportals; b++) {
                        int strain = strain_with_crystals(a, b);
                        if (strain != 0) {
                                int res = initial_strain - strain;
                                if (res > maxres) maxres = res;
                        }
                }

        printf("%d\n", maxres);
        exit(EXIT_SUCCESS);
}


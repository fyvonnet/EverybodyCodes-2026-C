#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>
#include "queue.h"

#define BUFSIZE 64
#define MAXCLOUDS 32


typedef struct { int energy, *conns, nconns; } Cloud;
typedef struct { int energy, icloud; } Pulse;


int main()
{
        char buffer[BUFSIZE];
        const char regex[] = "^id=(.+), energy=(.+), connections=(.+)$";
        regex_t preg;
        regmatch_t pmatch[4];
        int allconns[64];
        Cloud clouds[MAXCLOUDS];

        regcomp(&preg, regex, REG_NEWLINE | REG_EXTENDED);

        FILE *fp = fopen("inputs/everybody_codes_e2026_q07_p1.txt", "r");
        char *ret = fgets(buffer, BUFSIZE, fp);
        int iconn = 0;
        int nclouds = 0;
        while (ret) {
                regexec(&preg, buffer, 4, pmatch, 0);
                nclouds++;
                int id = atoi(buffer + pmatch[1].rm_so);
                int energy = atoi(buffer + pmatch[2].rm_so);
                clouds[id].energy = energy;
                char *tok = strtok(buffer + pmatch[3].rm_so, ",");
                clouds[id].conns = allconns + iconn;
                int nconns = 0;
                while (tok) {
                        nconns++;
                        allconns[iconn++] = atoi(tok);
                        tok = strtok(NULL, ",");
                }
                clouds[id].nconns = nconns;
                ret = fgets(buffer, BUFSIZE, fp);
        }

        int maxnconns = 0;
        int maxid;
        for (int id = 1; id <= nclouds; id++)
                if (clouds[id].nconns > maxnconns) {
                        maxnconns = clouds[id].nconns;
                        maxid = id;
                }

        Queue *queue = queue_create();
        Pulse *pulse = malloc(sizeof(Pulse));
        pulse->energy = 5;
        pulse->icloud = maxid;
        while (pulse->energy) {
                int energy = pulse->energy;
                Cloud *cloud = clouds + pulse->icloud;
                cloud->energy += energy--;
                for (int i = 0; i < cloud->nconns; i++) {
                        pulse = malloc(sizeof(Pulse));
                        pulse->energy = energy;
                        pulse->icloud = cloud->conns[i];
                        queue_enqueue(queue, pulse);
                } 
                pulse = queue_dequeue(queue);
        }

        int sum = 0;
        for (int i = 1; i <= nclouds; i++)
                sum += clouds[i].energy;
        printf("%d\n", sum);

        exit(EXIT_SUCCESS);
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <regex.h>
#include "queue.h"

#define BUFLEN  128
#define BRANCHING       -1


typedef struct { int time, length; } Branch;


void enqueue(Queue *queue, int time, int length)
{
        Branch *branch = malloc(sizeof(Branch));
        branch->time = time;
        branch->length= length;
        queue_enqueue(queue, branch);
}



int grow(int growth, int limit)
{
        int time = 0;
        int nelems = 0;
        Queue *queue = queue_create();
        enqueue(queue, 0, 0);

        for (;;) {
                int ttime = time + 1;
                Branch *branch = queue_peek(queue);
                if (branch->time == time) {
                        queue_dequeue(queue);
                        if (branch->length == BRANCHING) {
                                enqueue(queue, ttime, BRANCHING);
                                nelems++;
                        }
                        else {
                                nelems += branch->length;
                                branch->length++;
                                if (branch->length == growth) {
                                        enqueue(queue, ttime, branch->length / 2);
                                        enqueue(queue, ttime, branch->length / 2);
                                        enqueue(queue, ttime, 1);
                                        enqueue(queue, ttime, BRANCHING);
                                        free(branch);
                                }
                                else enqueue(queue, ttime, branch->length);
                        }
                }
                else {
                        if (nelems >= limit) return time;
                        nelems = 0;
                        time = ttime;
                }
        }
}


int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q09_p1.txt", "r");
        char buffer[BUFLEN];
        const char regex[] = "^id=(.+), growth=(.+), limit=(.+)$";
        regex_t preg;
        regmatch_t pmatch[4];

        if (regcomp(&preg, regex, REG_NEWLINE | REG_EXTENDED))
                exit(EXIT_FAILURE);

        int sum = 0;
        char *ret = fgets(buffer, BUFLEN, fp);
        while (ret) {
                if (regexec(&preg, buffer, 4, pmatch, 0)) exit(EXIT_FAILURE);
                //int id     = atoi(buffer + pmatch[1].rm_so);
                int growth = atoi(buffer + pmatch[2].rm_so);
                int limit  = atoi(buffer + pmatch[3].rm_so);
                sum += grow(growth, limit);
                ret = fgets(buffer, BUFLEN, fp);
        }

        printf("%d\n", sum);

        exit(EXIT_SUCCESS);
}


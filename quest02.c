#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

#define BUFSIZE         256

struct node {
        int i;
        int digits[10];
};
typedef struct node Node;


Node *nodecreate()
{
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->i = 0;
        for (int i = 0; i < 9; i++) newnode->digits[i] = 0;
        return newnode;
}


Node *nodecopy(Node *n)
{
        Node *newnode = nodecreate();
        newnode->i = n->i;
        for (int i = 0; i < 10; i++) newnode->digits[i] = n->digits[i];
        return newnode;
}


int main()
{
        char buffer[BUFSIZE];
        bool mtx[11][11];

        for (int part = 1; part <= 3; part++) {
                sprintf(buffer, "inputs/everybody_codes_e2026_q02_p%d.txt", part);
                FILE *fp = fopen(buffer , "r");
                long long sum = 0;
                Queue *queue = queue_create();

                char *ret = fgets(buffer, BUFSIZE, fp);
                while (ret) {
                        for (int i = 0; i < 11; i++)
                                for (int j = 0; j < 11; j++)
                                        mtx[i][j] = false;

                        char *token = strtok(buffer, " ");
                        while (token) {
                                int a, b;
                                switch(token[1]) {
                                        case '<':
                                                a = token[2] - '0';
                                                b = token[0] - '0';
                                                break;
                                        case '>':
                                                a = token[0] - '0';
                                                b = token[2] - '0';
                                                break;
                                        default:
                                                exit(EXIT_FAILURE);
                                }
                                mtx[a][b] = true;
                                token = strtok(NULL, " ");
                        }

                        for (int i = 1; i <= 9; i++) {
                                Node *n = nodecreate();
                                n->digits[0] = i;
                                queue_enqueue(queue, n);
                        }

                        Node *n = queue_dequeue(queue);
                        Node *oldnode = NULL;
                        while (n) {
                                if (oldnode) free(oldnode);
                                int d = n->digits[n->i++];
                                for (int i = 1; i <= 9; i++)
                                        if (mtx[d][i]) {
                                                Node *newnode = nodecopy(n);
                                                newnode->digits[n->i] = i;
                                                queue_enqueue(queue, newnode);
                                        }
                                oldnode = n;
                                n = queue_dequeue(queue);
                        }

                        int number = 0;
                        int i = 0;
                        int digit = oldnode->digits[i++];
                        while (digit != 0) {
                                number *= 10;
                                number += digit;
                                digit = oldnode->digits[i++];
                        }
                        sum += number;

                        ret = fgets(buffer, BUFSIZE, fp);
                }

                printf("Part %d: %lld\n", part, sum);
                fclose(fp);
        }
        exit(EXIT_SUCCESS);
}

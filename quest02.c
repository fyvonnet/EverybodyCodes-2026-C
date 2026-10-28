#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFSIZE         256

struct node {
        int i;
        int digits[10];
        struct node *next;
};
typedef struct node Node;

typedef struct { Node *head, *tail; } Queue;


Node *nodecreate()
{
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->i = 0;
        for (int i = 0; i < 9; i++) newnode->digits[i] = 0;
        newnode->next = NULL;
        return newnode;
}


Node *nodecopy(Node *n)
{
        Node *newnode = nodecreate();
        newnode->i = n->i;
        for (int i = 0; i < 10; i++) newnode->digits[i] = n->digits[i];
        return newnode;
}


void enqueue(Queue *q, Node *n)
{
        if (q->head == NULL)
                q->head = q->tail = n;
        else
                q->tail = q->tail->next = n;
}


Node *dequeue(Queue *q)
{
        if (q->head == NULL)
                return NULL;

        Node *n = q->head;
        if (n->next == NULL)
                q->head = q->tail = NULL;
        else
                q->head = n->next;
        return n;
}


int main()
{
        char buffer[BUFSIZE];
        bool mtx[11][11];

        for (int part = 1; part <= 3; part++) {
                sprintf(buffer, "inputs/everybody_codes_e2026_q02_p%d.txt", part);
                FILE *fp = fopen(buffer , "r");
                long long sum = 0;
                Queue queue = { NULL, NULL};

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
                                enqueue(&queue, n);
                        }

                        Node *n = dequeue(&queue);
                        Node *oldnode;
                        while (n) {
                                int d = n->digits[n->i++];
                                for (int i = 1; i <= 9; i++)
                                        if (mtx[d][i]) {
                                                Node *newnode = nodecopy(n);
                                                newnode->digits[n->i] = i;
                                                enqueue(&queue, newnode);
                                        }
                                oldnode = n;
                                n = dequeue(&queue);
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

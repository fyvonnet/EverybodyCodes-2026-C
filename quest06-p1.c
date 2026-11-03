#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "misc.h"
#include "queue.h"
#include "redblacktree.h"

#define BUFLEN          32
#define MAXNOTES        64


typedef uint64_t Hash;

struct Note {
        Hash hash;
        struct Note *next;
        bool tick;
};
typedef struct Note Note;


Hash hash(char *str)
{
        Hash h = 0;
        for (int i = 0; i < 4; i++) {
                h <<= 8;
                h += str[i];
        }
        return h;
}


int compar_hashes(const void *a, const void *b)
{
        return (Hash)a - (Hash)b;
}


int compar_notes(const void *a, const void *b)
{
        Note *aa = (Note *)a;
        Note *bb = (Note *)b;
        return aa->hash - bb->hash;
}


char *hash2str(Hash hash)
{
        char *str = malloc(5);
        str[4] = '\0';
        for (int i = 3; i >= 0; i--) {
                str[i] = hash & 0xFF;
                hash >>= 8;
        }
        return str;
}


int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q06_p1.txt", "r");
        char buffer[BUFLEN];
        Note notes[MAXNOTES];
        int nnotes = 0;

        char *ret = fgets(buffer, BUFLEN, fp);
        while (ret) {
                Note *headnote = notes + nnotes;
                char *bufptr = buffer;
                headnote->next = NULL;
                headnote->hash = hash(bufptr);
                headnote->tick = false;
                do {
                        bufptr += 5;
                        Note *n = malloc(sizeof(Note)); 
                        n->hash = hash(bufptr);
                        n->next = headnote->next;
                        headnote->next = n;
                } while (bufptr[4] == ',');
                nnotes++;
                ret = fgets(buffer, BUFLEN, fp);
        }

        qsort(notes, nnotes, sizeof(Note), compar_notes);

        Queue *queue = queue_create();
        RedBlackTree *set = redblacktree_init(compar_hashes);
        Hash h = hash("NULL");
        while (h) {
                redblacktree_insert(set, (void *)h);
                Note target = { .hash = h };
                Note *n = binsearch(notes, nnotes, sizeof(Note), compar_notes, &target);
                if (n && !n->tick) {
                        n->tick = true;
                        n = n->next;
                        while (n != NULL) {
                                queue_enqueue(queue, (void *)n->hash);
                                n = n->next;
                        }
                }
                h = (Hash)queue_dequeue(queue);
        }
        printf("%d\n", redblacktree_nodecount(set) - 1);
}

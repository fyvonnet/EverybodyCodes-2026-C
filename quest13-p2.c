#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "misc.h"

#define BUFLEN  32
#define NHANDS  3


struct { int hand, curr, move, dir, tick_angle, curr_angle; } hands[NHANDS];


char *move_after_space(char *str)
{
        while (*str != ' ') str++;
        return str + 1;
}


void read_values(FILE *fp, int *ptr)
{
        char buffer[BUFLEN];
        fgets(buffer, BUFLEN, fp);
        char *tok = strtok(move_after_space(buffer), ":");
        for (int i = 0; i < NHANDS; i++) {
                ptr[i] = atoi(tok);
                tok = strtok(NULL, ":");
        }

}


int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q13_p2.txt", "r");
        char buffer[BUFLEN];
        int tmp[NHANDS];
        char *ret;
        long long sum = 0;

        do {
                int degrees = 1;
                read_values(fp, tmp);
                for (int i = 0; i < NHANDS; i++) {
                        degrees *= tmp[i];
                        hands[i].hand = tmp[i];
                }

                fgets(buffer, BUFLEN, fp);
                buffer[strlen(buffer) - 1] = '\0';

                read_values(fp, tmp);
                for (int i = 0; i < NHANDS; i++)
                        hands[i].curr = tmp[i];

                read_values(fp, tmp);
                for (int i = 0; i < NHANDS; i++)
                        hands[i].move = tmp[i];

                char *tok = strtok(move_after_space(buffer), ":");
                for (int i = 0; i < NHANDS; i++) {
                        hands[i].tick_angle = degrees / hands[i].hand;
                        hands[i].curr_angle = hands[i].tick_angle * hands[i].curr;
                        if (strlen(tok) == 3) hands[i].tick_angle *= -1;
                        tok = strtok(NULL, ":");
                }

                int moves = 1;
                int nsignals = 0;
                while (moves != 0) {
                        moves = 0;
                        for (int h = 0; h < NHANDS; h++)
                                for (int hh = h + 1; hh < NHANDS; hh++) {
                                        int delta = hands[h].move ? hands[h].tick_angle : 0;
                                        if (hands[hh].move != 0)
                                                delta -= hands[hh].tick_angle;
                                        int dist;
                                        if (delta > 0)
                                                dist = modulo(hands[hh].curr_angle - hands[h].curr_angle, degrees);
                                        else
                                                dist = modulo(hands[h].curr_angle - hands[hh].curr_angle, degrees);
                                        if ((dist != 0) && (abs(delta) >= dist))
                                                nsignals++;
                                }

                        for (int h = 0; h < NHANDS; h++)
                                if (hands[h].move != 0) {
                                        moves++;
                                        hands[h].move--;
                                        hands[h].curr_angle += hands[h].tick_angle;
                                        hands[h].curr_angle = modulo(hands[h].curr_angle, degrees);
                                }
                }

                sum += nsignals;
                ret = fgets(buffer, BUFLEN, fp);
        } while (ret != NULL);

        printf("%lld\n", sum);

        exit(EXIT_SUCCESS);
}


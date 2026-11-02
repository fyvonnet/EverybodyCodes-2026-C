#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BUFSIZE 32

void invert(char *arr, int len) {
        int a = 0, b = len - 1;
        while (a < b) {
                char tmp = arr[a];
                arr[a] = arr[b];
                arr[b] = tmp;
                a++; b--;
        }
}

int main()
{
        //FILE *fp = fopen("inputs/everybody_codes_e2026_q03_p1_sample.txt", "r");
        //FILE *fp = fopen("inputs/everybody_codes_e2026_q03_p2_sample.txt", "r");
        //FILE *fp = fopen("inputs/everybody_codes_e2026_q03_p1.txt", "r");
        FILE *fp = fopen("inputs/everybody_codes_e2026_q03_p2.txt", "r");
        char buffer[BUFSIZE];
        char *ret = fgets(buffer, BUFSIZE, fp);
        long long total = 0;
        while (ret) {
                char *bufptr = buffer + 4;
                char standard[32], votes[32];
                int nstand = 0, nvotes = 0;
                while (*bufptr != ' ') {
                        standard[nstand++] = *bufptr - '0';
                        bufptr++;
                }
                invert(standard, nstand);
                bufptr++;
                while (*bufptr != '\n') {
                        votes[nvotes++] = *bufptr - '0';
                        bufptr++;
                }
                invert(votes, nvotes);
                /*
                for (int i = 0; i < nvotes; i++)
                        printf("%d ", votes[i]);
                putchar('\n');
                printf("%d: ", nstand);
                for (int i = 0; i < nstand; i++)
                        printf("%d ", standard[i]);
                printf(" / ");
                while (*bufptr != '\n') {
                        printf("%c", *bufptr);
                        bufptr++;
                }
                putchar('\n');
                */
                long long sum = 0;
                for (int e = 0; e < nvotes; e++)
                        sum += votes[e] * (long long)pow(standard[e % nstand], e);
                printf("%lld\n", sum);
                total += sum;
                ret = fgets(buffer, BUFSIZE, fp);
        }
        printf("\n%lld\n", total);
        exit(EXIT_SUCCESS);
}

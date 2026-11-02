#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BUFSIZE 32

int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q03_p1.txt", "r");
        char buffer[BUFSIZE];
        char *ret = fgets(buffer, BUFSIZE, fp);
        int total = 0;
        while (ret) {
                char *ptra = buffer + 4;
                char *ptrb = buffer + 9;
                int sum = 0;
                for (int i = 0; i < 4; i++)
                        sum += (ptrb[i] - '0') * (int)pow((double)(ptra[i] - '0'), 3 - i);
                total += sum;
                ret = fgets(buffer, BUFSIZE, fp);
        }
        printf("%d\n", total);
        exit(EXIT_SUCCESS);
}

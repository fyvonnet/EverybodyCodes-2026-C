#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFLEN 64


void compute(char *str, int *val, int *nsegs)
{
        int segs[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };
        int a = str[0] - '0';
        int b = str[4] - '0';

        *nsegs = segs[a] + segs[b];

        switch (str[2]) {
                case '+':
                        *val = a + b;
                        *nsegs += 2;
                        break;
                case '-':
                        *val = a - b;
                        *nsegs += 1;
                        break;
        }
}


int main()
{
        char buffer[BUFLEN];
        FILE *fp = fopen("inputs/everybody_codes_e2026_q20_p1.txt", "r");
        char *ret = fgets(buffer, BUFLEN, fp);
        int sum = 0;

        while (ret) {
                int vala, valb;
                int nsegsa, nsegsb;
                compute(buffer + 0, &vala, &nsegsa);
                compute(buffer + 8, &valb, &nsegsb);
                if (vala == valb) sum += nsegsa + nsegsb + 2;
                ret = fgets(buffer, BUFLEN, fp);
        }

        printf("%d\n", sum);

        exit(EXIT_SUCCESS);
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 3 * 1024

int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q01_p3.txt", "r");
        char buffer[BUFSIZE];

        fgets(buffer, BUFSIZE, fp);

        int sum = 0;
        char *tok = strtok(buffer, ",");
        while(tok) {
                int num = atoi(tok);
                int n = 3;
                int m = (n * n) - 1;
                while (m < num) { n += 2; m = (n * n) - 1; }
                sum += m - num;
                tok = strtok(NULL, ",");
        }

        printf("%d\n", sum);

        exit(EXIT_SUCCESS);
}

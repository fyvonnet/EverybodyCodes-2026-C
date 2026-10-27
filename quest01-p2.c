#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 1024

int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q01_p2.txt", "r");
        char buffer[BUFSIZE];

        fgets(buffer, BUFSIZE, fp);

        int sum = 0;
        char *tok = strtok(buffer, ",");
        while(tok) {
                int num = atoi(tok);
                int n = 8;
                while (n < num) n += 4;
                sum += n - num;
                tok = strtok(NULL, ",");
        }

        printf("%d\n", sum);

        exit(EXIT_SUCCESS);
}

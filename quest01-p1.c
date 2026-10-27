#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q01_p1.txt", "r");
        char buffer[512];

        fgets(buffer, 512, fp);

        int sum = 0;
        char *tok = strtok(buffer, ",");
        while(tok) {
                int num = atoi(tok);
                int root =  (int)ceil(sqrt(num));
                sum += (root * root) - num;
                tok = strtok(NULL, ",");
        }

        printf("%d\n", sum);

        exit(EXIT_SUCCESS);
}

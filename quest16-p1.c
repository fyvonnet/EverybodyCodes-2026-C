#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFLEN 128


int main()
{
        char buffer[BUFLEN];
        FILE *fp = fopen("inputs/everybody_codes_e2026_q16_p1.txt", "r");
        fgets(buffer, BUFLEN, fp);

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') { 
                buffer[len - 1] = '\0';
                len--;
        }

        char *bufptr = buffer;
        int nflips = 0;
        for (int i = 0; i < 3; i++) {
                char c = *bufptr;
                char *endptr = buffer + len - 1;
                while (*bufptr == c) bufptr++;

                while (endptr > bufptr) {
                        while (*endptr != c) endptr--;
                        if (endptr > bufptr) {
                                char *a = bufptr;
                                char *b = endptr;
                                while (a < b) {
                                        char t = *a;
                                        *a = *b;
                                        *b = t;
                                        a++; b--;
                                }
                                nflips++;
                        }
                        else break;
                        while (*bufptr == c) bufptr++;
                        while (*endptr == c) endptr--;
                }
        }

        printf("%d\n", nflips);
        exit(EXIT_SUCCESS);
}

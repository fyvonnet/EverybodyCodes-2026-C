#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFLEN 100000 * 101

char buffer[BUFLEN];

int main()
{
        FILE *fp = fopen("inputs/everybody_codes_e2026_q16_p3.txt", "r");
        fgets(buffer, BUFLEN, fp);
        fclose(fp);

        int len = strlen(buffer);
        if (buffer[len - 1] == '\n') { 
                buffer[len - 1] = '\0';
                len--;
        }

        char *endptr = buffer + len;
        for (int i = 0; i < 99; i++) {
                char *bufptr = buffer;
                for (int j = 0; j < len; j++)
                        *(endptr++) = *(bufptr++);
        }

        len *= 100;

        char *bufptr = buffer;
        long long sum = 0;
        for (int i = 0; i < 3; i++) {
                char c = *bufptr;
                char *endptr = buffer + len - 1;
                while (*bufptr == c) bufptr++;

                while (endptr > bufptr) {
                        while (*endptr != c) endptr--;
                        if (endptr > bufptr) {
                                char *a = bufptr;
                                char *b = endptr;
                                sum += (b - a + 1);
                                while (a < b) {
                                        char t = *a;
                                        *a = *b;
                                        *b = t;
                                        a++; b--;
                                }
                        }
                        else break;
                        while (*bufptr == c) bufptr++;
                        while (*endptr == c) endptr--;
                }
        }

        printf("%lld\n", sum);
        exit(EXIT_SUCCESS);
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFLEN 64
#define BASE    11


int convert(char *str)
{
        int acc = 0;

        for (;;) {
                char c = *str++;
                if ((c >= '0') && (c <= '9'))
                        acc = (acc * BASE) + (c - '0');
                else if (c == 'A')
                        acc = (acc * BASE) + 10;
                else
                        break;
        }

        return acc;
}


void moveafterchar(char **ptr, char c)
{
        while ((*(*ptr)++) != c);
}


int compute(char *str)
{
        int a = convert(str);
        moveafterchar(&str, ' ');
        int b = convert(str + 2);
        return a + b * (*str == '+' ? 1 : -1);
}


int main()
{
        char buffer[BUFLEN];
        FILE *fp = fopen("inputs/everybody_codes_e2026_q20_p2.txt", "r");
        char *ret = fgets(buffer, BUFLEN, fp);
        int sum = 0;
        int segs[256];

        segs['0'] = 6;
        segs['1'] = 2;
        segs['2'] = 5;
        segs['3'] = 5;
        segs['4'] = 4;
        segs['5'] = 5;
        segs['6'] = 6;
        segs['7'] = 3;
        segs['8'] = 7;
        segs['9'] = 6;
        segs['A'] = 6;
        segs[' '] = 0;
        segs['+'] = 2;
        segs['-'] = 1;
        segs['='] = 2;
        segs['\n'] = 0;
        segs['\0'] = 0;

        while (ret) {
                char *bufptr = buffer;
                int a = compute(bufptr);
                moveafterchar(&bufptr, '=');
                int b = compute(bufptr + 1);
                if (a == b) {
                        bufptr = buffer;
                        char c = *bufptr++;
                        while (c != '\0') {
                                sum += segs[(int)c];
                                c = *bufptr++;
                        }
                }
                ret = fgets(buffer, BUFLEN, fp);
        }

        char *bufptr = buffer;
        char symbs[BASE] = "0123456789A";
        while (sum != 0) {
                *bufptr++ =  symbs[sum % BASE];
                sum /= BASE;
        }

        while (bufptr > buffer) putchar(*--bufptr);
        putchar('\n');

        exit(EXIT_SUCCESS);
}


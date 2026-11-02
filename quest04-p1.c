#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define BUFSIZE 64
#define MAXPART 16


int compar(const void *a, const void *b)
{
        return *((int *)a) - *((int *)b);
}


int main()
{
        char buffer[BUFSIZE];
        const char regex[] = "^id=(.+) quest=(.+) part=(.+) time=(.+)$";
        int err;
        regex_t preg;
        regmatch_t pmatch[5];
        int times[MAXPART];

        for (int i = 0; i < MAXPART; i++)
                times[i] = 0;

        FILE *fp = fopen("inputs/everybody_codes_e2026_q04_p1.txt", "r");

        if (regcomp(&preg, regex, REG_NEWLINE | REG_EXTENDED))
                exit(EXIT_FAILURE);

        int maxid = 0;
        char *ret = fgets(buffer, BUFSIZE, fp);
        while (ret) {
                if (regexec(&preg, buffer, 5, pmatch, 0))
                        exit(EXIT_FAILURE);

                int id   = atoi(buffer + pmatch[1].rm_so);
                int time = atoi(buffer + pmatch[4].rm_so);
                times[id] += time;
                maxid = maxid < id ? id : maxid;
                ret = fgets(buffer, BUFSIZE, fp);
        }

        qsort(times + 1, maxid, sizeof(int), compar);

        int sum = 0;
        for (int i = 1; i <= maxid; i++)
                sum += i * times[i];

        printf("%d\n", sum);

        exit(EXIT_SUCCESS);
}


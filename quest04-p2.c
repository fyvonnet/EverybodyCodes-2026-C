#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define BUFSIZE 64
#define MAXPART 128


typedef struct { int time, parts; } Participant;


int compar(const void *a, const void *b)
{
        Participant *pa = (Participant *)a;
        Participant *pb = (Participant *)b;

        if (pa->parts == pb->parts)
                return pa->time - pb->time;

        return pb->parts - pa->parts;
}


int main()
{
        char buffer[BUFSIZE];
        const char regex[] = "^id=(.+) quest=(.+) part=(.+) time=(.+)$";
        int err;
        regex_t preg;
        regmatch_t pmatch[5];
        Participant participants[MAXPART];

        for (int i = 0; i < MAXPART; i++) {
                participants[i].time  = 0;
                participants[i].parts = 0;
        }

        FILE *fp = fopen("inputs/everybody_codes_e2026_q04_p2.txt", "r");

        if (regcomp(&preg, regex, REG_NEWLINE | REG_EXTENDED))
                exit(EXIT_FAILURE);

        int maxid = 0;
        char *ret = fgets(buffer, BUFSIZE, fp);
        while (ret) {
                if (regexec(&preg, buffer, 5, pmatch, 0))
                        exit(EXIT_FAILURE);

                int id   = atoi(buffer + pmatch[1].rm_so);
                int time = atoi(buffer + pmatch[4].rm_so);
                participants[id].time += time;
                participants[id].parts++;
                maxid = maxid < id ? id : maxid;
                ret = fgets(buffer, BUFSIZE, fp);
        }

        qsort(participants + 1, maxid, sizeof(Participant), compar);

        long long sum = 0;
        for (int i = 1; i <= maxid; i++) sum += i * participants[i].time;
        printf("%lld\n", sum);

        exit(EXIT_SUCCESS);
}


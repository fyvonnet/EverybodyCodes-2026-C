#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFLEN 64
#define MAXNMEAS         10000


typedef struct { int x, height, width; } Measurement;


int main()
{
        Measurement meas[MAXNMEAS];
        int nmeas = 0;
        char buffer[BUFLEN];
        int height = 0;

        FILE *fp = fopen("inputs/everybody_codes_e2026_q18_p3.txt", "r");
        char *ret = fgets(buffer, BUFLEN, fp);
        while (ret) {
                Measurement *ptr = meas + nmeas;
                char *tokx = strtok(buffer, " ");
                char *tokh = strtok(NULL,   " ");
                char *tokw = strtok(NULL,   " ");
                ptr->x      = atoi(tokx + 2);
                ptr->height = atoi(tokh + 2);
                ptr->width = tokw ? atoi(tokw + 6) : 1;
                height = ptr->height > height ? ptr->height : height;
                nmeas++;
                ret = fgets(buffer, BUFLEN, fp);
        }

        int l = 0; 
        int r = nmeas - 1;
        int rec_bottom = 0;
        long long sum = 0;

        while (rec_bottom < height) {
                while (meas[l].height <= rec_bottom) l++;
                while (meas[r].height <= rec_bottom) r--;
                int left_wall_height  = meas[l].height - rec_bottom;
                int right_wall_height = meas[r].height - rec_bottom;
                int rec_height = left_wall_height < right_wall_height ? left_wall_height : right_wall_height;
                int rec_left  = meas[l].x;
                int rec_right = meas[r].x + meas[r].width;
                long long rec_width = rec_right - rec_left;
                long long rec_area = rec_width * rec_height;
                sum += rec_area;
                rec_bottom += rec_height;
        }

        printf("%lld\n", sum);

        exit(EXIT_SUCCESS);
}


#include <stdio.h>

int a[21][21] = {
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
};

int main() {
    int i, j, cnt_1 = 0, cnt_2 = 0, *p;
    for (i = 1; i <= 19; i++)
        for (j = 1; j <= 19; j++)
            scanf("%d", &a[i][j]);
    for (i = 1; i <= 19; i++) {
        for (j = 1; j <= 19; j++) {
            if (a[i][j] == 0) {
                cnt_1 = 0;
                cnt_2 = 0;
            } else if (a[i][j] == 1) {
                cnt_1++;
                cnt_2 = 0;
            } else {
                cnt_2++;
                cnt_1 = 0;
            }
            if (cnt_1 == 4 && (a[i][j + 1] == 0 || a[i][j - 4] == 0)) {
                printf("1:%d,%d\n", i, j - 3);
                return 0;
            }
            if (cnt_2 == 4 && (a[i][j + 1] == 0 || a[i][j - 4] == 0)) {
                printf("2:%d,%d\n", i, j - 3);
                return 0;
            }
        }
        cnt_1 = 0;
        cnt_2 = 0;
    }
    for (j = 1; j <= 19; j++) {
        for (i = 1; i <= 19; i++) {
            if (a[i][j] == 0) {
                cnt_1 = 0;
                cnt_2 = 0;
            } else if (a[i][j] == 1) {
                cnt_1++;
                cnt_2 = 0;
            } else {
                cnt_2++;
                cnt_1 = 0;
            }
            if (cnt_1 == 4 && (a[i + 1][j] == 0 || a[i - 4][j] == 0)) {
                printf("1:%d,%d\n", i - 3, j);
                return 0;
            }
            if (cnt_2 == 4 && (a[i + 1][j] == 0 || a[i - 4][j] == 0)) {
                printf("2:%d,%d\n", i - 3, j);
                return 0;
            }
        }
        cnt_1 = 0;
        cnt_2 = 0;
    }
    for (i = 1; i <= 16; i++)
        for (j = 1; j <= 16; j++) {
            p = &a[i][j];
            if (*p == 1 && *(p + 22) == 1 && *(p + 44) == 1 && *(p + 66) == 1 && (*(p + 88) == 0 || *(p - 22) == 0)) {
                printf("1:%d,%d\n", i, j);
                return 0;
            }
            if (*p == 2 && *(p + 22) == 2 && *(p + 44) == 2 && *(p + 66) == 2 && (*(p + 88) == 0 || *(p - 22) == 0)) {
                printf("2:%d,%d\n", i, j);
                return 0;
            }
        }
    for (i = 1; i <= 16; i++)
        for (j = 4; j <= 19; j++) {
            p = &a[i][j];
            if (*p == 1 && *(p + 20) == 1 && *(p + 40) == 1 && *(p + 60) == 1 && (*(p + 80) == 0 || *(p - 20) == 0)) {
                printf("1:%d,%d\n", i, j);
                return 0;
            }
            if (*p == 2 && *(p + 20) == 2 && *(p + 40) == 2 && *(p + 60) == 2 && (*(p + 80) == 0 || *(p - 20) == 0)) {
                printf("2:%d,%d\n", i, j);
                return 0;
            }
        }
    printf("No\n");
    return 0;
}
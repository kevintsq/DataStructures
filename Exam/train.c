#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char dest[21];
    int mile;
} stru1;
stru1 mileage[51];

typedef struct {
    char id[5], dest[21];
    int push_cnt, rank;
} stru2;
stru2 carriage[51];

int B[51], Btop = -1, n1, n2, carriage_rank[51];

int cmp(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int search(int n) {
    for (int i = 0; i < n2; i++) {
        if (strcmp(carriage[n].dest, mileage[i].dest) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    int i;
    scanf("%d", &n1);
    for (i = 0; i < n1; i++) {
        scanf("%s%d", mileage[i].dest, &mileage[i].mile);
    }
    scanf("%d", &n2);
    int tmp = n2;
    Btop = n2 - 1;
    while (tmp--) {
        scanf("%s%s", carriage[tmp].id, carriage[tmp].dest);
        B[tmp] = tmp;
        carriage[tmp].push_cnt = 0;
        carriage[tmp].rank = carriage_rank[tmp] = search(tmp);
    }
    qsort(carriage_rank, n2, sizeof(int), cmp);
    int max = carriage_rank[0], finished = 1, tot_cnt = 0, j = 0, k = 0;
    while (Btop != -1) {
        if (carriage[B[Btop]].rank == max) {
            if (finished) {
                printf("%s ", carriage[B[Btop]].id);
                tot_cnt += ++carriage[B[Btop]].push_cnt;
                n2--;
            } else {
                printf("%s ", carriage[B[Btop]].id);
                tot_cnt += carriage[B[Btop]].push_cnt + 2;
                n2--;
                for (j = Btop; j < n2; j++) {
                    B[j] = B[j + 1];
                    Btop++;
                }
            }
            finished = 1;
            max = carriage_rank[++k];
        } else {
            finished = 0;
            carriage[B[Btop]].push_cnt++;
        }
        Btop--;
    }
    printf("\n%d", tot_cnt);
    return 0;
}
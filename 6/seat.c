#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    char name[21];
    int seat;
} list;
list students[100];

int cmp_num(const void *a, const void *b) {
    return ((list *) a)->num - ((list *) b)->num;
}

int cmp_seat(const void *a, const void *b) {
    int flag = ((list *) a)->seat - ((list *) b)->seat;
    if (flag == 0)
        flag = ((list *) a)->num - ((list *) b)->num;
    return flag;
}

int seats[200];

int main() {
    FILE *fp;
    fp = fopen("in.txt", "r");
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d%s%d", &students[i].num, students[i].name, &students[i].seat);
        seats[students[i].seat] = 1;
    }
    qsort(students, n, sizeof(list), cmp_seat);
    int max = students[n - 1].seat;
    int num = n, min = n < max ? n : max;
    for (i = 1; i <= min; i++) {
        for (int j = min; j >= 0; j--) {
            if (seats[j] == 1) {
                min = j;
                break;
            }
        }
        if (seats[i] == 0) {
            seats[students[--num].seat] = 0;
            students[num].seat = i;
            seats[i] = 1;
        }
    }
    qsort(students, n, sizeof(list), cmp_seat);
    int flag = students[0].seat;
    max = students[n - 1].seat;
    for (i = 1; i < n; i++) {
        if (students[i].seat == flag)
            students[i].seat = ++max;
        flag = students[i].seat;
    }
    qsort(students, n, sizeof(list), cmp_num);
    freopen("out.txt", "w", stdout);
    for (i = 0; i < n; i++) {
        printf("%d %s %d\n", students[i].num, students[i].name, students[i].seat);
    }
    fclose(fp);
    fclose(stdout);
    return 0;
}
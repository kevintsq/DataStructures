#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[21];
    int num;
} list;
list info[101];

int cmp(const void *a, const void *b) {
    int flag = strcmp(((list *) a)->name, ((list *) b)->name);
    if (flag == 0)
        flag = ((list *) a)->num - ((list *) b)->num;
    return flag;
}

int main() {
    int n, i, cnt = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%s%d", info[i].name, &info[i].num);
    qsort(info, n, sizeof(info[0]), cmp);
    printf("%s %d\n", info[0].name, info[0].num);
    for (i = 1; i < n; i++) {
        if (info[i].num == info[i - 1].num)
            continue;
        if (strcmp(info[i].name, info[i - 1].name) == 0)
            printf("%s_%d %d\n", info[i].name, ++cnt, info[i].num);
        else {
            printf("%s %d\n", info[i].name, info[i].num);
            cnt = 0;
        }
    }
    return 0;
}
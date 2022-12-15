#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char name[21];
    long long num;
} record;
record info[101];
int cmp(const void *a, const void *b)
{
    return strcmp(((record *)a)->name, ((record *)b)->name);
}
int main()
{
    int n, i, j, cnt = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%s%lld", info[i].name, &info[i].num);
    qsort(info, n, sizeof(info[0]), cmp);
    printf("%s %lld\n", info[0].name, info[0].num);
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
            if (info[i].num == info[j].num)
                goto there;
        if (strcmp(info[i].name, info[i - 1].name) == 0)
            printf("%s_%d %lld\n", info[i].name, ++cnt, info[i].num);
        else
        {
            printf("%s %lld\n", info[i].name, info[i].num);
            cnt = 0;
        }
    there:;
    }
    return 0;
}
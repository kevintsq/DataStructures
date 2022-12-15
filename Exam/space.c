#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int start, end;
} stru;
stru mem[101];

int cmp(const void *a, const void *b) {
    return ((stru *)a)->start - ((stru *)b)->end;
}

int main() {
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d%d", &mem[i].start, &mem[i].end);
    }
    qsort(mem, n, sizeof(stru), cmp);
    printf("%d ", mem[0].start);
    for (i = 1; i < n; i++) {
        if (mem[i].start - 1 != mem[i - 1].end)
            printf("%d\n%d ", mem[i - 1].end, mem[i].start);
    }
    printf("%d", mem[n - 1].end);
    return 0;
}
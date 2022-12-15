#include <stdio.h>

typedef struct node {
    int x1;
    int y1;
    int x2;
    int y2;
    struct node *next;
} list;
list line[10000];
int cnt[10000];

int main() {
    int n, i, j, max_idx = 0, max_cnt = 0;
    list *p;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d%d%d%d", &line[i].x1, &line[i].y1, &line[i].x2, &line[i].y2);
        line[i].next = NULL;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            if (j == i)
                continue;
            if (line[j].x1 == line[i].x2 && line[j].y1 == line[i].y2)
                line[i].next = &line[j];
        }
    for (i = 0; i < n; i++)
        for (p = &line[i]; p != NULL; p = p->next) {
            cnt[i]++;
            if (cnt[i] > max_cnt) {
                max_cnt = cnt[i];
                max_idx = i;
            }
        }
    printf("%d %d %d", max_cnt, line[max_idx].x1, line[max_idx].y1);
    return 0;
}
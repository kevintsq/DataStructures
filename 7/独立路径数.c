#include<stdio.h>
#define M 1005
int n, m, ans[M], t = 0, head[M], vi[M];
struct Node {
    int to, next, id;
} e[M];
struct node {
    int x, y, id;
} a[M], tmp;
void add(int x, int y, int id) {
    e[++t].to = y;
    e[t].next = head[x];
    e[t].id = id;
    head[x] = t;
    e[++t].to = x;
    e[t].next = head[y];
    e[t].id = id;
    head[y] = t;
}
void DFS(int x, int num) {
    int i;
    if (x == n) {
        for (i = 1; i < num; i++) printf("%d ", ans[i]);
        printf("%d\n", ans[num]);
        return;
    }
    i = head[x];
    while (i) {
        if (!vi[e[i].to]) {
            ans[num + 1] = e[i].id;
            vi[e[i].to] = 1;
            DFS(e[i].to, num + 1);
            vi[e[i].to] = 0;
        }
        i = e[i].next;
    }
}
int main() {
    scanf("%d%d", &n, &m);
    int i, j;
    for (i = 1; i <= m; i++) {
        scanf("%d%d%d", &a[i].id, &a[i].x, &a[i].y);
    }
    for (i = 1; i <= m; i++) {
        for (j = i + 1; j <= m; j++) {
            if (a[i].id < a[j].id) {
                tmp.id = a[i].id;
                tmp.x = a[i].x;
                tmp.y = a[i].y;
                a[i].id = a[j].id;
                a[i].x = a[j].x;
                a[i].y = a[j].y;
                a[j].id = tmp.id;
                a[j].x = tmp.x;
                a[j].y = tmp.y;
            }
        }
    }
    for (i = 1; i <= m; i++) {
        add(a[i].x + 1, a[i].y + 1, a[i].id);
    }
    vi[1] = 1;
    DFS(1, 0);
    return 0;
}

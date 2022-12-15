#include<stdio.h>
#include<string.h>

#define mem(a, b) memset(a,b,sizeof(a))
int n, first[100010], i, j, ce = -1, tmp, bfs_clock[100010], a[100010], ans[1010], fa[100010], len;
int queue[100010], head, tail, vis[100010];
char name[100010][30], s[30], tar[30];
typedef struct {
    int u, v, next;
} Edge;
Edge e[200010];

void addEdge(int a, int b) {
    e[++ce] = (Edge) {a, b, first[a]};
    first[a] = ce;
    e[++ce] = (Edge) {b, a, first[b]};
    first[b] = ce;
}

void bfs(int S) {
    head = 1;
    tail = 0;
    queue[++tail] = S;
    vis[S] = 1;
    fa[S] = -1;
    int cnt = 0, i;
    bfs_clock[S] = ++cnt;
    while (head <= tail) {
        int now = queue[head++], temp[300], temp_len = 0;
        for (i = first[now]; i != -1; i = e[i].next)
            if (!vis[e[i].v])temp[++temp_len] = e[i].v;
        for (i = temp_len; i; i--) {
            vis[temp[i]] = 1;
            fa[temp[i]] = now;
            bfs_clock[temp[i]] = ++cnt;
            queue[++tail] = temp[i];
        }
    }
}

int cmp(int x, int y) {
    return (a[x] != a[y]) ? a[x] > a[y] : bfs_clock[x] > bfs_clock[y];
}

void print(int x) {
    int now = x, temp[300], temp_len = 0, i;
    while (now != -1)temp[++temp_len] = now, now = fa[now];
    printf("%s:", name[temp[temp_len]]);
    for (i = temp_len - 1; i; i--)printf("\\%s", name[temp[i]]);
    puts("");
}

int main() {
    mem(first, -1);
    scanf("%s%d", tar, &n);
    FILE *in = fopen("files.txt", "r");
    for (i = 0; i < n; i++) {
        fscanf(in, "%s%s%d%d", name[i], s, &tmp, &a[i]);
        if (!strcmp(s, "*"))continue;
        for (j = 0; j < i; j++)
            if (!strcmp(s, name[j]))addEdge(i, j);
        if (!strcmp(name[i], tar))ans[++len] = i;
    }
    for (i = 0; i < n; i++)if (!vis[i])bfs(i);
    for (i = len; i > 1; i--)
        for (j = 1; j < i; j++)
            if (cmp(ans[j], ans[j + 1]))tmp = ans[j + 1], ans[j + 1] = ans[j], ans[j] = tmp;
    for (i = 1; i <= len; i++)print(ans[i]);
    return 0;
}
/*
test.c 49
 */
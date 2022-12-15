#include <stdio.h>
#include <string.h>

int n, m, a[105][105];
int vis[105], ok, q[105];

void dfs(int x) {
    if (!ok) {
        printf("%d", x);
        ok = 1;
    } else
        printf(" %d", x);
    vis[x] = 1;
    for (int i = 1; i <= n; i++)
        if (a[x][i] && !vis[i])
            dfs(i);
}

void bfs(int t) {
    q[1] = t;
    int l = 1, r = 1, i;
    while (l <= r) {
        int x = q[l];
        l++;
        if (vis[x])
            continue;
        if (!ok) {
            printf("%d", x);
            ok = 1;
        } else
            printf(" %d", x);
        vis[x] = 1;
        for (i = 1; i <= n; i++)
            if (a[x][i] && !vis[i])
                q[++r] = i;
    }
    memset(vis, 0, sizeof(vis));
}

int main() {
    scanf("%d%d", &n, &m);
    int i;
    for (i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        a[y][x] = a[x][y] = 1;
    }
    ok = 0;
    dfs(0);
    printf("\n");
    memset(vis, 0, sizeof(vis));
    ok = 0;
    bfs(0);
    printf("\n");
    scanf("%d", &i);
    vis[i] = 1;
    ok = 0;
    dfs(0);
    printf("\n");
    memset(vis, 0, sizeof(vis));
    vis[i] = 1;
    ok = 0;
    bfs(0);
    printf("\n");
    return 0;
}

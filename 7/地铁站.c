#include <stdio.h>
#include <string.h>
#define N 1005
int n, a[15], k = 0, tot = 0, head[N], d[N], q[N * 10], v[N], from[N], ans[N];
char s[25], s1[25], s2[25], name[N][25];
struct NODE {
    int from, to, next, id;
} e[N];
int find(char s[]) {
    int i, t = -1;
    for (i = 1; i <= tot; i++)
        if (strcmp(s, name[i]) == 0) {
            t = i;
            break;
        }
    return t;
}
void add(int x, int y, int z) {
    e[++k] = (struct NODE) {x, y, head[x], z};
    head[x] = k;
}
void Dijkstra(int xx, int yy) {
    int i;
    for (i = 1; i <= tot; i++) d[i] = 100000;
    d[xx] = 0;
    q[1] = xx;
    v[xx] = 1;
    int l = 1, r = 1;
    while (l <= r) {
        int x = q[l++];
        v[x] = 0;
        i = head[x];
        while (i) {
            if (d[e[i].to] > d[x] + 1) {
                d[e[i].to] = d[x] + 1;
                from[e[i].to] = i;
                if (!v[e[i].to]) {
                    v[e[i].to] = 1;
                    q[++r] = e[i].to;
                }
            }
            i = e[i].next;
        }
    }
    tot = 0;
    while (yy != xx) {
        ans[++tot] = from[yy];
        yy = e[from[yy]].from;
    }
    printf("%s", name[xx]);
    int num = 0;
    for (i = tot; i >= 1; i--) {
        if (i != tot && e[ans[i]].id != e[ans[i + 1]].id) {
            printf("-%d(%d)-%s", e[ans[i + 1]].id, num, name[e[ans[i]].from]);
            num = 1;
        } else num++;
    }
    printf("-%d(%d)-%s\n", e[ans[1]].id, num, name[e[ans[1]].to]);
}
int main() {
    FILE *fp = fopen("bgstations.txt", "r");
    fscanf(fp, "%d", &n);
    int i, j, x, y;
    for (i = 1; i <= n; i++) {
        fscanf(fp, "%d%d", &x, &a[i]);
        int pre = -1;
        for (j = 1; j <= a[i]; j++) {
            fscanf(fp, "%s%d", s, &y);
            int t = find(s);
            if (t == -1) {
                t = ++tot;
                strcpy(name[tot], s);
            }
            if (pre != -1) {
                add(pre, t, x);
                add(t, pre, x);
            }
            pre = t;
        }
    }
    scanf("%s%s", s1, s2);
    int t1 = find(s1);
    int t2 = find(s2);
    Dijkstra(t1, t2);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct e {
    int adjvex, id;
    struct e *next;
} edge;

typedef struct v {
    edge *next;
} vertex;

vertex graph[1000];
int visited[1000], paths[1000], n;

edge *insert(edge *head, int avex, int eid) {
    edge *e, *p;
    e = (edge *) malloc(sizeof(edge));
    e->adjvex = avex;
    e->next = NULL;
    if (head != NULL) {
        for (p = head; p->next != NULL; p = p->next);
        p->next = e;
        e->id = eid;
    } else {
        head = e;
        head->id = eid;
    }
    return head;
}

void create(vertex G[]) {
    int e, i, eid, v1, v2;
    scanf("%d%d", &n, &e);
    for (i = 0; i < e; i++) {
        scanf("%d%d%d", &eid, &v1, &v2);
        G[v1].next = insert(G[v1].next, v2, eid);
        G[v2].next = insert(G[v2].next, v1, eid);
    }
}

void print_path(int pos) {
    for (int i = 0; i < pos; i++) {
        printf("%d ", paths[i]);
    }
    printf("\n");
}

void DFS(vertex G[], int v, int pos) {
    if (G[v].next != NULL) {
        edge *p;
        visited[v] = 1;
        if (v == n - 1) {
            print_path(pos);
            return;
        }
        for (p = G[v].next; p != NULL; p = p->next)
            if (!visited[p->adjvex]) {
                paths[pos] = p->id;
                visited[p->adjvex] = 1;
                DFS(G, p->adjvex, pos + 1);
                visited[p->adjvex] = 0;
            }
    }
}

edge *sort(edge *start) {
    if (start->next == NULL)
        return start;
    edge *p, *p_last, *q, *q_last, *flag, *flag_last, *temp;
    int min;
    for (p_last = p = start; p->next != NULL; p_last = p, p = p->next) {
        min = p->id;
        flag = p;
        flag_last = p_last;
        for (q_last = q = p->next; q != NULL; q_last = q, q = q->next)
            if (q->id < min) {
                min = q->id;
                flag = q;
                flag_last = q_last;
            }
        if (flag != p) {
            if (p_last == p) {
                start = flag;
                temp = flag->next;
                flag->next = p->next;
                flag_last->next = p;
                p->next = temp;
                p = start;
            } else {
                p_last->next = flag;
                temp = flag->next;
                flag->next = p->next;
                flag_last->next = p;
                p->next = temp;
                p = flag;
            }
        }
    }
    p = NULL;
    return start;
}

int main() {
    create(graph);
    for (int i = 0; i < n; i++) {
        graph[i].next = sort(graph[i].next);
    }
    DFS(graph, 0, 0);
    return 0;
}
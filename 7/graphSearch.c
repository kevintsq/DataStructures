#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct e {
    int adjvex;
    struct e *next;
} edge;

typedef struct v {
    int deleted;
    edge *next;
} vertex;

vertex graph[1000];
int visited[1000], queue[1000], front, end;

edge *insert(edge *head, int avex) {
    edge *e, *p;
    e = (edge *) malloc(sizeof(edge));
    e->adjvex = avex;
    e->next = NULL;
    if (head != NULL) {
        for (p = head; p->next != NULL; p = p->next);
        p->next = e;
    } else
        head = e;
    return head;
}

int create(vertex G[]) {
    int v, e, i, v1, v2;
    scanf("%d%d", &v, &e);
    for (i = 0; i < e; i++) {
        scanf("%d%d", &v1, &v2);
        G[v1].next = insert(G[v1].next, v2);
        G[v2].next = insert(G[v2].next, v1);
    }
    return v;
}

void DFS(vertex G[], int v) {
    if (G[v].next != NULL) {
        edge *p;
        visited[v] = 1;
        printf("%d ", v);
        for (p = G[v].next; p != NULL; p = p->next)
            if (!visited[p->adjvex])
                DFS(G, p->adjvex);
    }
}

void DFSearch(vertex G[], int n) {
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++)
        if (!visited[i])
            DFS(G, i);
}

void BFS(vertex G[], int v) {
    if (G[v].next != NULL) {
        edge *p;
        printf("%d ", v);
        visited[v] = 1;
        queue[end++] = v;
        while (front != end) {
            v = queue[front++];
            for (p = G[v].next; p != NULL; p = p->next)
                if (!visited[p->adjvex]) {
                    printf("%d ", p->adjvex);
                    visited[p->adjvex] = 1;
                    queue[end++] = p->adjvex;
                }
        }
    }
}

void BFSearch(vertex G[], int n) {
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++)
        if (!visited[i])
            BFS(G, i);
}

edge *sort(edge *start) {
    if (start->next == NULL)
        return start;
    edge *p, *p_last, *q, *q_last, *flag, *flag_last, *temp;
    int min;
    for (p_last = p = start; p->next != NULL; p_last = p, p = p->next) {
        min = p->adjvex;
        flag = p;
        flag_last = p_last;
        for (q_last = q = p->next; q != NULL; q_last = q, q = q->next)
            if (q->adjvex < min) {
                min = q->adjvex;
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

edge *del_edge(edge *start, int v) {
    edge *p, *q, *p_last;
    for (p_last = p = start; p != NULL; p = p_last->next) {
        if (p->adjvex == v) {
            if (p == start && start->next == NULL) {
                start = (edge *) malloc(sizeof(edge));
                start->next = NULL;
                return start;
            }
            if (p == start) {
                q = start;
                p_last = start = p->next;
                free(q);
            } else if (p->next == NULL) {
                p_last->next = NULL;
                free(p);
                return start;
            } else {
                q = p;
                p_last->next = p->next;
                free(q);
            }
        } else
            p_last = p;
    }
    return start;
}


void delete(vertex G[], int v) {
    edge *p, *p_last = NULL;
    for (p = G[v].next; p != NULL; p = p->next) {
        free(p_last);
        G[p->adjvex].next = del_edge(G[p->adjvex].next, v);
        p_last = p;
    }
    free(p_last);
    G[v].next = NULL;
}

int main() {
    int n = create(graph);
    for (int i = 0; i < n; i++) {
        graph[i].next = sort(graph[i].next);
    }
    DFSearch(graph, n);
    puts("");
    BFSearch(graph, n);
    puts("");
    scanf("%d", &n);
    delete(graph, n);
    DFSearch(graph, n);
    puts("");
    BFSearch(graph, n);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int num;
    struct node *next;
} list;

list *create_list(list *start, int n) {
    int i;
    list *p;
    start = p = (list *) malloc(sizeof(list));
    start->next = NULL;
    for (i = 1; i < n; i++) {
        p->num = i;
        p = p->next = (list *) malloc(sizeof(list));
    }
    p->num = i;
    p->next = start;
    return start;
}

/* n只猴子围成一圈，从1到n顺序编号。
 * 从第q只猴子开始，从1到m报数，凡报到m的猴子退出竞选，
 * 下一次又从退出的那只猴子的下一只开始从1到m报数，直至剩下的最后一只为大王。*/
int josephus(list *p, int m, int q) {
    int i;
    list *r;
    for (i = 1; i < q; i++) {
        p = p->next;
    }
    while (p->next != p) {
        for (i = 1; i < m - 1; i++) {
            p = p->next;
        }
        r = p->next;
        p->next = r->next;
        free(r);
        p = p->next;
    }
    return p->num;
}

int main() {
    int n, m, q, end;
    scanf("%d%d%d", &n, &m, &q);
    list *start = NULL;
    start = create_list(start, n);
    end = josephus(start, m, q);
    printf("%d", end);
    return 0;
}
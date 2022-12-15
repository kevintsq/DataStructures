#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int coef;
    int exp;
    struct node *next;
} list;

list *sort(list *start) {
    if (start->next == NULL)
        return start;
    list *p = start, *p_last, *q, *q_last, *flag, *flag_last, *temp;
    int max;
    for (p_last = p; p->next->next != NULL; p_last = p, p = p->next) {
        max = p->exp;
        flag = p;
        flag_last = p_last;
        for (q_last = q = p->next; q->next != NULL; q_last = q, q = q->next)
            if (q->exp > max) {
                max = q->exp;
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
    p->next = NULL;
    return start;
}

list *create_list(list *start) {
    list *p, *p_last;
    start = p = (list *) malloc(sizeof(list));
    do {
        scanf("%d%d", &(p->coef), &(p->exp));
        p_last = p;
        p = p->next = (list *) malloc(sizeof(list));
    } while (getchar() != '\n');
    p_last->next = NULL;
    return start;
}

list *multiple(list *expr1, list *expr2) {
    list *p, *q, *r, *result;
    result = r = (list *) malloc(sizeof(list));
    for (p = expr1; p != NULL; p = p->next)
        for (q = expr2; q != NULL; q = q->next) {
            r->coef = p->coef * q->coef;
            r->exp = p->exp + q->exp;
            r = r->next = (list *) malloc(sizeof(list));
        }
    r->next = NULL;
    result = sort(result);
    return result;
}

list *simplify(list *start) {
    list *p, *p_last = start, *tmp;
    for (p = start->next; p != NULL; p_last = p, p = p->next)
        if (p->exp == p_last->exp) {
            p_last->coef += p->coef;
            p_last->next = p->next;
            tmp = p;
            free(tmp);
            p = p_last;
        }
    return start;
}

int main() {
    list *expr1 = NULL, *expr2 = NULL, *result, *p;
    expr1 = create_list(expr1);
    expr2 = create_list(expr2);
    result = multiple(expr1, expr2);
    result = simplify(result);
    for (p = result; p != NULL; p = p->next)
        printf("%d %d ", p->coef, p->exp);
    return 0;
}
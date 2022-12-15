#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[51];
    char author[21];
    char publisher[31];
    int date;
    struct node *next;
} list;

list *create_list(list *start) {
    FILE *fp;
    fp = fopen("books.txt", "r");
    list *p;
    start = p = (list *) malloc(sizeof(list));
    start->next = NULL;
    while (fscanf(fp, "%s%s%s%d", p->name, p->author, p->publisher, &(p->date)) != EOF) {
        p = p->next = (list *) malloc(sizeof(list));
        p->next = NULL;
    }
    fclose(fp);
    return start;
}
//新建链表函数写得有一点问题，导致排序函数要多加一行
list *sort_list(list *start) {
    if (start->next == NULL)
        return start;
    list *p, *p_last, *q, *q_last, *flag, *flag_last, *temp;
    char *min;
    for (p_last = p = start; p->next->next != NULL; p_last = p, p = p->next) {
        min = p->name;
        flag = p;
        flag_last = p_last;
        for (q_last = q = p->next; q->next != NULL; q_last = q, q = q->next) {
            if (strcmp(q->name, min) < 0) {
                min = q->name;
                flag = q;
                flag_last = q_last;
            }
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

list *insert(list *start) {
    if (!isprint(*(start->name))) {
        scanf("%s%s%s%d", start->name, start->author, start->publisher, &(start->date));
        return start;
    }
    list *p, *new, *temp = start;
    new = (list *) malloc(sizeof(list));
    scanf("%s%s%s%d", new->name, new->author, new->publisher, &(new->date));
    for (p = start; p != NULL; p = p->next) {
        if (strcmp(p->name, new->name) < 0)
            temp = p;
        else if (p == start) {
            new->next = start;
            return new;
        } else {
            new->next = temp->next;
            temp->next = new;
            return start;
        }
        if (p->next == NULL) {
            new->next = p->next;
            p->next = new;
            return start;
        }
    }
    return start;
}

void find(list *start) {
    list *p;
    char s[51];
    scanf("%s", s);
    for (p = start; p != NULL; p = p->next) {
        if (strstr(p->name, s) != NULL) {
            printf("%-50s%-20s%-30s%-10d\n", p->name, p->author, p->publisher, p->date);
        }
    }
}

list *delete(list *start) {
    list *p, *q, *p_last;
    char s[51];
    scanf("%s", s);
    for (p_last = p = start; p != NULL; p = p_last->next) {
        if (strstr(p->name, s) != NULL) {
            if (p == start && start->next == NULL) {
                start = (list *) malloc(sizeof(list));
                start->next = NULL;
                return start;
            }
            if (p == start) {
                q = start;
                start = p->next;
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

int main() {
    list *start = NULL, *p;
    start = create_list(start);
    start = sort_list(start);
    int n;
    while (scanf("%d", &n), n != 0) {
        switch (n) {
            case 1:
                start = insert(start);
                break;
            case 2:
                find(start);
                break;
            case 3:
                start = delete(start);
                break;
        }
    }
    freopen("ordered.txt", "w", stdout);
    if (!isprint(*(start->name))) {
        printf("\n");
    } else
        for (p = start; p != NULL; p = p->next) {
            printf("%-50s%-20s%-30s%-10d\n", p->name, p->author, p->publisher, p->date);
        }
    fclose(stdout);
    return 0;
}

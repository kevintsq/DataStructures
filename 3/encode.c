#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char dict[96], hash[129];
typedef struct node {
    char c;
    struct node *next;
} list;

list *create_list(list *start) {
    int i;
    list *p;
    start = p = (list *) malloc(sizeof(list));
    start->next = NULL;
    for (i = 0; i < 94; i++) {
        p->c = dict[i];
        p = p->next = (list *) malloc(sizeof(list));
    }
    p->c = dict[i];
    p->next = start;
    return start;
}

void josephus(list *p) {
    list *r, *p_last = p;
    int i, tmp;
    while (p_last->next != p)
        p_last = p_last->next;
    do {
        tmp = p->c;
        p_last->next = p->next;
        r = p;
        p = p->next;
        free(r);
        for (i = 1; i < tmp - 1; i++) {
            p = p->next;
        }
        p_last = p;
        p = p->next;
        hash[tmp] = p->c;
    } while (p->next != p);
    hash[p->c] = dict[0];  // 环中剩下的最后一个字母，则它的密文字符为明码的第一个字母。
}

int map(char s) {
    if (s != EOF) {
        if (isprint(s))
            return hash[s];
        else
            return s;
    } else {
        fclose(stdout);
        exit(0);
    }
}

int main() {
    char dict_raw[33];
    gets(dict_raw);
    int i, j, k = 0;
    dict[0] = dict_raw[0];
    for (i = 1; i < strlen(dict_raw); i++) {
        for (j = 0; j < i; j++)
            if (dict_raw[j] == dict_raw[i])
                goto there;
        dict[++k] = dict_raw[i];
        there:;
    }
    int base = strlen(dict), break_flag = 0;
    for (k = 32; k <= 126; k++) {
        for (j = 0; j < base; j++)
            if (k == dict[j]) {
                break_flag = 1;
                break;
            }
        if (!break_flag)
            dict[base++] = k;
        break_flag = 0;
    }
    list *start = NULL;
    start = create_list(start);
    josephus(start);
    FILE *fp;
    fp = fopen("in.txt", "r");
    freopen("in_crpyt.txt", "w", stdout);
    for (i = 0; (putchar(map(getc(fp)))); i++);
    return 0;
}
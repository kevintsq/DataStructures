#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char Word[32];
    int cnt;
    struct node *next;
} list;

list *put_word_in_list(char *word, list *words) {
    list *p = words, *p_last;
    for (p_last = p; p != NULL; p_last = p, p = p->next)
        if (strcmp(word, p->Word) == 0) {
            (p->cnt)++;
            return words;
        }
    p = (list *) malloc(sizeof(list));
    strcpy(p->Word, word);
    p->cnt = 1;
    p->next = NULL;
    if (p_last != NULL)
        p_last->next = p;
    if (words == NULL)
        words = p;
    return words;
}

list *sort(list *start) {
    if (start->next == NULL)
        return start;
    list *p, *p_last, *q, *q_last, *flag, *flag_last, *temp;
    char *min;
    for (p_last = p = start; p->next != NULL; p_last = p, p = p->next) {
        min = p->Word;
        flag = p;
        flag_last = p_last;
        for (q_last = q = p->next; q != NULL; q_last = q, q = q->next)
            if (strcmp(q->Word, min) < 0) {
                min = q->Word;
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
    freopen("article.txt", "r", stdin);
    int i = 0;
    char tmp, s[32];
    list *words = NULL, *p;
    while (1) {
        if (isalpha(tmp = getchar())) {
            if (isupper(tmp))
                s[i++] = tolower(tmp);
            else
                s[i++] = tmp;
        } else if (i == 0) {
            if (tmp == EOF)
                break;
        } else {
            s[i] = '\0';
            i = 0;
            words = put_word_in_list(s, words);
        }
    }
    words = sort(words);
    for (p = words; p != NULL; p = p->next)
        printf("%s %d\n", p->Word, p->cnt);
    fclose(stdin);
    return 0;
}
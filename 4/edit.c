#include <stdio.h>
#include <string.h>

#define len (int)strlen

struct {
    int op;
    int pos;
    char str[BUFSIZ];
} edit[100];

char *insert(char s[], int pos, char str[]) {
    int i, j, s_len = len(s), str_len = len(str);
    s[s_len + str_len] = '\0';
    for (i = s_len - 1; i >= pos; i--) {
        s[i + str_len] = s[i];
    }
    for (i = pos, j = 0; j < str_len; i++, j++) {
        s[i] = str[j];
    }
    return s;
}

char *delete(char s[], int pos, int num) {
    int i, s_len = len(s);
    if (pos + num >= s_len) {
        s[pos] = '\0';
    } else {
        for (i = pos; i < s_len - num; i++) {
            s[i] = s[i + num];
        }
        s[i] = '\0';
    }
    return s;
}

int main() {
    char s[BUFSIZ];
    gets(s);
    int n, top, i;
    scanf("%d", &n);
    for (top = 0; top < n; top++) {
        scanf("%d%d%s", &edit[top].op, &edit[top].pos, edit[top].str);
    }
    for (i = top - 1; i >= 0; i--) {
        switch (edit[i].op) {
            case 1:
                delete(s, edit[i].pos, len(edit[i].str));
                break;
            case 2:
                insert(s, edit[i].pos, edit[i].str);
                break;
        }
    }
    while (1) {
        scanf("%d", &n);
        if (n == -1)
            break;
        if (n == 3 && top > 0) {
            top--;
            continue;
        }
        edit[top].op = n;
        if (n == 2) {
            scanf("%d%d", &edit[top].pos, &n);
            for (i = 0; i < n; i++) edit[top].str[i] = '*';
            edit[top].str[i] = '\0';
        } else if (n == 1) {
            scanf("%d%s", &edit[top].pos, edit[top].str);
        }
        top++;
    }
    for (i = 0; i < top; i++) {
        switch (edit[i].op) {
            case 1:
                insert(s, edit[i].pos, edit[i].str);
                break;
            case 2:
                delete(s, edit[i].pos, len(edit[i].str));
                break;
        }
    }
    puts(s);
    return 0;
}
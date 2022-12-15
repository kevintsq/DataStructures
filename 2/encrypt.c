#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char dict[27];

int map(char s) {
    if (islower(s))
        return dict[s - 'a'];
    if (s == EOF) {
        fclose(stdout);
        exit(0);
    }
    return s;
}

int main() {
    char dict_raw[51];
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
    for (k = 'z'; k >= 'a'; k--) {
        for (j = 0; j < base; j++)
            if (k == dict[j]) {
                break_flag = 1;
                break;
            }
        if (!break_flag)
            dict[base++] = k;
        break_flag = 0;
    }
    FILE *fp;
    fp = fopen("encrypt.txt", "r");
    freopen("output.txt", "w", stdout);
    for (i = 0; (putchar(map(getc(fp)))); i++);
}

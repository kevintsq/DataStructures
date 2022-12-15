#include <stdio.h>
#include <string.h>

void init(char raw[], char s[]) {
    int i, j;
    for (i = 0; i < strlen(raw); i++)
        if (raw[i] != '0')
            break;
    for (j = 0; i < strlen(raw); j++, i++)
        s[j] = raw[i];
    s[j] = '\0';
}

int a_is_smaller(char a[], char b[]) {
    if (strlen(a) < strlen(b))
        return 1;
    if (strlen(a) > strlen(b))
        return 0;
    if (strcmp(a, b) > 0)
        return 0;
    return 1;
}

void subtract(char a[], char b[]) {
    int c[81], i, j, k, a_len = strlen(a);
    for (i = a_len - 1, j = strlen(b) - 1; j >= 0; i--, j--) {
        if (a[i] >= b[j])
            c[i] = a[i] - b[j];
        else {
            c[i] = a[i] - b[j] + 10;
            if (a[i - 1] == '0') {
                a[i - 1] = '9';
                a[i - 2]--;
            } else
                a[i - 1]--;
            for (k = 2; k < strlen(a); k++)
                if (a[i - k] < '0') {
                    a[i - k] = '9';
                    a[i - k - 1]--;
                }
        }
    }
    for (; i >= 0; i--)
        c[i] = a[i] - '0';
    for (i = 0; i < a_len - 1; i++)
        if (c[i] != 0)
            break;
    for (; i <= a_len - 1; i++)
        printf("%d", c[i]);
}

int main() {
    char raw_a[81], raw_b[81];
    char a[81], b[81];
    scanf("%s%s", raw_a, raw_b);
    init(raw_a, a);
    init(raw_b, b);
    if (strcmp(a, b) == 0) {
        printf("%d", 0);
        return 0;
    }
    if (a_is_smaller(a, b)) {
        printf("-");
        subtract(b, a);
    } else
        subtract(a, b);
    return 0;
}

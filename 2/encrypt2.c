#include <stdio.h>

int main() {
    char key[2][100] = {'\0'}, ch;
    int i, j;
    FILE *fp1, *fp2;
    fp1 = fopen("encrypt.txt", "r");
    fp2 = fopen("output.txt", "w");
    gets(key[0]);
    for (i = 0; key[0][i] != '\0'; i++);
    for (ch = 'z'; ch >= 'a'; ch--, i++)
        key[0][i] = ch;
    for (j = 0, ch = 'a'; ch <= 'z'; ch++, j++)
        key[1][j] = ch;
    for (i = 1; key[0][i] != '\0'; i++) {
        for (j = i - 1; j >= 0 && key[0][i] != key[0][j]; j--);
        if (j != -1) {
            for (j = i; key[0][j] != '\0'; j++)
                key[0][j] = key[0][j + 1];
            i--;
        }
    }
    while ((ch = fgetc(fp1)) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            for (i = 0; key[1][i] != ch; i++);
            fprintf(fp2, "%c", key[0][i]);
        } else
            fprintf(fp2, "%c", ch);
    }
    return 0;
}

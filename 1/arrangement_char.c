#include <stdio.h>
#include <string.h>

int N, mark[11];
char chars[] = "tlzgy", array[11];

void arrange(int index) {
    int i;
    if (index >= N) {
        for (i = 0; i < N; i++)
            printf("%c ", array[i]);
        printf("\n");
        return;
    }
    for (i = 0; i < N; i++)
        if (mark[i] == 0) {
            array[index] = chars[i];
            mark[i] = 1;
            arrange(index + 1);
            mark[i] = 0;
        }
}

int main() {
    N = strlen(chars);
    arrange(0);
    return 0;
}

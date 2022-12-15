#include <stdio.h>

int N, array[11], mark[11];

void arrange(int index) {
    int i;
    if (index >= N) {
        for (i = 0; i < N; i++)
            printf("%d ", array[i]);
        printf("\n");
        return;
    }
    for (i = 0; i < N; i++)
        if (mark[i] == 0) {
            array[index] = i + 1;
            mark[i] = 1;
            arrange(index + 1);
            mark[i] = 0;
        }
}

int main() {
    scanf("%d", &N);
    arrange(0);
    return 0;
}

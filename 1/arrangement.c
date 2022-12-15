#include <stdio.h>
#include <stdlib.h>

int tmp;
#define swap(a, b) tmp = a; a = b; b = tmp

int arrange(int a[], int n) {
    // 从最右端开始第一个比右边小的位置
    int i, j = -1;
    for (i = n - 2; i >= 0; i--)
        if (a[i] < a[i + 1]) {
            j = i;
            break;
        }
    // 此时已经是最大序了
    if (j == -1)
        return 0;
    // j后边比j位置大的最小的一个位置
    int k = -1, min = INT_MAX;
    for (i = j; i < n; i++)
        if (a[i] > a[j] && a[i] <= min) {
            min = a[i];
            k = i;
        }
    swap(a[j], a[k]);
    // 对j后边的序列进行反转
    int left = j + 1, right = n - 1;
    while (left < right) {
        swap(a[left], a[right]);
        left++;
        right--;
    }
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}

int fact(int n) {
    if (n == 0)
        return 1;
    else
        return n * fact(n - 1);
}

int main() {
    int n, i, a[11];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        a[i] = i + 1;
        printf("%d ", a[i]);
    }
    printf("\n");
    for (i = 0; i < fact(n); i++)
        arrange(a, n);
    return 0;
}
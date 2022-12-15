#include <stdio.h>
int n, a[100010], sum, time, now, num, all, come[100010], leave[100010];
int min(int a, int b) { return a < b ? a : b; }
int main()
{
    int i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        for (j = 1; j <= a[i]; j++)
            come[++now] = i;
        sum += a[i];
    }
    now = 0;
    num = 3;
    for (time = 1; now < sum; time++) { //num表示当前有几个窗口
        if (time <= n) {
            all += a[time];
            while (all >= num * 7 && num < 5)
                num++;
        }
        for (i = 1; i <= min(all, num); i++)
            leave[++now] = time;
        all -= min(all, num);
        if (all < num * 7 && num > 3)
            num--;
    }
    for (i = 1; i <= sum; i++)
        printf("%d : %d\n", i, leave[i] - come[i]);
    return 0;
}
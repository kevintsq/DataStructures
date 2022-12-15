#include <stdio.h>
#include <stdlib.h>

int cnt;

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sel_sort(int arr[], int n) {
    int i, j, min, flag;
    for (i = 0; i < n - 1; i++) {
        min = arr[i];
        flag = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < min) {
                min = arr[j];
                flag = j;
            }
            cnt++;
        }
        if (flag != i) {
            arr[flag] = arr[i];
            arr[i] = min;
        }
    }
}

void bubble_sort(int arr[], int n) {
    int i, j, flag;
    for (i = 0; i < n - 1; i++) {
        flag = 0;
        for (j = 0; j < n - 1 - i; j++) {
            cnt++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}

void adjust(int arr[], int i, int n) {
    int j = 2 * i + 1, temp = arr[i];
    while (j < n) {
        if (j < n - 1 && arr[j] < arr[j + 1])
            j++;
        cnt++;
        if (temp >= arr[j])
            break;
        arr[(j - 1) / 2] = arr[j];
        j = 2 * j + 1;
    }
    arr[(j - 1) / 2] = temp;
}

void heap_sort(int arr[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        adjust(arr, i, n);
    for (i = n - 1; i >= 1; i--) {
        swap(&arr[0], &arr[i]);
        adjust(arr, 0, i);
    }
}

void merge(int *restrict arr, int *restrict tmp, int left, int left_end, int right_end) {
    int i = left, j = left_end + 1, k = left;
    while (i <= left_end && j <= right_end) {
        if (arr[i] <= arr[j])
            tmp[k++] = arr[i++];
        else
            tmp[k++] = arr[j++];
    }
    while (i <= left_end)
        tmp[k++] = arr[i++];
    while (j <= right_end)
        tmp[k++] = arr[j++];
    for (i = left; i <= right_end; i++)
        arr[i] = tmp[i];
}

void mSort(int *restrict arr, int *restrict tmp, int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;
        mSort(arr, tmp, left, middle);
        mSort(arr, tmp, middle + 1, right);
        merge(arr, tmp, left, middle, right);
    }
}

void merge_sort(int arr[], int n) {
    int *tmp = (int *) malloc(sizeof(int) * n);
    if (tmp != NULL) {
        mSort(arr, tmp, 0, n - 1);
        free(tmp);
    }
}

int cmp(const void *a, const void *b) {
    cnt++;
    return *(int *) a - *(int *) b;
}

void quick_sort(int arr[], int left, int right) {
    int i, last;
    if (left < right) {
        last = left;
        for (i = left + 1; i <= right; i++) {
            cnt++;
            if (arr[i] < arr[left]) {
                swap(&arr[++last], &arr[i]);
            }
        }
        swap(&arr[left], &arr[last]);
        quick_sort(arr, left, last - 1);
        quick_sort(arr, last + 1, right);
    }
}

int main() {
    int n, type, i, s[100];
    scanf("%d%d", &n, &type);
    for (i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }
    switch (type) {
        case 1:
            sel_sort(s, n);
            break;
        case 2:
            bubble_sort(s, n);
            break;
        case 3:
            heap_sort(s, n);
            break;
        case 4:
            merge_sort(s, n);
            break;
        case 5:
            quick_sort(s, 0, n - 1);
            //qsort(s, n, sizeof(int), cmp);
            break;
    }
    for (i = 0; i < n; i++) {
        printf("%d ", s[i]);
    }
    printf("\n%d", cnt);
    return 0;
}
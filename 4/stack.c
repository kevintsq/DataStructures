#include <stdio.h>
#define MAXSIZE 100
int stack[MAXSIZE], cnt;
void push(int n){
    if (cnt > MAXSIZE){
        printf("error ");
        return;
    }
    stack[cnt++] = n;
}
void pop(){
    if (cnt == 0){
        printf("error ");
        return;
    }
    printf("%d ", stack[--cnt]);
}
int main(){
    int op = 0, n;
    while (op != -1){
        scanf("%d", &op);
        switch (op){
            case 1:
                scanf("%d", &n);
                push(n);
                break;
            case 0:
                pop();
                break;
        }
    }
    return 0;
}
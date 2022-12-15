#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 100
#define OPTR_NUM 8 //不可多！

typedef struct node {
    int data;
    struct node *left, *right;
} node;

node *create_tree(node *left, int data, node *right) {
    node *tree = (node *) malloc(sizeof(node));
    tree->data = data;
    tree->left = left;
    tree->right = right;
    return tree;
}

enum operator {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    L_P,
    R_P,
    EOE
};

const char pri[OPTR_NUM][OPTR_NUM] = { // [栈顶][当前]
        //[栈顶] +    -    *    /    %    (    )   \0 [当前]
        /* + */ '>', '>', '<', '<', '<', '<', '>', '>',
        /* - */ '>', '>', '<', '<', '<', '<', '>', '>',
        /* * */ '>', '>', '>', '>', '>', '<', '>', '>',
        /* / */ '>', '>', '>', '>', '>', '<', '>', '>',
        /* % */ '>', '>', '>', '>', '>', '<', '>', '>',
        /* ( */ '<', '<', '<', '<', '<', '<', '=', ' ',
        /* ) */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /*\0 */ '<', '<', '<', '<', '<', '<', ' ', '='};

enum operator optr2rank(char op) { //由运算符转译出编号
    switch (op) {
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '/':
            return DIV;
        case '%':
            return MOD;
        case '(':
            return L_P;
        case ')':
            return R_P;
        case '\0':
            return EOE;
        default:
            exit(-1);
    }
}

char order_between(char op1, char op2) { //比较两个运算符之间的优先级
    return pri[optr2rank(op1)][optr2rank(op2)];
}

char *rpn(char *expr) {
    char operator[MAXSIZE], *expr_rpn = (char *) malloc(MAXSIZE * sizeof(char)), *p = expr_rpn;
    int operator_top = 0;
    operator[operator_top++] = '\0'; //尾哨兵'\0'也作为头哨兵首先入栈
    while (operator_top) { //在运算符栈非空之前，逐个处理表达式中各字符
        if (isdigit(*expr)) { //若当前字符为操作数
            char *tmp, temp[16];
            int num = strtol(expr, &tmp, 10);
            sprintf(p, "%d ", num); // 直接入 RPN 串
            sprintf(temp, "%d ", num);
            p += strlen(temp);
            expr = tmp;
        } else //若当前字符为运算符
            switch (order_between(operator[operator_top - 1], *expr)) { //视其与栈顶运算符之间优先级高低分别处理
                case '<': //栈顶运算符优先级更低时
                    operator[operator_top++] = *expr;
                    expr++; //当前运算符进栈
                    break;
                case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                    operator_top--;
                    expr++; //脱括号并接收下一个字符
                    break;
                case '>': //栈顶运算符优先级更高时
                    sprintf(p, "%c ", operator[--operator_top]); //栈顶运算符出栈进入 RPN
                    p += 2;
                    break;
                default:
                    exit(-1);
            }
    }
    *p = '\0';
    return expr_rpn;
}

node *expr_tree(char *expr_rpn) {
    node *stack[MAXSIZE];
    int stack_top = 0;
    while (*expr_rpn != '\0') {
        if (isdigit(*expr_rpn)) {
            char *tmp;
            stack[stack_top++] = create_tree(NULL, strtol(expr_rpn, &tmp, 10), NULL);
            expr_rpn = tmp + 1;
        } else {
            node *right = stack[--stack_top], *left = stack[--stack_top];
            stack[stack_top++] = create_tree(left, *expr_rpn, right);
            expr_rpn += 2;
        }
    }
    return stack[0];
}

int is_leaf(node *tree) {
    return tree->left == NULL && tree->right == NULL;
}

int calculate(node *left, node *op, node *right) {
    if (is_leaf(op)) {
        return op->data;
    } else
        switch (op->data) {
            case '+':
                return calculate(left->left, left, left->right) + calculate(right->left, right, right->right);
            case '-':
                return calculate(left->left, left, left->right) - calculate(right->left, right, right->right);
            case '*':
                return calculate(left->left, left, left->right) * calculate(right->left, right, right->right);
            case '/':
                return calculate(left->left, left, left->right) / calculate(right->left, right, right->right);
            case '%':
                return calculate(left->left, left, left->right) % calculate(right->left, right, right->right);
            default:
                exit(-1);
        }
}

int main() {
    char expr_raw[MAXSIZE], expr[MAXSIZE], *expr_rpn;
    gets(expr_raw);
    int i, j;
    for (i = 0, j = 0; i < strlen(expr_raw); i++)
        if (expr_raw[i] != ' ')
            expr[j++] = expr_raw[i];
    expr[--j] = '\0';
    expr_rpn = rpn(expr);
    node *tree;
    tree = expr_tree(expr_rpn);
    printf("%c ", tree->data);
    if (is_leaf(tree->left)) {
        printf("%d ", tree->left->data);
    } else {
        printf("%c ", tree->left->data);
    }
    if (is_leaf(tree->right)) {
        printf("%d\n", tree->right->data);
    } else {
        printf("%c\n", tree->right->data);
    }
    printf("%d", calculate(tree->left, tree, tree->right));
    return 0;
}

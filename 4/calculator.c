#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSIZE 100
#define OPTR_NUM 8  //不可多！

enum operator {
    ADD, SUB, MUL, DIV, MOD, L_P, R_P, EOE
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
/*\0 */ '<', '<', '<', '<', '<', '<', ' ', '='
};

enum operator optr2rank(char op) { //由运算符转译出编号
    switch (op) {
        case '+' :
            return ADD;
        case '-' :
            return SUB;
        case '*' :
            return MUL;
        case '/' :
            return DIV;
        case '%' :
            return MOD;
        case '(' :
            return L_P;
        case ')' :
            return R_P;
        case '\0':
            return EOE;
        default  :
            exit(-1);
    }
}

int calculate(int num1, char op, int num2) {
    switch (op) {
        case '+' :
            return num1 + num2;
        case '-' :
            return num1 - num2;
        case '*' :
            return num1 * num2;
        case '/' :
            return num1 / num2;
        case '%' :
            return num1 % num2;
        default  :
            exit(-1);
    }
}

char order_between(char op1, char op2) { //比较两个运算符之间的优先级
    return pri[optr2rank(op1)][optr2rank(op2)];
}

int evaluate(char *expr) { //对无空格的表达式求值
    char operator[MAXSIZE];
    int operand[MAXSIZE], optr_top = 0, opnd_top = 0;
    operator[optr_top++] = '\0'; //尾哨兵'\0'也作为头哨兵首先入栈
    while (optr_top) { //在运算符栈非空之前，逐个处理表达式中各字符
        if (isdigit(*expr)) { //若当前字符为操作数
            char *tmp;
            operand[opnd_top++] = strtol(expr, &tmp, 10);
            expr = tmp;
        } else //若当前字符为运算符
            switch (order_between(operator[optr_top - 1], *expr)) { //视其与栈顶运算符之间优先级高低分别处理
                case '<': //栈顶运算符优先级更低时
                    operator[optr_top++] = *expr;
                    expr++; //计算推迟，当前运算符进栈
                    break;
                case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                    optr_top--;
                    expr++; //脱括号并接收下一个字符
                    break;
                case '>': { //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
                    char optr_tmp = operator[--optr_top]; //栈顶运算符出栈
                    int opnd2 = operand[--opnd_top], opnd1 = operand[--opnd_top]; //取出后、前操作数
                    operand[opnd_top++] = calculate(opnd1, optr_tmp, opnd2); //实施二元计算，结果入栈
                    break;
                }
                default :
                    exit(-1);
            }
    }
    return operand[--opnd_top]; //弹出并返回最后的计算结果
}

int main() {
    char expr_raw[MAXSIZE], expr[MAXSIZE];
    gets(expr_raw);
    int i, j;
    for (i = 0, j = 0; i < strlen(expr_raw); i++)
        if (expr_raw[i] != ' ')
            expr[j++] = expr_raw[i];
    expr[--j] = '\0';
    printf("%d", evaluate(expr));
    return 0;
}

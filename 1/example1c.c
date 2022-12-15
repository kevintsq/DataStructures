#include <stdio.h>
typedef unsigned long long ULL;
int main()
{ //为了保证结构，在最开始加上 0 +
    ULL a1 = 0, a2, a3;
    char op1 = '+', op2, op3;
    while (op1 != '=')
    {
        scanf("%llu %c", &a2, &op2);
        while (op2 == '*' || op2 == '/')
        {
            scanf("%llu %c", &a3, &op3);
            if (op2 == '*')
                a2 *= a3;
            else if (op2 == '/')
                a2 /= a3;
            op2 = op3; // 此处注意
        }
        if (op1 == '+')
            a1 += a2;
        else if (op1 == '-')
            a1 -= a2;
        op1 = op2; // 此处注意
    }
    printf("%llu", a1);
    return 0;
}

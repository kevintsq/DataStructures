#include <stdio.h>
#include <string.h>

int main()
{
    char s[101];
    gets(s);
    int i, j, s_len = strlen(s);
    if (s[0] == '0')
    {
        for (i = 2; i < s_len; i++)
            if (s[i] != '0')
                break;
        int zeros = i;
        printf("%c", s[i]);
        if (++i != s_len)
            printf(".");
        for (; i < s_len; i++)
            printf("%c", s[i]);
        printf("e-%d", zeros - 1);
    }
    else if (s[1] == '.')
        printf("%se0", s);
    else
    {
        for (i = 0; i < s_len; i++)
            if (s[i] == '.')
                break;
        printf("%c.", s[0]);
        for (j = 1; j < i; j++)
            printf("%c", s[j]);
        for (j++; j < s_len; j++)
            printf("%c", s[j]);
        printf("e%d", i - 1);
    }
    return 0;
}
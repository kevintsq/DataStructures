#include <stdio.h>
#include <string.h>

int main()
{
    char s[100];
    gets(s);
    int i, j;
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] == '-' && i > 0 && s[i - 1] < s[i + 1])
        {
            if (s[i - 1] >= '0' && s[i + 1] <= '9')
                for (j = 1; j < s[i + 1] - s[i - 1]; j++)
                    printf("%c", s[i - 1] + j);
            else if (s[i - 1] >= 'a' && s[i + 1] <= 'z')
                for (j = 1; j < s[i + 1] - s[i - 1]; j++)
                    printf("%c", s[i - 1] + j);
            else if (s[i - 1] >= 'A' && s[i + 1] <= 'Z')
                for (j = 1; j < s[i + 1] - s[i - 1]; j++)
                    printf("%c", s[i - 1] + j);
            else
                printf("%c", s[i]);
        }
        else
            printf("%c", s[i]);
    }
    return 0;
}
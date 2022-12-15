#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char raw[1000000], raw_lower[1000000], txt[1000000], tar[100], tar_lower[100], src[100];
void init()
{
    FILE *fp;
    fp = fopen("filein.txt", "r");
    int i;
    for (i = 0; (raw[i] = getc(fp)) != EOF; i++){
        if (isupper(raw[i]))
            raw_lower[i] = tolower(raw[i]);
        else
            raw_lower[i] = raw[i];
    }
    raw[i] = '\0'; // 全局变量这两行可不写
    raw_lower[i] = '\0';
    gets(tar);
    for (i = 0; i < strlen(tar); i++)
        if (isupper(tar[i]))
            tar_lower[i] = tolower(tar[i]);
        else
            tar_lower[i] = tar[i];
    gets(src);
    fclose(fp);
}
int main()
{
    init();
    int i = 0, j = 0, k = 0, tar_len = strlen(tar), src_len = strlen(src);
    char *p;
    freopen("fileout.txt", "w", stdout);
    if ((p = strstr(raw_lower, tar_lower)) == NULL)
    {
        puts(raw);
        fclose(stdout);
        return 0;
    }
    do
    {
        if (&raw_lower[i] < p)
            txt[j++] = raw[i++];
        else if (k < src_len)
            txt[j++] = src[k++];
        else
        {
            i += tar_len;
            k = 0;
            if ((p = strstr(p + tar_len, tar_lower)) == NULL)
                break;
        }
    } while (i < strlen(raw));
    while (i < strlen(raw))
        txt[j++] = raw[i++];
    txt[j] = '\0';
    puts(txt);
    fclose(stdout);
    return 0;
}

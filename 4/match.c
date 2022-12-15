#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    fp = fopen("example.c", "r");
    char line[205], p_stack[205], p_all[205], last_token = '\0';
    int i, j, in_str = 0, p_top = -1, p_all_top = -1, p_line[205];
    for (i = 1; fgets(line, 205, fp) != NULL; i++) { // 遍历每行
        for (j = 0; j < strlen(line); j++) { // 遍历每行的字符
            if (line[j] == '\'' || line[j] == '\"') {
                if (!in_str) { // 如果当前不在字符串中
                    last_token = line[j]; // 标记进入符
                    in_str = 1; // 标记进入字符串，直到这个last_token == 新的line[j]
                } else if (last_token == line[j]) { // 如果当前在字符串中，且刚才last_token == 这个line[j]
                    in_str = 0; // 标记要出字符串
                    last_token = '\0'; // 重置last_token，准备开始看括号
                }
            } else if (line[j] == '/' && line[j + 1] == '*') { // 如果遇到行内注释开头符
                if (!in_str) { // 如果当前不在字符串中
                    last_token = 's'; // 标记行内注释开始
                    in_str = 1; // 标记进入字符串，直到遇到*/
                    j++; // 多跳一个j【注：不可在字符串中跳，以防/*/*/】
                }
            } else if (line[j] == '*' && line[j + 1] == '/') { // 如果遇到行内注释结尾符，顺便多跳一个j
                if (in_str && last_token == 's') { // 如果当前在字符串中且上一符号为行内注释开头符
                    in_str = 0; // 标记要出字符串
                    last_token = '\0'; // 重置last_token，准备开始看括号
                    j++; // 多跳一个j【注：不可在条件语句中跳，因为会被误执行】
                }
            } else if (!in_str) { // 如果不在字符串中
                if (line[j] == '/' && line[j + 1] == '/') { // 整行注释直接跳过该行
                    break;
                }
                if (line[j] == '(' || line[j] == '{') {
                    p_stack[++p_top] = line[j];
                    p_all[++p_all_top] = line[j];
                    p_line[p_top] = i;
                } else
                    switch (line[j]) {
                        case ')':
                            if (p_stack[p_top] != '(') {
                                printf("without maching \'%c\' at line %d", line[j], i);
                                return 0;
                            }
                            p_top--;
                            p_all[++p_all_top] = line[j];
                            break;
                        case '}':
                            if (p_stack[p_top] == '(') {
                                printf("without maching \'%c\' at line %d", p_stack[p_top], p_line[p_top]);
                                return 0;
                            } else if (p_stack[p_top] != '{') {
                                printf("without maching \'%c\' at line %d", line[j], i);
                                return 0;
                            }
                            p_top--;
                            p_all[++p_all_top] = line[j];
                            break;
                    }
            }
        }
    }
    if (p_top != -1 && (p_stack[p_top] == '(' || p_stack[p_top] == '{')) {
        printf("without maching \'%c\' at line %d", p_stack[p_top], p_line[p_top]);
        return 0;
    }
    p_all[++p_all_top] = '\0';
    puts(p_all);
    fclose(fp);
    return 0;
}
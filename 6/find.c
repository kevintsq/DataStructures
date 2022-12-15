#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NHASH  3001
#define MULT  37

unsigned int hash(char *str) {
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)
        h = MULT * h + *p;
    return h % NHASH;
}

char words[3500][16];
char words_index[26][500][16];
typedef struct node {
    int flag;
    char word[16];
    struct node *next;
} list;
list words_hash[3500];

void seq_search(char word[], char list[][16], int n) {
    int i;
    for (i = 0; i < n; i++) {
        int result = strcmp(word, list[i]);
        if (result == 0) {
            printf("1 %d", i + 1);
            return;
        } else if (result < 0) {
            printf("0 %d", i + 1);
            return;
        }
    }
    printf("0 %d", i);
}

void bin_search(char word[], char list[][16], int n) {
    int lo = 0, hi = n - 1, mid, result, cnt = 0;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        result = strcmp(word, list[mid]);
        cnt++;
        if (result < 0)
            hi = mid - 1;
        else if (result > 0)
            lo = mid + 1;
        else {
            printf("1 %d", cnt);
            return;
        }
    }
    printf("0 %d", cnt);
}

void hash_search(char word[], list hash_list[]) {
    unsigned int word_hash = hash(word);
    if (hash_list[word_hash].next == NULL) {
        if (hash_list[word_hash].flag == 0) {
            printf("0 1");
        } else {
            printf("1 1");
        }
    } else {
        list *p;
        int cnt = 1;
        for (p = &hash_list[word_hash]; p->next != NULL; p = p->next, cnt++) {
            if (strcmp(p->word, word) == 0) {
                printf("1 %d", cnt);
                return;
            }
        }
        printf("0 %d", cnt);
    }
}

int main() {
    FILE *fp;
    fp = fopen("dictionary3000.txt", "r");
    char word[16];
    int type, i;
    scanf("%s%d", word, &type);
    switch (type) {
        case 1:
            for (i = 0; fscanf(fp, "%s", words[i]) != EOF; i++);
            seq_search(word, words, i);
            break;
        case 2:
            for (i = 0; fscanf(fp, "%s", words[i]) != EOF; i++);
            bin_search(word, words, i);
            break;
        case 3:
            i = 0;
            int index_len[26];
            char c, c_last = 'a';
            while ((c = fgetc(fp)) != EOF) {
                if (c == '\n' || c == '\r')
                    continue;
                ungetc(c, fp);
                if (c != c_last) {
                    index_len[c_last - 'a'] = i;
                    i = 0;
                    c_last = c;
                }
                fscanf(fp, "%s", words_index[c - 'a'][i]);
                i++;
            }
            index_len[c_last - 'a'] = i;
            c = word[0] - 'a';
            if (words_index[c][0][0] == '\0') {
                printf("0 0");
                return 0;
            }
            bin_search(word, words_index[c], index_len[c]);
            break;
        case 4:
            for (i = 0; fscanf(fp, "%s", words[i]) != EOF; i++) {
                unsigned int word_hash = hash(words[i]);
                if (words_hash[word_hash].flag == 0) {
                    words_hash[word_hash].flag = 1;
                } else {
                    list *p;
                    for (p = &words_hash[word_hash]; p->next != NULL; p = p->next);
                    p->next = (list *) malloc(sizeof(list));
                    strcpy(p->next->word, words[i]);
                    p->next->next = NULL;
                }
            }
            hash_search(word, words_hash);
            break;
    }
    fclose(fp);
    return 0;
}
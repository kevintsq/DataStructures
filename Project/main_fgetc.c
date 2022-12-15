#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
    char is_word, is_stopword, is_top_n_in_1, word[64];
    int cnt1, cnt2;
    struct node *next[26];
} node;
node *list1[10000000], *list2[10000000];

node *insert(node *root, char *word) {
    register node *p;
    register int index;
    for (p = root; *word != '\0'; word++) {  // p首先在根节点
        index = *word - 'a';  // 依次取出word中的字母
        if (p->next[index] == NULL) {  // 若该位置的字母没有子树
            p->next[index] = (node *) calloc(1, sizeof(node));  // 为其分配子树
            //p->is_leaf = 0;  // p所指的这层节点不再是叶子，因为刚刚分配了子树
        }
        p = p->next[index];  // 进入该位置的字母的子树
    }
    p->is_word = 1;  // 最终p所在的位置是个词
    return p;
}

node *search(node *root, char *word) {
    register node *p;
    register int index;
    for (p = root; *word != '\0'; word++) {
        index = *word - 'a';
        if (p->next[index] == NULL)
            return NULL;
        p = p->next[index];  // 进入该位置的字母的子树
    }
    if (p->is_word)
        return p;
    else
        return NULL;
}

int cmp1(const void *a, const void *b) {
    register int flag = (*((node **) b))->cnt1 - (*((node **) a))->cnt1;
    if (flag == 0)
        flag = strcmp((*((node **) a))->word, (*((node **) b))->word);
    return flag;
}

int cmp2(const void *a, const void *b) {
    register int flag = (*((node **) b))->cnt2 - (*((node **) a))->cnt2;
    if (flag == 0)
        flag = strcmp((*((node **) a))->word, (*((node **) b))->word);
    return flag;
}

int main() {
    register char c;
    char word[64];
    register node *dict = (node *) calloc(1, sizeof(node)), *p;
    register int i = 0, cnt = 0, union_sum1 = 0, union_sum2 = 0, sum1 = 0, sum2 = 0;
    int n;
    scanf("%d", &n);
    //clock_t t1 = clock();
    FILE *fp = fopen("dictionary.txt", "rb");
    while ((c = fgetc(fp)) != EOF) {
        if ('a' <= c && c <= 'z')
            word[i++] = c;
        else if (i != 0) {
            word[i] = '\0';
            p = insert(dict, word);
            memcpy(p->word, word, i + 1);
            list1[cnt] = p;
            list2[cnt++] = p;
            i = 0;
        }
    }
    word[i] = '\0';
    p = insert(dict, word);
    memcpy(p->word, word, i + 1);
    list1[cnt] = p;
    list2[cnt++] = p;
    i = 0;
    fp = fopen("stopwords.txt", "rb");
    while ((c = fgetc(fp)) != EOF) {
        if ('a' <= c && c <= 'z')
            word[i++] = c;
        else if (i != 0) {
            word[i] = '\0';
            if ((p = search(dict, word)) != NULL)
                p->is_stopword = 1;
            i = 0;
        }
    }
    word[i] = '\0';
    if ((p = search(dict, word)) != NULL)
        p->is_stopword = 1;
    i = 0;
    fp = fopen("article1.txt", "rb");
    while ((c = fgetc(fp)) != EOF) {
        if ('a' <= c && c <= 'z')
            word[i++] = c;
        else if ('A' <= c && c <= 'Z') {
            word[i++] = c + 32;
        } else if (i != 0) {
            word[i] = '\0';
            if ((p = search(dict, word)) != NULL && !p->is_stopword) {
                p->cnt1++;
            }
            i = 0;
        }
    }
    word[i] = '\0';
    if ((p = search(dict, word)) != NULL && !p->is_stopword) {
        p->cnt1++;
    }
    i = 0;
    fp = fopen("article2.txt", "rb");
    while ((c = fgetc(fp)) != EOF) {
        if ('a' <= c && c <= 'z')
            word[i++] = c;
        else if ('A' <= c && c <= 'Z') {
            word[i++] = c + 32;
        } else if (i != 0) {
            word[i] = '\0';
            if ((p = search(dict, word)) != NULL && !p->is_stopword) {
                p->cnt2++;
            }
            i = 0;
        }
    }
    word[i] = '\0';
    if ((p = search(dict, word)) != NULL && !p->is_stopword) {
        p->cnt2++;
    }
    fp = fopen("results.txt", "wb");
    qsort(list1, cnt, sizeof(node *), cmp1);
    qsort(list2, cnt, sizeof(node *), cmp2);
    register int tmp_cnt = list2[n]->cnt2;
    register char *tmp_word = list2[n]->word;
    for (i = 0; i < n; i++) {
        sum1 += list1[i]->cnt1;
        sum2 += list2[i]->cnt2;
        if (list1[i]->cnt2 > tmp_cnt || (list1[i]->cnt2 == tmp_cnt && strcmp(list1[i]->word, tmp_word) < 0)) {
            union_sum1 += list1[i]->cnt1;
            union_sum2 += list1[i]->cnt2;
        }
    }
    double pro1 = (double) union_sum1 / sum1, pro2 = (double) union_sum2 / sum2;
    double sim = (pro1 < pro2 ? pro1 : pro2) / (pro1 > pro2 ? pro1 : pro2);
    printf("%.5lf", sim);
    fprintf(fp, "%.5lf\n\n", sim);
    for (i = 0; i < n; i++) {
        fprintf(fp, "%s %d\n", list1[i]->word, list1[i]->cnt1);
    }
    fwrite("\n", 1, 1, fp);
    for (i = 0; i < n; i++) {
        fprintf(fp, "%s %d\n", list2[i]->word, list2[i]->cnt2);
    }
    //clock_t t2 = clock();
    //printf("\n%lf", (double)(t2 - t1) / CLOCKS_PER_SEC);
    return 0;
}
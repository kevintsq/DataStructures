// 没写出来

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    char name[21], parent[21];
    int type, date, child_cnt;
    struct node *next[101];
} tree;
tree files[101];

int cmp(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

tree *search(tree *root, char s[]) {
    if (root == NULL) {
        return NULL;
    } else if (strcmp(root->name, s) == 0) {
        return root;
    } else {
        tree *p;
        for (int i = 0; i < 101; i++) {
            if ((p = search(root->next[i], s)) != NULL)
                return p;
        }
    }
    return NULL;
}

int main() {
    FILE *fp = fopen("files.txt", "r");
    int n, i, j, k = 0;
    char str[21];
    tree *root, *p;
    scanf("%d%s", &n, str);
    fscanf(fp, "%s%s%d%d", files[0].name, files[0].parent, &files[0].type, &files[0].date);
    for (i = 1; i < n; i++) {
        fscanf(fp, "%s%s%d%d", files[i].name, files[i].parent, &files[i].type, &files[i].date);
        files[i].child_cnt = 0;
        for (j = 0; j < 101; j++) {
            files[i].next[j] = NULL;
        }
        if ((p = search(&files[0], files[i].parent)) != NULL) {
            p->next[p->child_cnt++] = &files[i];
        }
    }
    
    return 0;
}
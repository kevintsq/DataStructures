#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node *left;
    char word[32];
    int cnt;
    struct node *right;
} node;

node *insert(node *tree, char *word) {
    if (tree == NULL) {
        tree = (node *) malloc(sizeof(node));
        strcpy(tree->word, word);
        tree->cnt = 1;
        tree->left = tree->right = NULL;
    } else if (strcmp(tree->word, word) > 0)
        tree->left = insert(tree->left, word);
    else if (strcmp(tree->word, word) < 0)
        tree->right = insert(tree->right, word);
    else
        tree->cnt++;
    return tree;
}

void post_order(node *tree) {
    if (tree != NULL) {
        post_order(tree->left);
        printf("%s %d\n", tree->word, tree->cnt);
        post_order(tree->right);
    }
}

int main() {
    freopen("article.txt", "r", stdin);
    int i = 0;
    char tmp, s[32];
    node *words = NULL;
    while (1) {
        if (isalpha(tmp = getchar())) {
            if (isupper(tmp))
                s[i++] = tolower(tmp);
            else
                s[i++] = tmp;
        } else if (i == 0) {
            if (tmp == EOF)
                break;
        } else {
            s[i] = '\0';
            i = 0;
            words = insert(words, s);
        }
    }
    i = 1;
    for (node *p = words; p != NULL && i <= 3; p = p->right, i++) {
        printf("%s ", p->word);
    }
    printf("\n");
    post_order(words);
    fclose(stdin);
    return 0;
}
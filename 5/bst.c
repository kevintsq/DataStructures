#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *left;
    int data;
    struct node *right;
} node;

int height;

node *insert(node *tree, int item) {
    if (tree == NULL) {
        tree = (node *) malloc(sizeof(node));
        tree->data = item;
        tree->left = tree->right = NULL;
    } else if (item < tree->data)
        tree->left = insert(tree->left, item);
    else if (item >= tree->data)
        tree->right = insert(tree->right, item);
    return tree;
}

int is_leaf(node *tree) {
    return tree->left == NULL && tree->right == NULL;
}

void post_order(node *tree) {
    height++;
    if (tree != NULL) {
        post_order(tree->left);
        height--;
        post_order(tree->right);
        height--;
        if (is_leaf(tree)) {
            printf("%d %d\n", tree->data, height);
        }
    }
}

int main() {
    node *tree = NULL;
    int m, n;
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &n);
        tree = insert(tree, n);
    }
    post_order(tree);
    return 0;
}
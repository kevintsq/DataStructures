#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left, *middle, *right;
} node;

node *insert_sub_node(node *tree, int data) {
    if (data != 0) {
        tree = (node *) malloc(sizeof(node));
        tree->data = data;
        tree->left = tree->middle = tree->right = NULL;
    }
    return tree;
}

node *r_in_tree(node *tree, int r) {
    if (tree != NULL) {
        if (tree->data == r) {
            return tree;
        }
        node *t = r_in_tree(tree->left, r);
        if (t == NULL)
            t = r_in_tree(tree->middle, r);
        else
            return t;
        if (t == NULL)
            r_in_tree(tree->right, r);
    } else {
        return NULL;
    }
}

node *insert(node *tree, int r, int s1, int s2, int s3) {
    node *t = r_in_tree(tree, r);
    if (t == NULL) {
        tree = (node *) malloc(sizeof(node));
        tree->data = r;
        tree->left = insert_sub_node(tree->left, s1);
        tree->middle = insert_sub_node(tree->middle, s2);
        tree->right = insert_sub_node(tree->right, s3);
    } else {
        t->left = insert_sub_node(t->left, s1);
        t->middle = insert_sub_node(t->middle, s2);
        t->right = insert_sub_node(t->right, s3);
    }
    return tree;
}

int is_leaf(node *tree) {
    return tree->left == NULL && tree->middle == NULL && tree->right == NULL;
}

int child_cnt(node *tree) {
    int cnt = 0;
    if (tree->left != NULL)
        cnt++;
    if (tree->middle != NULL)
        cnt++;
    if (tree->right != NULL)
        cnt++;
    return cnt;
}

int height, order;
typedef struct {
    int val, cnt, pos, ord;
} record;
record info[10000];

void post_order(node *tree) {
    height++;
    if (tree != NULL) {
        info[tree->data].val = tree->data;
        info[tree->data].cnt = child_cnt(tree);
        info[tree->data].pos = height;
        info[tree->data].ord = ++order;
        post_order(tree->left);
        height--;
        post_order(tree->middle);
        height--;
        post_order(tree->right);
        height--;
    }
}

int cmp(const void *a, const void *b) {
    int flag = ((record *) b)->cnt - ((record *) a)->cnt;
    if (flag == 0)
        flag = ((record *) b)->pos - ((record *) a)->pos;
    if (flag == 0)
        flag = ((record *) a)->ord - ((record *) b)->ord;
    return flag;
}

int main() {
    int n, r, s1, s2, s3;
    node *tree = NULL;
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d%d%d", &r, &s1, &s2, &s3);
        tree = insert(tree, r, s1, s2, s3);
    }
    post_order(tree);
    qsort(info, 10000, sizeof(info[0]), cmp);
    printf("%d %d\n", info[0].val, info[0].ord);
    for (int i = 1; i < 10000; i++) {
        if (info[i].cnt == info[0].cnt && info[i].pos == info[0].pos)
            printf("%d %d\n", info[i].val, info[i].ord);
    }
    return 0;
}
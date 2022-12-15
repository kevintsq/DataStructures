//文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct node { //Huffman树结构节点类型
    char c;
    int weight; //树节点权重，叶节点为字符和它的出现次数
    struct node *left, *right;
};
int CharCnt[128] = {0};           //存放每个字符的出现次数，如CharCnt[i]表示ASCII值为i的字符出现次数
struct node *Root = NULL;         //Huffman树的根节点
char HCode[128][MAXSIZE] = {{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式）
int Step = 0;                     //实验步骤
FILE *Src, *Obj;

void cntChar();     //步骤1：统计文件中字符频率
void createHTree(); //步骤2：创建一个Huffman树，根节点为Root
void makeHCode();   //步骤3：根据Huffman树生成Huffman编码
void atoHzip();     //步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();               //输出步骤1的结果
void print2(struct node *p); //输出步骤2的结果
void print3();               //输出步骤3的结果
void print4();               //输出步骤4的结果

int main() {
    if ((Src = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "%s open failed!\n", "input.txt");
        return 1;
    }
    if ((Obj = fopen("output.txt", "w")) == NULL) {
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d", &Step); //输入当前实验步骤

    cntChar();                             //实验步骤1：统计文件中字符出现次数（频率）
    (Step == 1) ? print1() : 1;            //输出实验步骤1结果
    createHTree();                         //实验步骤2：依据字符频率生成相应的Huffman树
    (Step == 2) ? print2(Root) : 2;        //输出实验步骤2结果
    makeHCode(Root);                       //实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
    (Step == 3) ? print3() : 3;            //输出实验步骤3结果
    (Step >= 4) ? atoHzip(), print4() : 4; //实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果

    fclose(Src);
    fclose(Obj);

    return 0;
}

//【实验步骤1】开始

void cntChar() {
    CharCnt[0] = 1;
    int c;
    while ((c = getc(Src)) != EOF) {
        if (c != '\n')
            CharCnt[c]++;
    }
}

//【实验步骤1】结束

//【实验步骤2】开始

typedef struct node tree;
tree *F[128];

int cmp(const void *a, const void *b) {
    int flag = (*((tree **) a))->weight - (*((tree **) b))->weight;
    if (flag == 0)
        flag = (*((tree **) a))->c - (*((tree **) b))->c;
    return flag;
}

tree *createTree(tree *T0, tree *T1) {
    tree *t = (tree *) malloc(sizeof(tree));
    t->weight = T0->weight + T1->weight;
    t->left = T0;
    t->right = T1;
    t->c = '~';
    return t;
}

void createHTree() {
    tree *p;
    int i, cnt = 0;
    for (i = 0; i < 128; i++)
        if (CharCnt[i] > 0) {
            p = (tree *) malloc(sizeof(tree));
            p->c = (char) i;
            p->weight = CharCnt[i];
            p->left = p->right = NULL;
            F[cnt++] = p;
        }
    qsort(F, cnt, sizeof(tree *), cmp);
    while (cnt > 1) {
        tree *t = createTree(F[0], F[1]);
        for (i = 2; i <= cnt; i++) {
            if (i == cnt) {
                F[i - 2] = t;
            } else if (F[i]->weight <= t->weight) {
                F[i - 2] = F[i];
            } else if (F[i]->weight > t->weight) {
                F[i - 2] = t;
                while (i <= cnt) {
                    F[i - 1] = F[i];
                    i++;
                }
                break;
            }
        }
        F[--cnt] = NULL;
    }
    Root = F[0];
}

//【实验步骤2】结束

//【实验步骤3】开始
int is_leaf(tree *t) {
    return t->left == NULL && t->right == NULL;
}

char str[MAXSIZE];
int height = -1;

void visitHTree(tree *t) {
    height++;
    if (t != NULL) {
        if (is_leaf(t)) {
            strcpy(HCode[t->c], str);
            return;
        }
        str[height] = '0';
        visitHTree(t->left);
        str[--height] = '1';
        visitHTree(t->right);
        str[--height] = '\0';
    }
}

void makeHCode() {
    visitHTree(Root);
}

//【实验步骤3】结束

//【实验步骤4】开始

void atoHzip() {
    int c, i = 0;
    unsigned char hc, *s;
    fseek(Src, 0, SEEK_SET);
    do {
        c = getc(Src);
        if (c == EOF)
            c = 0;
        for (s = HCode[c]; *s != '\0'; i++, s++) {
            hc = (hc << 1) | (*s - '0');
            if ((i + 1) % 8 == 0) {
                fputc(hc, Obj);   //输出到目标（压缩）文件中
                printf("%x", hc); //按十六进制输出到屏幕上
            }
        }
    } while (c);
}

//【实验步骤4】结束

void print1() {
    int i;
    printf("NUL:1\n");
    for (i = 1; i < 128; i++)
        if (CharCnt[i] > 0)
            printf("%c:%d\n", i, CharCnt[i]);
}

void print2(struct node *p) {
    if (p != NULL) {
        if ((p->left == NULL) && (p->right == NULL))
            switch (p->c) {
                case 0:
                    printf("NUL ");
                    break;
                case ' ':
                    printf("SP ");
                    break;
                case '\t':
                    printf("TAB ");
                    break;
                case '\n':
                    printf("CR ");
                    break;
                default:
                    printf("%c ", p->c);
                    break;
            }
        print2(p->left);
        print2(p->right);
    }
}

void print3() {
    int i;
    for (i = 0; i < 128; i++) {
        if (HCode[i][0] != 0) {
            switch (i) {
                case 0:
                    printf("NUL:");
                    break;
                case ' ':
                    printf("SP:");
                    break;
                case '\t':
                    printf("TAB:");
                    break;
                case '\n':
                    printf("CR:");
                    break;
                default:
                    printf("%c:", i);
                    break;
            }
            printf("%s\n", HCode[i]);
        }
    }
}

void print4() {
    long int in_size, out_size;

    fseek(Src, 0, SEEK_END);
    fseek(Obj, 0, SEEK_END);
    in_size = ftell(Src);
    out_size = ftell(Obj);

    printf("\n原文件大小：%ldB\n", in_size);
    printf("压缩后文件大小：%ldB\n", out_size);
    printf("压缩率：%.2f%%\n", (float) (in_size - out_size) * 100 / in_size);
}

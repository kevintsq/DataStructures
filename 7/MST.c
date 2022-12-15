#include <stdio.h>
#include <stdlib.h>

#define MAX 1005

typedef struct {
    int id, weight;
} edge;
edge graph[MAX][MAX];
edge MSTEdges[MAX]; // 存放生成的最小生成树的边，如(i, edges[i])为最小生成树的一条边，共有n - 1条边
int weight_to_MST[MAX]; // 存放未进入生成树的顶点至已确定的生成树上顶点的边的权重，weight_to_MST[i] = 0表示其已确定为最小生成树的顶点
int n; // 顶点个数

void create(edge G[][MAX]) {
    int e, i, eid, v1, v2, weight;
    scanf("%d%d", &n, &e);
    for (i = 0; i < e; i++) {
        scanf("%d%d%d%d", &eid, &v1, &v2, &weight);
        G[v1][v2].id = G[v2][v1].id = eid;
        G[v1][v2].weight = G[v2][v1].weight = weight;
    }
}

void Prim(edge G[][MAX], int start, edge edges[]) {
    unsigned min_weight;
    int i, j, min_weight_index = 0;
    for (i = 0; i < n; i++) {
        weight_to_MST[i] = G[start][i].weight; // 存下所有与start顶点相连的边的权重
        edges[i].id = G[start][i].id; // 暂时先把每个顶点到start顶点的边都看成最小生成树
        edges[i].weight = G[start][i].weight;
    }
    weight_to_MST[start] = -1; // start顶点已在最小生成树中
    for (i = 1; i < n; i++) { // 对于其余每个顶点，
        min_weight = -1; // 初始化到最小生成树的权值为无穷大(unsigned -1)
        for (j = 0; j < n; j++) { // 在未进入最小生成树的顶点中，寻找到最小生成树权重最小的顶点
            if (weight_to_MST[j] != 0 && weight_to_MST[j] != -1 && weight_to_MST[j] < min_weight) {
                min_weight = weight_to_MST[j];
                min_weight_index = j;
            }
        }
        weight_to_MST[min_weight_index] = -1; // 找到一个到最小生成树权重最小的顶点，把它加入树中
        for (j = 0; j < n; j++) {
            if (G[min_weight_index][j].weight != 0 // 如果顶点j到刚才那个顶点存在边
                && (weight_to_MST[j] == 0 || G[min_weight_index][j].weight < weight_to_MST[j])) { // 并且到原来的最小生成树没有边或权重比到刚才那个顶点更小，
                weight_to_MST[j] = G[min_weight_index][j].weight; // 更新它到最新的最小生成树的权重，
                edges[j].id = G[min_weight_index][j].id; // 并更新对顶点j假定的最小生成树
                edges[j].weight = G[min_weight_index][j].weight;
            }
        }
    }
}

int cmp(const void *a, const void *b) {
    return (*(edge *) a).id - (*(edge *) b).id;
}

int main() {
    create(graph);
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d to %d: %d %d,\t", i, j, graph[i][j].weight, graph[i][j].id);
        }
        printf("\n");
    }*/
    Prim(graph, 0, MSTEdges);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += MSTEdges[i].weight;
    }
    printf("%d\n", sum);
    qsort(MSTEdges, n, sizeof(edge), cmp);
    for (int i = 0; i < n; i++) {
        if (MSTEdges[i].id)
            printf("%d ", MSTEdges[i].id);
    }
    return 0;
}
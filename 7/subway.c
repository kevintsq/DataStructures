#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 512

typedef struct {
    char name[32];
    int exchange;
} vertex;
vertex station[MAX];

typedef struct {
    int weight, line;
} edge;
edge map[MAX][MAX];

int line_cnt, station_cnt, precursor[MAX], weight_to_path[MAX], board[MAX];

int search(char s[]) {
    for (int i = 0; i < station_cnt; i++) {
        if (strcmp(station[i].name, s) == 0) {
            return i;
        }
    }
    return -1;
}

int add_vertex(vertex v) {
    for (int i = 0; i < station_cnt; i++) {
        if (strcmp(station[i].name, v.name) == 0) {
            station_cnt--;
            return i;
        } else if (station[i].name[0] == '\0') {
            strcpy(station[i].name, v.name);
            station[i].exchange = v.exchange;
            return i;
        }
    }
    exit(-1);
}

void create_map() {
    FILE *fp = fopen("bgstations.txt", "r");
    int i, j, line, line_station_cnt, v1, v2;
    vertex tmp;
    fscanf(fp, "%d", &line_cnt);
    for (i = 0; i < line_cnt; i++) {
        fscanf(fp, "%d%d", &line, &line_station_cnt);
        station_cnt += line_station_cnt;
        v1 = v2 = -1;
        for (j = 0; j < line_station_cnt; j++) {
            fscanf(fp, "%s%d", tmp.name, &tmp.exchange);
            v2 = add_vertex(tmp);
            if (v1 != -1) {
                map[v1][v2].weight = map[v2][v1].weight = 1;
                map[v1][v2].line = map[v2][v1].line = line;
            }
            v1 = v2;
        }
    }
    fclose(fp);
}

void Dijkstra(int v0, int v1) {
    // weight_to_path[i]为顶点v0到顶点i的最小权重
    // precursor[i]为顶点i的前驱顶点
    int i, j, min_weight_index = v0;
    unsigned min_weight;
    for (i = 0; i < station_cnt; i++) {
        weight_to_path[i] = map[v0][i].weight; // 存下所有与顶点v0相连的边的权重，0为不相连，1为相连
        precursor[i] = v0; // 暂时先把每个顶点到顶点v0的边都看成最短路径
    }
    weight_to_path[v0] = -1; // v0顶点已在最短路径中
    for (i = 1; i < station_cnt; i++) { // 对于其余每个顶点，
        min_weight = -1; // 初始化到最短路径的权值为无穷大(unsigned -1)
        for (j = 0; j < station_cnt; j++) // 在未进入最短路径的顶点中，寻找到最短路径权重最小的顶点
            if (weight_to_path[j] != 0 && weight_to_path[j] != -1 && weight_to_path[j] < min_weight) {
                min_weight = weight_to_path[j];
                min_weight_index = j;
            }
        weight_to_path[min_weight_index] = -1; // 找到一个到最短路径权重最小的顶点，把它加入最短路径中
        if (min_weight_index == v1)
            return;
        for (j = 0; j < station_cnt; j++) {
            if (map[min_weight_index][j].line > 0 // 如果顶点j到刚才那个顶点存在边
                && (weight_to_path[j] == 0 || (weight_to_path[j] != -1 && min_weight + map[min_weight_index][j].weight <
                                                                          weight_to_path[j]))) { // 并且到原来的最短路径没有边或权重比到刚才那个顶点更小，
                weight_to_path[j] = (int) min_weight + map[min_weight_index][j].weight; // 更新它到最新的最短路径的权重，
                precursor[j] = min_weight_index;  // 并更新对顶点j假定的最短路径
            }
        }
    }
}

void print_path(int v0, int v1) {
    int tot_cnt = 0, station_cnt_for_line, line, i;
    do {
        board[tot_cnt++] = v1;
    } while ((v1 = precursor[v1]) != v0);
    board[tot_cnt++] = v0;
    line = map[board[tot_cnt - 1]][board[tot_cnt - 2]].line;
    printf("%s-%d(", station[board[tot_cnt - 1]].name, line);
    station_cnt_for_line = 1;
    for (i = tot_cnt - 2; i > 0; i--, station_cnt_for_line++) {
        if (map[board[i]][board[i - 1]].line != line) {
            line = map[board[i]][board[i - 1]].line;
            printf("%d)-%s-%d(", station_cnt_for_line, station[board[i]].name, line);
            station_cnt_for_line = 0;
        }
    }
    printf("%d)-%s", station_cnt_for_line, station[board[i]].name);
}

int main() {
    create_map();
    //for (int i = 0; i < station_cnt; i++) {
    //    printf("%s %d\n", station[i].name, station[i].exchange);
    //}
    char s1[32], s2[32];
    scanf("%s%s", s1, s2);
    int tmp1 = search("西局"), tmp2 = search("北京南站");
    map[tmp1][tmp2] = (edge) {0, 0};
    map[tmp2][tmp1] = (edge) {0, 0};
    int v0 = search(s1), v1 = search(s2);
    Dijkstra(v0, v1);
    print_path(v0, v1);
    return 0;
}

#include <iostream>

using namespace std;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define V_SIZE 13
#define INF 10000
#define ARGC 3

typedef int Status;
typedef string VertexType;
typedef enum { DG, DN, AG, AN } GraphKind;
typedef struct {
  VertexType vexs[V_SIZE];
  int edge[V_SIZE][V_SIZE];
  int vexnum;
  int arcnum;
  GraphKind kind;
} Mgraph;

void array_fill(int *array, int len, int val) {
  int i;
  for (i = 0; i < len; i++) {
    array[i] = val;
  }
}

Status Dijkstra(int graph[][V_SIZE], int len, int start, int dist[]) {
  int *path = (int *)malloc(sizeof(int) * len);
  int *shortest = (int *)malloc(sizeof(int) * len);
  int *mark = (int *)malloc(sizeof(int) * len);
  int min, v, i, j;
  array_fill(mark, len, 0);
  array_fill(dist, len, INF);

  for (i = 0; i < len; i++) {
    dist[i] = graph[start][i];
    if (i != start && dist[i] < INF)
      path[i] = start;
    else
      path[i] = -1;
  }
  mark[start] = 1;
  while (1) {
    min = INF;
    v = -1;
    //找到最小的距离
    for (i = 0; i < len; i++) {
      if (!mark[i]) {
        if (dist[i] < min) {
          min = dist[i];
          v = i;
        }
      }
    }
    if (v == -1)
      break; //找不到更短的路径了
    //更新最短路径
    mark[v] = 1;
    for (i = 0; i < len; i++) {
      if (!mark[i] && graph[v][i] != INF && dist[v] + graph[v][i] < dist[i]) {
        dist[i] = dist[v] + graph[v][i];
        path[i] = v;
      }
    }
  }
  //输出路径
  printf("起点\t终点\t最短距离\t对应路径 \n");
  for (i = 0; i < len; i++) {
    if (i == start)
      continue;
    array_fill(shortest, len, 0);
    printf("%d\t", start);
    printf("%d\t", i);
    printf("%d\t", dist[i]);
    int k = 0;
    shortest[k] = i;
    while (path[shortest[k]] != start) {
      k++;
      shortest[k] = path[shortest[k - 1]];
    }
    k++;
    shortest[k] = start;
    for (j = k; j > 0; j--) {
      printf("%d->", shortest[j]);
    }
    printf("%d\n", shortest[0]);
  }
  free(path);
  free(shortest);
  free(mark);
  return OK;
}

int main(int argc, char **argv) {
  // if (argc != ARGC) {
  //   printf("ERROR_01");
  //   return ERROR;
  // } //命令行参数检查

  Mgraph XJTUMap = {
      {"北门", "饮水思源", "腾飞塔", "图书馆", "教学主楼", "活动中心", "南门",
       "宪梓堂", "西迁馆", "传送门1", "传送门2", "传送门3",
       "传送门4"}, //顶点数组
      {
          {0, 18, INF, INF, INF, INF, INF, INF, INF, INF, INF, 22, INF},
          {18, 0, 19, INF, INF, INF, INF, INF, INF, 27, INF, INF, INF},
          {INF, 19, 0, 23, INF, INF, INF, INF, INF, INF, INF, 4, 32},
          {INF, INF, 23, 0, 15, INF, INF, INF, INF, 4, 4, INF, INF},
          {INF, INF, INF, 15, 0, 21, INF, 8, INF, INF, INF, INF, INF},
          {INF, INF, INF, INF, 21, 0, 30, INF, INF, INF, INF, INF, INF},
          {INF, INF, INF, INF, INF, 30, 0, 14, 20, INF, 21, INF, INF},
          {INF, INF, INF, INF, 8, INF, 14, 0, INF, INF, INF, INF, 4},
          {INF, INF, INF, INF, INF, INF, 20, INF, 0, INF, 43, INF, INF},
          {INF, 27, INF, 4, INF, INF, INF, INF, INF, 0, INF, INF, INF},
          {INF, INF, INF, 4, INF, INF, 21, INF, 43, INF, 0, INF, INF},
          {22, INF, 4, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF},
          {INF, INF, 32, INF, INF, INF, INF, 4, INF, INF, INF, INF, 0},
      },  //弧权值数组
      V_SIZE, //顶点数
      18, //弧段数
      AG, //无向图
  };

  int dist[V_SIZE];
  Dijkstra(XJTUMap.edge, V_SIZE, 0, dist);

  return 0;
}

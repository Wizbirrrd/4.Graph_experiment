#include <iostream>
#include <string.h>

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

//根据字符串寻找邻接矩阵的下标
Status TrackPosition(string *s, string t, int &p) {
  int i = 0;
  for (i = 0; s[i] != t; i++) {
    if (i == V_SIZE) {
      return ERROR;
    };
  }
  p = i;
  return OK;
}

// Dijkstra算法实现
Status Dijkstra(Mgraph G, string From, string To) {
  int from, to;
  if (!TrackPosition(G.vexs, From, from) || !TrackPosition(G.vexs, To, to)) {
    printf("ERROR_02");
    return ERROR;
  } //合法性输入检查

  int i;
  int *shortest = (int *)malloc(sizeof(int) * V_SIZE);
  if (!shortest)
    return (OVERFLOW);
  Status *IsMin = (Status *)malloc(sizeof(Status) * V_SIZE);
  if (!IsMin)
    return (OVERFLOW);
  char **Path = (char **)malloc(sizeof(char) * V_SIZE);
  if (!Path)
    return (OVERFLOW);
  for (i = 0; i < V_SIZE; i++) {
    shortest[i] = G.edge[from][i];
    IsMin[i] = FALSE;
    strcpy(Path[i],"i");
    if (shortest[i] == 0) {
      IsMin[i] = TRUE;
      strcpy(Path[i],"\0");
    }
  } //初始化距离数组用于迭代

  int Min, MinPos;
  Status Over = TRUE;
  while (Over) {
    Min = INF;
    Over = FALSE;
    for (i = 0; i < V_SIZE; i++) {
      if (Min > shortest[i] && !IsMin[i]) {
        Min = shortest[i];
        MinPos = i;
        IsMin[i] = TRUE;
        Over = TRUE;
      } //寻找距离最近的结点并标记
    }
    for (i = 0; i < V_SIZE; i++) {
      if (shortest[i] > G.edge[MinPos][i] + Min) {
        shortest[i] = G.edge[MinPos][i] + Min;
      }
    } //更新距离数组
  }   //迭代结束的条件:对所有结点都找到了最短路径
  printf("%d", shortest[to]);
  free(shortest);
  free(IsMin); //释放内存
  return OK;
}

int main(int argc, char **argv) {
  if (argc != ARGC) {
    printf("ERROR_01");
    return ERROR;
  } //命令行参数检查

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
      },      //弧权值数组
      V_SIZE, //顶点数
      18,     //弧段数
      AG,     //无向图
  };

  Dijkstra(XJTUMap, argv[1], argv[2]);

  return 0;
}

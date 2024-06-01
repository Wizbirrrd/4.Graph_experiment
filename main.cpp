#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define ARGC 3

typedef int Status;

int main(int argc, char **argv) {
  if (argc != ARGC) {
    printf("ERROR_01");
    return ERROR;
  } //命令行参数检查
  printf("Hello, from Dijkstra!\n");
}

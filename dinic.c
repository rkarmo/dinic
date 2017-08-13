/* Dinic algorithm for the Max-Flow problem,
implemented for simple oriented graphs */

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>

#define uv 0
#define vu 1

//We assume that every edge also has its opposite edge. If not,
//we add it with capacity 0.

typedef struct edge {
  int u, v; //endpoints
  int c[2]; //capacities of uv and vu
  int f[2]; //flows on uv and vu
} edge_t;

int n, m; //# of vertices/edges
int s, t; //source and sink

int main(void)
{
  return 0;
}

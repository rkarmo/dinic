/* Dinic algorithm for the Max-Flow problem,
implemented for simple oriented graphs */

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h> //for memset

#define uv 0
#define vu 1
#define DEBUG 1

//We assume that every edge also has its opposite edge. If not,
//we add it with capacity 0.

typedef struct edge {
  int u, v; //endpoints
  int c[2]; //capacities of uv and vu
  int f[2]; //flows on uv and vu
} edge_t;


void sort_edges(edge_t* G, int n, int m)
{
  int *offset = calloc(n + 1,  sizeof(int));
  edge_t *by2nd = malloc(m * sizeof(edge_t));
  for (int i = 0; i < m; i++) {
    offset[G[i].v]++;
  }
  for (int i = 1; i <= n; i++) {
    offset[i] += offset[i - 1];
  }
  for (int i = 0; i < m; i++) {
    by2nd[--offset[G[i].v]] = G[i];
  }
  memset(offset, 0, (n + 1) * sizeof(int));
  for (int i = 0; i < m; i++) {
    offset[G[i].u]++;
  }
  for (int i = 1; i <= n; i++) {
    offset[i] += offset[i - 1];
  }
    for (int i = m - 1; i >= 0; i--) {
    G[--offset[by2nd[i].u]] = by2nd[i];
  }
  free(offset);
  free(by2nd); 
}

// merges all edges between a pair of vertices into one. 
// assumes that all edges satisfy edge.u < edge.v
// retval: updated number of edges after merge

int merge_edges(edge_t *G, int n, int m)
{
  sort_edges(G, n, m);
  if (DEBUG) {
    printf("before merge\n");
    for (int i = 0; i < m; i++) {
      printf("%d %d %d %d\n", G[i].u, G[i].v, G[i].c[uv], G[i].c[vu]);
    }
  }
  int _m = 0;
  for (int i = 1; i < m; i++) {
    if (G[i].u == G[_m].u && G[i].v == G[_m].v) {
      G[_m].c[uv] += G[i].c[uv];
      G[_m].c[vu] += G[i].c[vu];
    }
    else {
      G[++_m] = G[i];
    }
  }
  m = (m == 0) ? m : _m + 1;
  if (DEBUG) {
    printf("after merge\n");
    for (int i = 0; i < m; i++) {
      printf("%d %d %d %d\n", G[i].u, G[i].v, G[i].c[uv], G[i].c[vu]);
    }
  }
  return m;
}

int n, m; //# of vertices/edges
int s, t; //source and sink

int main(void)
{
  scanf("%d%d%d%d", &n, &m, &s, &t);
  edge_t *G = malloc(m * sizeof(edge_t));
  for (int i = 0; i < m; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    G[i].f[uv] = G[i].f[vu] = 0;
    if (u < v) {
      G[i].u = u;
      G[i].v = v;
      G[i].c[uv] = c;
      G[i].c[vu] = 0;
    }
    else {
      G[i].u = v;
      G[i].v = u;
      G[i].c[uv] = 0;
      G[i].c[vu] = c;
    }
  }

  m = merge_edges(G, n, m);
  
  free(G);
  return 0;
}

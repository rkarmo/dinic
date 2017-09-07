/* Dinic algorithm for the Max-Flow problem,
implemented for simple oriented graphs */

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h> //for memset

#define uv 0
#define vu 1

#define MAXN 10000
#define MAXM 1000000

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
  int *bucket = calloc(n + 1,  sizeof(int));
  edge_t *by2nd = malloc(m * sizeof(edge_t));
  for (int i = 0; i < m; i++) {
    bucket[G[i].v]++;
  }
  for (int i = 1; i <= n; i++) {
    bucket[i] += bucket[i - 1];
  }
  for (int i = 0; i < m; i++) {
    by2nd[--bucket[G[i].v]] = G[i];
  }
  memset(bucket, 0, (n + 1) * sizeof(int));
  for (int i = 0; i < m; i++) {
    bucket[G[i].u]++;
  }
  for (int i = 1; i <= n; i++) {
    bucket[i] += bucket[i - 1];
  }
  for (int i = m - 1; i >= 0; i--) {
    G[--bucket[by2nd[i].u]] = by2nd[i];
  }
  free(bucket);
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
int l; //distance of source and sink

int V[MAXN + 1];
int E[2 * MAXM];
int lvl[MAXN];
int c[MAXM];
int f[MAXM];
int outdeg[MAXN];

//vertex queue for various purposes
int Q[MAXN];
int Qsize;

//vertex stack for various purposes
int S[MAXN];
int Stop;

static void create_reserve_network(edge_t *G)
{
  memset(V, 0, (n + 1) * sizeof(int));

  for (int i = 0; i < m; i++) {
    if (G[i].c[uv] - G[i].f[uv] + G[i].f[vu] > 0) {
      V[G[i].u]++;
    }
    if (G[i].c[vu] - G[i].f[vu] + G[i].f[uv] > 0) {
      V[G[i].v]++;
    }
  }
  for (int i = 1; i <= n; i++) {
    V[i] += V[i-1];
  }
  for (int i = 0; i < m; i++) {
    if (G[i].c[uv] - G[i].f[uv] + G[i].f[vu] > 0) {
      E[--V[G[i].u]] = G[i].v;
    }
    if (G[i].c[vu] - G[i].f[vu] + G[i].f[uv] > 0) {
      E[--V[G[i].v]] = G[i].u;
    }
  }
}

static void calculate_levels()
{
  Qsize = 0;
  for (int i = 0; i < n; i++) {
    lvl[i] = -1;
  }

  Q[Qsize++] = s;
  lvl[s] = 0;
  for (int q = 0; q < Qsize; q++) {
    int u = Q[q];
    for (int i = V[u]; i < V[u + 1]; i++) {
      int v = E[i];
      if (lvl[v] == -1) {
        lvl[v] = lvl[u] + 1;
        Q[Qsize++] = v;
      }
    }
  }
  l = lvl[t];
}

static void clean_reserve_network(edge_t *G)
{
  memset(V, 0, (n + 1) * sizeof(int));

  for (int i = 0; i < m; i++) {
    if ( (G[i].u == t || lvl[G[i].u]) ) {
    }
  }
}

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

  for (int phase = 0; phase < n; phase++) {
    create_reserve_network(G);
  }

  free(G);
  return 0;
}

#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph_t {
    int32_t n;
    int32_t m;
    int32_t M;
    int32_t *deg;
    int32_t *adj;
} graph_t;

void graph_construct(graph_t *G, int32_t n, int32_t M)
{
    G->n = n;
    G->m = 0;
    G->M = M;
    G->deg = (int32_t *)calloc(G->n, sizeof(int32_t));
    G->adj = (int32_t *)malloc(G->n * G->M * sizeof(int32_t));
    assert(G->deg != NULL);
    assert(G->adj != NULL);
}

void graph_destruct(graph_t *G)
{
    free(G->deg);
    free(G->adj);
}

int32_t *graph_adj(graph_t *G, int32_t v)
{
    assert(0 <= v && v < G->n);
    return G->adj + v * G->M;
}

// add u -> v
void graph_add_edge(graph_t *G, int32_t u, int32_t v)
{
    assert(0 <= u && u < G->n);
    assert(0 <= v && v < G->n);
    assert(G->deg[u] < G->M);
    (graph_adj(G, u))[G->deg[u]] = v;
    G->deg[u]++;
    G->m++;
}

#endif /* GRAPH_H */

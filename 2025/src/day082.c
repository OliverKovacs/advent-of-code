#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <priorityqueue.h>
#include <disjointset.h>

#define BUFFER_LEN 1024

bool fgetint(int64_t *n, FILE *stream)
{
    int c = fgetc(stream);
    if (c < '0' || '9' < c)
        return false;

    *n = 0;
    do {
        *n = 10 * *n + c - '0';
        c = fgetc(stream);
    } while('0' <= c && c <= '9');

    return true;
}

typedef struct edge_t {
    int32_t v;
    int32_t u;
    double w;
} edge_t;

double norm(int32_t v, int32_t u, int64_t *x, int64_t *y, int64_t *z)
{
    int64_t dx = x[v] - x[u];
    int64_t dy = y[v] - y[u];
    int64_t dz = z[v] - z[u];
    return sqrt(dx * dx + dy * dy + dz * dz);
}

bool compare_edge(void *lhs, void *rhs)
{
    return ((edge_t *)lhs)->w < ((edge_t *)rhs)->w;
}

int main()
{
    int64_t x[BUFFER_LEN];
    int64_t y[BUFFER_LEN];
    int64_t z[BUFFER_LEN];
    int64_t e;
    int32_t n = 0;

    while (fgetint(&e, stdin)) {
        assert(n < BUFFER_LEN);
        x[n] = e;
        assert(fgetint(&e, stdin));
        y[n] = e;
        assert(fgetint(&e, stdin));
        z[n] = e;
        n++;
    }

    pq_t pq;
    pq_construct(&pq, BUFFER_LEN * BUFFER_LEN, sizeof(edge_t), compare_edge);

    for (int32_t i = 0; i < n; i++)
        for (int32_t j = i + 1; j < n; j++) {
            edge_t e = {i, j, norm(i, j, x, y, z)};
            pq_push(&pq, &e);
        }

    djs_t djs;
    djs_construct(&djs, n);

    edge_t edge = {0, 0, 0};
    while (djs.count > 1) {
        pq_pop(&pq, &edge);
        djs_union(&djs, edge.u, edge.v);
    }

    printf("%ld\n", x[edge.u] * x[edge.v]);
    // 2185817796
}

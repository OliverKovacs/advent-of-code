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

bool compare_int(void *lhs, void *rhs)
{
    return *(int32_t *)lhs > *(int32_t *)rhs;
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

    const int32_t N = (n < 50) ? 10 : 1000;

    for (int32_t i = 0; i < N; i++) {
        edge_t e = {0, 0, 0};
        pq_pop(&pq, &e);
        djs_union(&djs, e.u, e.v);
    }

    int32_t *counts = (int32_t *)calloc(djs.size, sizeof(int32_t));

    for (int32_t i = 0; i < djs.size; i++)
        counts[djs_find(&djs, i)]++;

    pq_t sort;
    pq_construct(&sort, djs.size, sizeof(int32_t), compare_int);

    for (int32_t i = 0; i < djs.size; i++)
        pq_push(&sort, counts + i);

    for (int32_t i = 0; i < djs.size; i++)
        pq_pop(&sort, counts + i);

    int64_t prod = 1;
    for (int32_t i = 0; i < 3; i++)
        prod *= counts[i];

    printf("%ld\n", prod);
    // 24360
}

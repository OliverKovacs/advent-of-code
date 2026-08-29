#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <stdint.h>

static void swap(int32_t *x, int32_t *y)
{
    int32_t tmp = *x;
    *x = *y;
    *y = tmp;
}

typedef struct djs_t {
    int32_t size;
    int32_t count;
    int32_t *next;
    int32_t *rank;
} djs_t;

void djs_construct(djs_t *djs, int32_t size)
{
    djs->size = size;
    djs->count = size;
    djs->next = (int32_t *)malloc(size * sizeof(int32_t));
    djs->rank = (int32_t *)calloc(size, sizeof(int32_t));
    assert(djs->next != NULL);
    assert(djs->rank != NULL);
    for (int32_t i = 0; i < size; i++)
        djs->next[i] = i;
}

void djs_destruct(djs_t *djs)
{
    free(djs->next);
    free(djs->rank);
}

int32_t djs_find(djs_t *djs, int32_t id)
{
    if (djs->next[id] == id)
        return id;

    djs->next[id] = djs_find(djs, djs->next[id]);
    return djs->next[id];
}

void djs_union(djs_t *djs, int32_t id1, int32_t id2)
{
    id1 = djs_find(djs, id1);
    id2 = djs_find(djs, id2);

    if (id1 == id2)
        return;

    if (djs->rank[id1] < djs->rank[id2])
        swap(&id1, &id2);

    djs->next[id2] = id1;
    djs->count--;

    if (djs->rank[id1] == djs->rank[id2])
        djs->rank[id1]++;
}

#endif /* DISJOINTSET_H */

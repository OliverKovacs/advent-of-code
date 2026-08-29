#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <binarytree.h>

typedef struct pq_t {
    int32_t capacity;
    int32_t size;
    int32_t node;
    char *buffer;
    bool (*compare)(void *lhs, void *rhs);
} pq_t;

void pq_construct(
    pq_t *pq,
    int32_t capacity,
    int32_t node,
    bool (*compare)(void *lhs, void *rhs)
) {
    pq->capacity = capacity;
    pq->size = 0;
    pq->node = node;
    pq->buffer = (char *)malloc(capacity * node + node);
    assert(pq->buffer != NULL);
    pq->compare = compare;
}

void pq_destruct(pq_t *pq)
{
    free(pq->buffer);
}

static void pq_copy__(pq_t *pq, int32_t id_dest, int32_t id_src)
{
    memcpy(
        pq->buffer + id_dest * pq->node,
        pq->buffer + id_src * pq->node,
        pq->node
    );
}

static void pq_swap__(pq_t *pq, int32_t id1, int32_t id2)
{
    int32_t id_tmp = pq->capacity;
    pq_copy__(pq, id_tmp, id1);
    pq_copy__(pq, id1, id2);
    pq_copy__(pq, id2, id_tmp);
}

static int32_t pq_cmp__(pq_t *pq, int32_t id_rhs, int32_t id_lhs)
{
    return pq->compare(
        (void *)(pq->buffer + id_lhs * pq->node),
        (void *)(pq->buffer + id_rhs * pq->node)
    );
}

static void pq_down__(pq_t *pq, int32_t id)
{
    int32_t l = bt_left(id);
    int32_t r = bt_right(id);
    int32_t next = -1;

    if (l < pq->size && pq_cmp__(pq, id, l))
        next = l;
    if (r < pq->size && pq_cmp__(pq, l, r))
        next = r;

    if (next >= 0) {
        pq_swap__(pq, id, next);
        pq_down__(pq, next);
    }
}

static void pq_up__(pq_t *pq, int32_t id)
{
    if (id == 0)
        return;

    int32_t par = bt_parent(id);
    if (pq_cmp__(pq, id, par))
        return;

    pq_swap__(pq, id, par);
    pq_up__(pq, par);
}

void pq_peek(pq_t *pq, void *res)
{
    assert(pq->size > 0);
    memcpy(res, pq->buffer, pq->node);
}

void pq_pop(pq_t *pq, void *res)
{
    pq_peek(pq, res);
    pq_copy__(pq, 0, pq->size - 1);
    pq->size--;
    pq_down__(pq, 0);
}

void pq_push(pq_t * pq, void *value)
{
    assert(pq->size < pq->capacity);
    memcpy(pq->buffer + pq->size * pq->node, value, pq->node);
    pq->size++;
    pq_up__(pq, pq->size - 1);
}

#endif /* PRIORITYQUEUE_H */

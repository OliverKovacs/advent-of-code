#ifndef AVLTREE_H
#define AVLTREE_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define idx_t int32_t
#define IDX_NULL -1

typedef enum dir_t {
    DIR_L = 0,
    DIR_R = 1,
    DIR_INV = 2,
} dir_t;

typedef enum bf_t {
    BF_E = 1,       // even
    BF_L = 2,       // left heavy
    BF_R = 4,       // right heavy
    BF_X = 8,       // invalid
} bf_t;

#define BF_V BF_E | BF_L | BF_R     // valid
#define BF_U BF_L | BF_R            // unbalanced

typedef struct avl_t {
    int32_t capacity;
    int32_t size;
    int32_t key_size;
    int32_t val_size;
    idx_t head;
    idx_t free;
    idx_t *P;       // parent
    idx_t *L;       // left
    idx_t *R;       // right
    bf_t *BF;       // balance factor
    char *keys;
    char *vals;
    bool (*compare)(void *lhs, void *rhs);
} avl_t;

void avl_construct(
    avl_t *avl,
    int32_t capacity,
    int32_t key_size,
    int32_t val_size,
    bool (*compare)(void *lhs, void *rhs)
) {
    avl->capacity = capacity;
    avl->size = 0;
    avl->key_size = key_size;
    avl->val_size = val_size;
    avl->head = IDX_NULL;
    avl->free = 0;
    avl->compare = compare;

    avl->P = (idx_t *)malloc(avl->capacity * sizeof(idx_t));
    avl->L = (idx_t *)malloc(avl->capacity * sizeof(idx_t));
    avl->R = (idx_t *)malloc(avl->capacity * sizeof(idx_t));
    avl->BF = (bf_t *)malloc(avl->capacity * sizeof(bf_t));
    avl->keys = (char *)malloc(avl->capacity * avl->key_size);
    avl->vals = (char *)malloc(avl->capacity * avl->val_size);
    assert(avl->P != NULL);
    assert(avl->L != NULL);
    assert(avl->R != NULL);
    assert(avl->BF != NULL);
    assert(avl->keys != NULL);
    assert(avl->vals != NULL);

    for (int32_t i = 0; i < avl->capacity - 1; i++)
        avl->P[i] = i + 1;
    avl->P[avl->size - 1] = IDX_NULL;
}

void avl_destruct(avl_t *avl)
{
    free(avl->P);
    free(avl->L);
    free(avl->R);
    free(avl->BF);
    free(avl->keys);
    free(avl->vals);
}

static bool avl_equal__(avl_t *avl, void *rhs, void *lhs)
{
    return !avl->compare(lhs, rhs) && !avl->compare(lhs, rhs);
}

static char *avl_lookup__(char *buf, idx_t idx, int32_t size)
{
    assert(idx != IDX_NULL);
    return buf + idx * size;
}

static void *avl_key__(avl_t *avl, idx_t idx)
{
    return avl_lookup__(avl->keys, idx, avl->key_size);
}

static void *avl_val__(avl_t *avl, idx_t idx)
{
    return avl_lookup__(avl->vals, idx, avl->val_size);
}

static idx_t avl_find__(avl_t *avl, idx_t idx, void *key)
{
    if (idx == IDX_NULL)
        return idx;

    if (avl->compare(key, avl_key__(avl, idx)))
        return avl_find__(avl, avl->L[idx], key);

    if (avl->compare(avl_key__(avl, idx), key))
        return avl_find__(avl, avl->R[idx], key);

    return idx;
}

static idx_t avl_alloc__(avl_t *avl)
{
    assert(avl->free != IDX_NULL);
    idx_t idx = avl->free;
    avl->free = avl->P[idx];
    avl->P[idx] = IDX_NULL;
    avl->L[idx] = IDX_NULL;
    avl->R[idx] = IDX_NULL;
    avl->BF[idx] = BF_E;
    return idx;
}

// Ax(ByC) -> (AxB)yC
static idx_t avl_rot_left__(avl_t *avl, idx_t x)
{
    assert(x != IDX_NULL);
    assert(avl->BF[x] == BF_R);
    idx_t parent = avl->P[x];

    idx_t y = avl->R[x];
    assert(y != IDX_NULL);
    // assert(avl->BF[y] & (BF_E | BF_R));
    assert(avl->BF[y] & BF_V);

    idx_t A = avl->L[x];
    idx_t B = avl->L[y];
    idx_t C = avl->R[y];

    assert(avl->P[y] == x);
    assert(A == IDX_NULL || avl->P[A] == x);
    assert(B == IDX_NULL || avl->P[B] == y);
    assert(C == IDX_NULL || avl->P[C] == y);

    avl->P[y] = parent;

    avl->L[y] = x;
    avl->P[x] = y;

    avl->R[x] = B;
    if (B != IDX_NULL)
        avl->P[B] = x;

    avl->BF[x] = (avl->BF[y] == BF_E) ? BF_R : BF_E;
    avl->BF[y] = BF_E;

    return y;
}

// (AyB)xC -> Ay(BxC)
static idx_t avl_rot_right__(avl_t *avl, idx_t x)
{
    assert(x != IDX_NULL);
    assert(avl->BF[x] == BF_L);
    idx_t parent = avl->P[x];

    idx_t y = avl->L[x];
    assert(y != IDX_NULL);
    // assert(avl->BF[y] & (BF_E | BF_L));
    assert(avl->BF[y] & BF_V);

    idx_t A = avl->R[x];
    idx_t B = avl->R[y];
    idx_t C = avl->L[y];

    assert(avl->P[y] == x);
    assert(A == IDX_NULL || avl->P[A] == x);
    assert(B == IDX_NULL || avl->P[B] == y);
    assert(C == IDX_NULL || avl->P[C] == y);

    avl->P[y] = parent;

    avl->R[y] = x;
    avl->P[x] = y;

    avl->L[x] = B;
    if (B != IDX_NULL)
        avl->P[B] = x;

    avl->BF[x] = (avl->BF[y] == BF_E) ? BF_L : BF_E;
    avl->BF[y] = BF_E;

    return y;
}

static idx_t avl_insert__(avl_t *avl, idx_t idx, idx_t par, void *key, void *val)
{
    if (idx == IDX_NULL) {
        idx = avl_alloc__(avl);
        avl->P[idx] = par;
        memcpy(avl_key__(avl, idx), key, avl->key_size);
        memcpy(avl_val__(avl, idx), val, avl->val_size);
        return idx;
    }

    dir_t dir = DIR_INV;
    if (avl->compare(key, avl_key__(avl, idx)))
        dir = DIR_L;

    if (avl->compare(avl_key__(avl, idx), key))
        dir = DIR_R;

    assert(dir != DIR_INV);     // key alread present!

    idx_t *child[2] = {avl->L, avl->R};
    idx_t (*rot[2])(avl_t *, idx_t) = {avl_rot_left__, avl_rot_right__};
    bf_t BF[2] = {BF_L, BF_R};

    idx_t *next = child[dir] + idx;
    bf_t bf_old = *next == IDX_NULL ? BF_X : avl->BF[*next];
    *next = avl_insert__(avl, *next, idx, key, val);
    bf_t bf_new = *next == IDX_NULL ? BF_X : avl->BF[*next];

    assert(avl->BF[idx] & BF_V);
    assert(bf_new & BF_V);
    switch (bf_old) {
        case BF_X:
            assert(bf_new == BF_E);
            // assert(avl->BF[idx] & (BF_E | BF[!dir]));
            avl->BF[idx] = (avl->BF[idx] == BF_E) ? BF[dir] : BF_E;
            return idx;
        case BF_E:
            if (bf_new == BF_E)
                return idx;

            // subtree grew
            assert(bf_new & BF_U);
            if (avl->BF[idx] == BF[dir]) {
                if (bf_new == BF[dir])
                    return rot[!dir](avl, idx);
                child[dir][idx] = rot[dir](avl, child[dir][idx]);
                return rot[!dir](avl, idx);
            }

            // no rotations needed
            assert(avl->BF[idx] & (BF_E | BF[!dir]));
            avl->BF[idx] = (avl->BF[idx] == BF_E) ? BF[dir] : BF_E;
            return idx;
        case BF_L:
            assert(bf_new & (BF_L | BF_E));
            return idx;
        case BF_R:
            assert(bf_new & (BF_R | BF_E));
            return idx;
        default:
            assert(false);
    }
}

bool avl_get(avl_t *avl, void *key, void *val)
{
    idx_t idx = avl_find__(avl, avl->head, key);
    if (idx == IDX_NULL)
        return false;

    memcpy(val, avl_val__(avl, idx), avl->val_size);
    return true;
}

void avl_insert(avl_t *avl, void *key, void *val)
{
    avl->head = avl_insert__(avl, avl->head, IDX_NULL, key, val);
    avl->size++;
}

bool avl_delete(avl_t *avl, void *key, void *val)
{
    (void)avl;
    (void)key;
    (void)val;
    assert(false); // not implemented!
}

static void avl_print_impl__(
    avl_t *avl,
    idx_t idx,
    void (*print_key)(void *),
    void (*print_val)(void *)
) {
    if (idx != IDX_NULL) {
        avl_print_impl__(avl, avl->L[idx], print_key, print_val);
        print_key(avl_key__(avl, idx));
        printf(": ");
        print_val(avl_val__(avl, idx));
        printf(", ");
        avl_print_impl__(avl, avl->R[idx], print_key, print_val);
    }
}

void avl_print(
    avl_t *avl,
    void (*print_key)(void *),
    void (*print_val)(void *)
) {
    printf("{");
    avl_print_impl__(avl, avl->head, print_key, print_val);
    printf("}");
}

#endif /* AVLTREE_H */

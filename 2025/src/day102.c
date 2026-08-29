#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <avltree.h>
#include <matrix.h>

#define MIN(a,b) (((a)>(b))?(b):(a))

#define BUFFER_LEN 512
#define DIM 10
#define DP_MAX (2 << 15) - 1
#define axis_t int16_t

bool fgetuint(uint64_t *n, FILE *stream)
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

bool read_diagram(uint64_t *x, FILE *stream)
{
    int c = fgetc(stream);
    if (c != '[')
        return false;

    *x = 0;
    int32_t i = 0;
    for (c = fgetc(stream); c != ']'; c = fgetc(stream)) {
        assert(c == '.' || c == '#');
        assert(i < 64);
        assert(i < DIM);
        *x |= ((c == '#') << i);
        i++;
    }
    return true;
}

bool read_schematics(uint64_t *x, FILE *stream)
{
    int c = fgetc(stream);
    if (c != '(')
        return false;

    *x = 0;
    uint64_t n;
    while(fgetuint(&n, stdin)) {
        assert(n < 64);
        *x = *x | (1 << n);
    }
    return true;
}

uint64_t nxor(uint64_t *S, int32_t n, uint64_t mask)
{
    uint64_t res = 0;
    for (int32_t i = 0; i < n; i++)
        res ^= S[i] * !!(mask & ((uint64_t)1 << i));
    return res;
}

int32_t cntbits(uint64_t mask)
{
    int32_t cnt = 0;
    for (int32_t i = 0; i < 64; i++)
        cnt += !!(mask & ((uint64_t)1 << i));
    return cnt;
}

void print_key(void *key)
{
    printf("<");
    printf("%d", ((axis_t *)key)[0]);
    for (int32_t i = 1; i < DIM; i++)
        printf(",%d", ((axis_t *)key)[i]);
    printf(">");
}

void print_val(void *val)
{
    printf("%d", *((int32_t *)val));
}

bool compare(void *lhs, void *rhs)
{
    for (int32_t i = 0; i < DIM; i++) {
        if (((axis_t *)lhs)[i] < ((axis_t *)rhs)[i])
            return true;
        if (((axis_t *)lhs)[i] > ((axis_t *)rhs)[i])
            return false;
    }
    return false;
}

bool read_line(uint64_t *D, uint64_t *S, uint64_t *R, int32_t *n, int32_t *m)
{
    *n = 0;
    *m = 0;

    if (!read_diagram(D, stdin))
        return false;

    assert(fgetc(stdin) == ' ');
    while (read_schematics(S + *n, stdin)) {
        assert(*n < BUFFER_LEN);
        (*n)++;
    }
    while (fgetuint(R + *m, stdin)) {
        assert(R[*m] <= DP_MAX);
        assert(*m < BUFFER_LEN);
        (*m)++;
    }

    return true;
}

int64_t solve(uint64_t *S, uint64_t *R, int32_t n, int32_t m)
{
    matrix_t M;
    matrix_construct(&M, n, m);
    for (int32_t x = 0; x < n; x++)
        for (int32_t y = 0; y < m; y++)
            matrix_set(&M, x, y, !!(S[x] & (1 << y)));

    if (matrix_is_total_unimodular(&M)) {
        printf("true\n");
    }
    else {
        matrix_print(&M);
        printf("false\n");
    }
}

int main()
{
    uint64_t diagram;
    uint64_t schematics[BUFFER_LEN];
    uint64_t requirements[BUFFER_LEN];
    int32_t n = 0;
    int32_t m = 0;

    int64_t sum = 0;
    while (read_line(&diagram, schematics, requirements, &n, &m))
        sum += solve(schematics, requirements, n, m);
    printf("%ld\n", sum);
}

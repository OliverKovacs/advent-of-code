#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MIN(a,b) (((a)>(b))?(b):(a))

#define _GET matrix_get
#define _SET matrix_set

typedef struct matrix_t {
    int32_t n;
    int32_t m;
    double *buffer;
} matrix_t;

void matrix_construct(matrix_t *M, int32_t n, int32_t m)
{
    M->n = n;
    M->m = m;
    M->buffer = (double *)malloc(M->n * M->m * sizeof(double));
    assert(M->buffer != NULL);
}

void matrix_destruct(matrix_t *M)
{
    free(M->buffer);
}

double matrix_get(matrix_t *M, int32_t x, int32_t y)
{
    assert(0 <= x && x < M->n);
    assert(0 <= y && y < M->m);
    return M->buffer[y * M->n + x];
}

void matrix_set(matrix_t *M, int32_t x, int32_t y, double v)
{
    assert(0 <= x && x < M->n);
    assert(0 <= y && y < M->m);
    M->buffer[y * M->n + x] = v;
}

void dswap__(double *a, double *b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void matrix_swap_cols(matrix_t *M, int32_t x1, int32_t x2)
{
    assert(0 <= x1 && x2 < M->n);
    assert(0 <= x1 && x2 < M->n);
    for (int32_t y = 0; y < M->m; y++)
        dswap__(M->buffer + y * M->n + x1, M->buffer + y * M->n + x2);
}

void matrix_submatrix(
    matrix_t *M,
    matrix_t *S,
    int32_t x1,
    int32_t y1,
    int32_t x2,
    int32_t y2
) {
    assert(0 <= x1 && x1 < M->n);
    assert(0 <= y1 && y1 < M->m);
    assert(0 <= x2 && x2 <= M->n);
    assert(0 <= y2 && y2 <= M->m);
    matrix_construct(S, x2 - x1, y2 - y1);
    for (int32_t x = x1; x < x2; x++)
        for (int32_t y = y1; y < y2; y++)
            _SET(S, x - x1, y - y1, _GET(M, x, y));
}

double matrix_det(matrix_t *M)
{
    assert(M != NULL);
    assert(M->n == M->m);

    const double EPS = 1e-9;
    double det = 1;

    for (int32_t i = 0; i < M->n; i++) {
        int32_t k = i;
        for (int32_t j = i + 1; j < M->n; j++)
            if (fabs(_GET(M, j, i)) > fabs(_GET(M, k, i)))
                k = j;
        if (fabs(_GET(M, k, i)) < EPS) {
            det = 0;
            break;
        }

        matrix_swap_cols(M, i, k);
        if (i != k)
            det = -det;
        det *= _GET(M, i, i);
        for (int32_t j = i + 1; j < M->n; j++)
            _SET(M, i, j, _GET(M, i, j) / _GET(M, i, i));
        for (int j = 0; j < M->n; j++)
            if (j != i && fabs(_GET(M, j, i)) > EPS)
                for (int32_t k = i + 1; k < M->n; k++)
                    _SET(M, j, k, _GET(M, j, k) - _GET(M, i, k) * _GET(M, j, i));
    }

    return det;
}

bool matrix_is_total_unimodular(matrix_t *M)
{
    for (int32_t x1 = 0; x1 < M->n; x1++)
        for (int32_t y1 = 0; y1 < M->m; y1++)
            for (int32_t k = 0; k <= MIN(M->n - x1, M->m - y1); k++) {
                    matrix_t S;
                    matrix_submatrix(M, &S, x1, y1, x1 + k, y1 + k);
                    double det = matrix_det(&S);
                    if (det != 0 && det != -1 && det != 1)
                        return false;
                    matrix_destruct(&S);
                }

    return true;
}

void matrix_print(matrix_t *M)
{
    for (int32_t x = 0; x < M->n; x++) {
        printf("[");
        if (M->m > 0);
            printf("%f", matrix_get(M, x, 0));
        for (int32_t y = 1; y < M->m; y++)
            printf(" %f", matrix_get(M, x, y));
        printf("]\n");
    }
}

#endif /* MATRIX_H */

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 512

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)>(b))?(b):(a))

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

bool is_valid(int32_t a, int32_t b, int64_t *x, int64_t *y, int32_t n)
{
    int64_t rect_l = MIN(x[a], x[b]);
    int64_t rect_r = MAX(x[a], x[b]);
    int64_t rect_b = MIN(y[a], y[b]);
    int64_t rect_t = MAX(y[a], y[b]);

    for (int32_t i = 0; i < n; i++) {
        int32_t j = (i + 1) % n;
        assert(x[i] == x[j] || y[i] == y[j]);

        int64_t line_l = MIN(x[i], x[j]);
        int64_t line_r = MAX(x[i], x[j]);
        int64_t line_b = MIN(y[i], y[j]);
        int64_t line_t = MAX(y[i], y[j]);

        // if (!(line_r <= rect_l || rect_l <= line_l || line_t <= rect_b || rect_t <= line_b))
        if (!(rect_l >= line_r || rect_r <= line_l || rect_t <= line_b || rect_b >= line_t))
            return false;
    }
    return true;
}

int64_t area(int32_t a, int32_t b, int64_t *x, int64_t *y)
{
    return (int64_t)(abs(x[a] - x[b]) + 1) * (abs(y[a] - y[b]) + 1);
}

int main()
{
    int64_t x[BUFFER_LEN];
    int64_t y[BUFFER_LEN];
    int64_t e;
    int32_t n = 0;

    while (fgetint(&e, stdin)) {
        assert(n < BUFFER_LEN);
        x[n] = e;
        assert(fgetint(&e, stdin));
        y[n] = e;
        n++;
    }

    int64_t m = -1;
    for (int32_t i = 0; i < n; i++)
        for (int32_t j = i + 1; j < n; j++)
            if (is_valid(i, j, x, y, n))
                m = MAX(m, area(i, j, x, y));

    printf("%ld\n", m);
    // 1525241870
}

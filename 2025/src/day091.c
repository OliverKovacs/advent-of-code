#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 512

#define MAX(a,b) (((a)>(b))?(a):(b))
#define ABS(a) (MAX((a),(-a)))

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
            m = MAX(m, (ABS(x[i] - x[j]) + 1) * (ABS(y[i] - y[j]) + 1));

    printf("%ld\n", m);
    // 4759930955
}

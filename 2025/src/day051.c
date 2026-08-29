#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 2048

typedef struct range_t {
    uint64_t l;
    uint64_t r;
} range_t;

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

void read_input(range_t *ranges, uint64_t *ids, int32_t *n, int32_t *m)
{
    *n = 0;
    *m = 0;

    while (fgetuint(&(ranges[*n].l), stdin)) {
        assert(fgetuint(&(ranges[*n].r), stdin));
        ranges[*n].r++;
        (*n)++;
        assert(*n < N);
    }

    while (fgetuint(ids + *m, stdin)) {
        (*m)++;
        assert(*m < N);
    }
}

bool in_range(range_t *ranges, int32_t n, uint64_t id)
{
    for (int32_t i = 0; i < n; i++)
        if (ranges[i].l <= id && id < ranges[i].r) {
            return true;
        }
    return false;
}

int main()
{
    range_t ranges[N];
    uint64_t ids[N];
    int32_t n = 0;
    int32_t m = 0;
    read_input(ranges, ids, &n, &m);
    int32_t count = 0;
    for (int32_t i = 0; i < m; i++)
        count += in_range(ranges, n, ids[i]);
    printf("%d\n", count);
}

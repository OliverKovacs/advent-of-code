#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) (((a)>(b))?(b):(a))
#define MAX(a,b) (((a)<(b))?(b):(a))
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

void merge_range(range_t *ranges, int32_t *n, range_t *range)
{
    range_t tmp[N];
    int32_t m = *n;
    memcpy(tmp, ranges, m * sizeof(range_t));
    *n = 0;

    for (int32_t i = 0; i < m; i++) {
        if (tmp[i].l < range->l) {
            ranges[*n].l = tmp[i].l;
            ranges[*n].r = MIN(tmp[i].r, range->l);
            (*n)++;
            assert(*n < N);
        }
        if (range->r < tmp[i].r) {
            ranges[*n].l = MAX(tmp[i].l, range->r);
            ranges[*n].r = tmp[i].r;
            (*n)++;
            assert(*n < N);
        }
    }
    ranges[*n] = *range;
    (*n)++;
    assert(*n < N);
}

void merge_ranges(range_t *ranges, int32_t *n)
{
    range_t tmp[N];
    int32_t m = *n;
    memcpy(tmp, ranges, m * sizeof(range_t));
    *n = 0;

    for (int32_t i = 0; i < m; i++)
        merge_range(ranges, n, tmp + i);
}

uint64_t count_ids(range_t *ranges, int32_t n)
{
    uint64_t count = 0;
    for (int32_t i = 0; i < n; i++)
        count += ranges[i].r - ranges[i].l;
    return count;
}

int main()
{
    range_t ranges[N];
    uint64_t ids[N];
    int32_t n = 0;
    int32_t m = 0;
    read_input(ranges, ids, &n, &m);
    merge_ranges(ranges, &n);
    printf("%lu\n", count_ids(ranges, n));
}

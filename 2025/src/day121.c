#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 6
#define N 1024

bool fgetuint(int32_t *n, FILE *stream)
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

int32_t cntbits(uint16_t mask)
{
    int32_t cnt = 0;
    for (int32_t i = 0; i < 16; i++)
        cnt += !!(mask & ((uint64_t)1 << i));
    return cnt;
}

typedef struct case_t {
    int32_t w;
    int32_t h;
    int32_t counts[T];
} case_t;

void read_tile(uint16_t *tile)
{
    *tile = 0;
    fgetc(stdin);
    assert(fgetc(stdin) == ':');
    assert(fgetc(stdin) == '\n');
    for (int32_t y = 0; y < 3; y++) {
        for (int32_t x = 0; x < 3; x++)
            *tile |= (fgetc(stdin) == '#') << (3 * y + x);
        assert(fgetc(stdin) == '\n');
    }
    assert(fgetc(stdin) == '\n');
}

void read_input(uint16_t *tiles, case_t * cases, int32_t *n)
{
    for (int32_t i = 0; i < T; i++)
        read_tile(tiles + i);

    *n = 0;

    while (fgetuint(&(cases[*n].w), stdin)) {
        assert(fgetuint(&(cases[*n].h), stdin));
        assert(fgetc(stdin) == ' ');
        for (int32_t i = 0; i < T; i++)
            assert(fgetuint(&(cases[*n].counts[i]), stdin));
        (*n)++;
    }
}

bool is_packable(uint16_t *tiles, case_t *c)
{
    int32_t area = 0;
    int32_t count = 0;
    for (int32_t i = 0; i < T; i++) {
        area += c->counts[i] * cntbits(tiles[i]);
        count += c->counts[i];
    }

    if (area > c->w * c->h)
        return false;

    if (area <= c->w * c->h)
        return true;

    if (((c->w / 3) * (c->h / 3)) > count)
        return true;

    assert(false);
}

int main() {
    uint16_t tiles[T];
    case_t cases[N];
    int32_t n;
    read_input(tiles, cases, &n);

    int32_t count = 0;
    for (int32_t i = 0; i < n; i++)
        count += is_packable(tiles, cases + i);
    printf("%d\n", count);
}

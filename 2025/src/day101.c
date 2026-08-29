#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LEN 512

#define MIN(a,b) (((a)>(b))?(b):(a))

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
        *x |= (1 << n);
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

int32_t solve(uint64_t D, uint64_t *S, int32_t n)
{
    int32_t best = n + 1;

    for (uint64_t i = 0; i < ((uint64_t)1 << n); i++)
        if (nxor(S, n, i) == D)
            best = MIN(best, cntbits(i));

    assert(best != n + 1);
    return best;
}

int main()
{
    uint64_t D;
    uint64_t x;
    int64_t sum = 0;
    while (read_diagram(&D, stdin)) {
        uint64_t S[BUFFER_LEN];
        uint64_t R[BUFFER_LEN];
        int32_t n = 0;
        int32_t m = 0;

        assert(fgetc(stdin) == ' ');
        while (read_schematics(S + n, stdin)) {
            assert(n < BUFFER_LEN);
            n++;
        }
        while (fgetuint(R + m, stdin)) {
            assert(m < BUFFER_LEN);
            m++;
        }
        sum += solve(D, S, n);
    }

    printf("%ld\n", sum);
    // 517
}

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 256

typedef struct field_t {
    int32_t w;
    int32_t h;
    char **arr;
} field_t;

void start(field_t *f, int32_t *x, int32_t *y)
{
    *y = 0;
    *x = -1;
    for (int32_t i = 0; i < f->w; i++)
        if ((f->arr)[0][i] == 'S')
            *x = i;

    assert(x != -1);
}

int32_t solve(field_t *f, int32_t x, int32_t y) {
    if (x < 0 || f->w <= x || y < 0 || f->h <= y)
        return 0;

    switch((f->arr)[y][x]) {
        case 'X': return 0;
        case '^':
            (f->arr)[y][x] = 'X';
            return 1 + solve(f, x - 1, y) + solve(f, x + 1, y);
        default:
            return solve(f, x, y + 1);
    }
}

int main()
{
    char buffer[BUFFER_LEN];
    char *array[BUFFER_LEN];
    int32_t w = -1;
    int32_t h = 0;

    while (fgets(buffer, sizeof buffer, stdin)) {
        size_t len = strlen(buffer);
        assert(len < BUFFER_LEN - 1);
        if (w == -1)
            w = len;
        assert(w == len);
        assert(h < BUFFER_LEN);
        array[h] = (char *)malloc(w * sizeof(char));
        assert(array[h] != NULL);
        memcpy(array[h], buffer, w);
        h++;
    }

    field_t field = {.w = w, .h = h, .arr = array};
    int32_t x, y;
    start(&field, &x, &y);
    int32_t s = solve(&field, x, y);
    printf("%d\n", s);
    // 1615
}

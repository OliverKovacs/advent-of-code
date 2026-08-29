#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <stack.h>

#define ALPH_MIN 'a'
#define ALPH_MAX 'z'
#define ALPH_N (ALPH_MAX - ALPH_MIN + 1)
#define NAME_N (ALPH_N * ALPH_N * ALPH_N)
#define N 1024
#define M 1024

void assert_valid_name(uint32_t name)
{
    char *str = (char *)&name;
    assert(ALPH_MIN <= str[0] && str[0] <= ALPH_MAX);
    assert(ALPH_MIN <= str[1] && str[1] <= ALPH_MAX);
    assert(ALPH_MIN <= str[2] && str[2] <= ALPH_MAX);
    assert(str[3] == '\0');
}

bool read_name(uint32_t *name, FILE *stream)
{
    char *str = (char *)name;
    str[0] = fgetc(stream);
    if (str[0] < 'a' || 'z' < str[0])
        return false;
    str[1] = fgetc(stream);
    str[2] = fgetc(stream);
    str[3] = '\0';
    assert_valid_name(*name);
    return true;
}

int32_t name_to_idx(uint32_t name) {
    assert_valid_name(name);
    char *str = (char *)&name;
    return (str[0] - ALPH_MIN) * ALPH_N * ALPH_N
        + (str[1] - ALPH_MIN) * ALPH_N
        + (str[2] - ALPH_MIN);
}

void translate(uint32_t name, int32_t *n, int32_t *name_to_id, uint32_t *id_to_name)
{
    if (name_to_id[name_to_idx(name)] != -1)
        return;

    assert(*n < N);
    name_to_id[name_to_idx(name)] = *n;
    id_to_name[*n] = name;
    (*n)++;
}

// kahn's algorithm
void topological_sort(int32_t *V, int32_t *E, int32_t n, stack_t *T) {
    printf("sort...\n");
    int32_t indeg[N];
    for (int32_t i = 0; i < n; i++)
        indeg[i] = 0;

    for (int32_t i = 0; i < n; i++)
        for (int32_t j = 0; j < V[i]; j++)
            indeg[E[i * M + j]]++;

    stack_t S;
    stack_construct(&S, N, sizeof(int32_t));
    for (int32_t i = 0; i < n; i++)
        if (indeg[i] == 0)
            stack_push(&S, &i);

    printf("indegs: \n");
    for (int32_t i = 0; i < n; i++)
        printf("%d ", indeg[i]);
    printf("\n");

    assert(S.size > 0);
    while (S.size > 0) {
        int32_t v;
        stack_pop(&S, &v);
        stack_push(T, &v);
        for (int32_t i = 0; i < V[v]; i++) {
            indeg[E[v * M + i]]--;
            if (indeg[E[v * M + i]] == 0)
                stack_push(&S, E + v * M + i);
        }
    }

    stack_destruct(&S);
}

int32_t solve(int32_t *V, int32_t *E, int32_t n, int32_t s, int32_t t)
{
    stack_t T;
    stack_construct(&T, N, sizeof(int32_t));
    topological_sort(V, E, n, &T);
    assert(T.size == n);

    printf("s/t %d/%d\n", s, t);
    printf("topo: ");
    for (int32_t i = 0; i < T.size; i++)
        printf("%d ", ((int32_t *)T.buffer)[i]);
    printf("\n");

    int64_t dp[N];
    for (int32_t i = 0; i < n; i++)
        dp[i] = 0;
    dp[s] = 1;

    for (int32_t i = 0; i < n; i++) {
        int32_t v = ((int32_t *)T.buffer)[i];
        for (int32_t j = 0; j < V[v]; j++)
            dp[E[v * M + j]] += dp[v];
    }

    stack_destruct(&T);
    return dp[t];
}

int main()
{
    int32_t name_to_id[NAME_N];
    for (int32_t i = 0; i < NAME_N; i++)
        name_to_id[i] = -1;

    fflush(stdout);

    uint32_t id_to_name[N];


    int32_t V[N];
    int32_t E[N * M];

    int32_t n = 0;
    uint32_t curr;
    uint32_t next;
    while (read_name(&curr, stdin)) {
        translate(curr, &n, name_to_id, id_to_name);
        int32_t v = name_to_id[name_to_idx(curr)];
        V[v] = 0;
        assert(getc(stdin) == ':');
        while (getc(stdin) == ' ') {
            assert(V[v] < M);
            read_name(&next, stdin);
            translate(next, &n, name_to_id, id_to_name);
            int32_t u = name_to_id[name_to_idx(next)];
            E[v * M + V[v]] = u;
            V[v]++;
        }
    }

    printf("translation: \n");
    for (int32_t i = 0; i < n; i++)
        printf("%d: %s\n", i, (char *)&id_to_name[i]);


    printf("degs: \n");
    for (int32_t i = 0; i < n; i++)
        printf("%d ", V[i]);
    printf("\n");

    int32_t s = name_to_id[name_to_idx(*((int32_t *)"you"))];
    int32_t t = name_to_id[name_to_idx(*((int32_t *)"out"))];

    int32_t res = solve(V, E, n, s, t);
    printf("%d\n", res);
    // 658
}

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <graph.h>
#include <stack.h>

#define ALPH_MIN 'a'
#define ALPH_MAX 'z'
#define ALPH_N (ALPH_MAX - ALPH_MIN + 1)
#define NAME_N (ALPH_N * ALPH_N * ALPH_N)
#define N 4096
#define MM 256

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

void construct_layer_graph(graph_t *G, graph_t *Gp, int32_t dac, int32_t fft)
{
    graph_construct(Gp, 4 * G->n, G->M);

    for (int32_t i = 0; i < G->n; i++)
        if (i != dac && i != fft)
            for (int32_t j = 0; j < G->deg[i]; j++)
                for (int32_t l = 0; l < 4; l++)
                    graph_add_edge(
                        Gp,
                        l * G->n + i,
                        l * G->n + graph_adj(G, i)[j]
                    );

    // dac
    for (int32_t i = 0; i < G->deg[dac]; i++) {
        graph_add_edge(Gp, 0 * G->n + dac, 1 * G->n + graph_adj(G, dac)[i]);
        graph_add_edge(Gp, 2 * G->n + dac, 3 * G->n + graph_adj(G, dac)[i]);
    }

    // fft
    for (int32_t i = 0; i < G->deg[fft]; i++) {
        graph_add_edge(Gp, 0 * G->n + fft, 2 * G->n + graph_adj(G, fft)[i]);
        graph_add_edge(Gp, 1 * G->n + fft, 3 * G->n + graph_adj(G, fft)[i]);
    }
}

// kahn's algorithm
void topological_sort(graph_t *G, stack_t *T) {
    int32_t indeg[N];
    for (int32_t i = 0; i < G->n; i++)
        indeg[i] = 0;

    for (int32_t i = 0; i < G->n; i++)
        for (int32_t j = 0; j < G->deg[i]; j++)
            indeg[graph_adj(G, i)[j]]++;

    stack_t S;
    stack_construct(&S, N, sizeof(int32_t));
    for (int32_t i = 0; i < G->n; i++)
        if (indeg[i] == 0)
            stack_push(&S, &i);

    assert(S.size > 0);         // graph not acyclic
    while (S.size > 0) {
        int32_t v;
        stack_pop(&S, &v);
        stack_push(T, &v);
        for (int32_t i = 0; i < G->deg[v]; i++) {
            int32_t next = graph_adj(G, v)[i];
            indeg[next]--;
            if (indeg[next] == 0)
                stack_push(&S, &next);
        }
    }

    stack_destruct(&S);
    assert(T->size == G->n);
}

__int128_t count_paths(graph_t *G, int32_t s, int32_t t)
{
    stack_t T;
    stack_construct(&T, N, sizeof(int32_t));
    topological_sort(G, &T);

    __int128_t dp[N];
    for (int32_t i = 0; i < G->n; i++)
        dp[i] = 0;
    dp[s] = 1;

    for (int32_t i = 0; i < G->n; i++) {
        int32_t v = ((int32_t *)T.buffer)[i];
        for (int32_t j = 0; j < G->deg[v]; j++)
            dp[graph_adj(G, v)[j]] += dp[v];
    }

    stack_destruct(&T);
    return dp[t];
}

int main()
{
    int32_t name_to_id[NAME_N];
    for (int32_t i = 0; i < NAME_N; i++)
        name_to_id[i] = -1;

    uint32_t id_to_name[N];

    int32_t V[N];
    int32_t E[N * MM];

    int32_t n = 0;
    uint32_t curr;
    while (read_name(&curr, stdin)) {
        translate(curr, &n, name_to_id, id_to_name);
        int32_t v = name_to_id[name_to_idx(curr)];
        V[v] = 0;
        assert(getc(stdin) == ':');
        while (getc(stdin) == ' ') {
            assert(V[v] < MM);
            uint32_t next;
            read_name(&next, stdin);
            translate(next, &n, name_to_id, id_to_name);
            int32_t u = name_to_id[name_to_idx(next)];
            E[v * MM + V[v]] = u;
            V[v]++;
        }
    }

    graph_t G;
    graph_construct(&G, n, MM);
    for (int32_t i = 0; i < n; i++)
        for (int32_t j = 0; j < V[i]; j++)
            graph_add_edge(&G, i, E[i * MM + j]);

    int32_t dac = name_to_id[name_to_idx(*((int32_t *)"dac"))];
    int32_t fft = name_to_id[name_to_idx(*((int32_t *)"fft"))];
    assert(4 * n < N);
    graph_t Gp;
    construct_layer_graph(&G, &Gp, dac, fft);

    int32_t s = name_to_id[name_to_idx(*((int32_t *)"svr"))];
    int32_t t = name_to_id[name_to_idx(*((int32_t *)"out"))];
    printf("%ld\n", count_paths(&Gp, s, 3 * n + t));
    // 371113003846800

    graph_destruct(&G);
    graph_destruct(&Gp);
}

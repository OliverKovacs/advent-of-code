#ifndef STACK_H
#define STACK_H

#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct stack_t {
    int32_t capacity;
    int32_t size;
    int32_t node;
    char *buffer;
} stack_t;

void stack_construct(stack_t *stack, int32_t capacity, int32_t node)
{
    stack->capacity = capacity;
    stack->size = 0;
    stack->node = node;
    stack->buffer = (char *)malloc(capacity * node);
    assert(stack->buffer != NULL);
}

void stack_destruct(stack_t *stack)
{
    free(stack->buffer);
}

void stack_push(stack_t *stack, void *value)
{
    assert(stack->size < stack->capacity);
    memcpy(stack->buffer + stack->size * stack->node, value, stack->node);
    stack->size++;
}

void stack_pop(stack_t *stack, void *value)
{
    assert(0 < stack->size);
    stack->size--;
    memcpy(value, stack->buffer + stack->size * stack->node, stack->node);
}

#endif /* STACK_H */

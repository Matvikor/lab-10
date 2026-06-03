#include "stack_lib.h"
#include <stdlib.h>


struct stack_t {
    int* data;
    size_t capacity;
    size_t count;
};

static const size_t GROWTH_FACTOR = 2;

stack_t* stack_create(size_t initial_capacity) {
    if (initial_capacity == 0) return NULL;

    stack_t* stack = (stack_t*)malloc(sizeof(stack_t));
    if (!stack) return NULL;

    stack->data = (int*)calloc(initial_capacity, sizeof(int));
    if (!stack->data) {
        free(stack);
        return NULL;
    }

    stack->capacity = initial_capacity;
    stack->count = 0;
    return stack;
}

void stack_destroy(stack_t* stack) {
    if (stack) {
        free(stack->data);
        free(stack);
    }
}

stack_err_t stack_push(stack_t* stack, int value) {
    if (!stack) return STACK_ERR_NULL_PTR;

    if (stack->count >= stack->capacity) {
        size_t new_capacity = stack->capacity * GROWTH_FACTOR;
        if (new_capacity < stack->capacity) return STACK_ERR_ALLOC;

        int* new_data = (int*)realloc(stack->data, new_capacity * sizeof(int));
        if (!new_data) return STACK_ERR_ALLOC;

        stack->data = new_data;
        stack->capacity = new_capacity;
    }

    stack->data[stack->count] = value;
    stack->count++;
    return STACK_OK;
}

stack_err_t stack_pop(stack_t* stack, int* out_value) {
    if (!stack || !out_value) return STACK_ERR_NULL_PTR;
    if (stack->count == 0) return STACK_ERR_EMPTY;

    stack->count--;
    *out_value = stack->data[stack->count];
    return STACK_OK;
}

stack_err_t stack_peek(const stack_t* stack, int* out_value) {
    if (!stack || !out_value) return STACK_ERR_NULL_PTR;
    if (stack->count == 0) return STACK_ERR_EMPTY;

    *out_value = stack->data[stack->count - 1];
    return STACK_OK;
}

int stack_is_empty(const stack_t* stack) {
    return (stack && stack->count == 0) ? 1 : 0;
}

int stack_is_full(const stack_t* stack) {
    return (stack && stack->count >= stack->capacity) ? 1 : 0;
}

size_t stack_size(const stack_t* stack) {
    return stack ? stack->count : 0;
}
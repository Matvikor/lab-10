#include <stdio.h>
#include <assert.h>
#include "stack_lib.h"

static int passed = 0, failed = 0;
#define CHECK(cond, msg) do { if (!(cond)) { printf("FAIL: %s\n", msg); failed++; } else passed++; } while(0)

void test_lifecycle() {
    CHECK(stack_create(0) == NULL, "Create with 0 capacity");
    stack_t* s = stack_create(2);
    CHECK(s != NULL && stack_size(s) == 0, "Create valid");
    CHECK(stack_is_empty(s) == 1, "Empty initially");
    stack_destroy(s);
    stack_destroy(NULL);
}

void test_operations() {
    stack_t* s = stack_create(2);
    int v = 0;
    CHECK(stack_push(s, 10) == STACK_OK, "Push 10");
    CHECK(stack_push(s, 20) == STACK_OK, "Push 20");
    CHECK(stack_is_full(s) == 1, "Full after capacity");
    
    CHECK(stack_peek(s, &v) == STACK_OK && v == 20, "Peek top");
    CHECK(stack_pop(s, &v) == STACK_OK && v == 20, "Pop top");
    CHECK(stack_pop(s, &v) == STACK_OK && v == 10, "Pop second");
    CHECK(stack_is_empty(s) == 1, "Empty after pops");
    
    CHECK(stack_pop(s, &v) == STACK_ERR_EMPTY, "Pop empty error");
    CHECK(stack_push(NULL, 5) == STACK_ERR_NULL_PTR, "Push null stack");
    stack_destroy(s);
}

void test_expand() {
    stack_t* s = stack_create(1);
    for (int i = 0; i < 100; i++) CHECK(stack_push(s, i) == STACK_OK, "Push expand");
    CHECK(stack_size(s) == 100, "Size after expand");
    int v;
    for (int i = 99; i >= 0; i--) {
        CHECK(stack_pop(s, &v) == STACK_OK && v == i, "Pop reverse");
    }
    stack_destroy(s);
}

int main(void) {
    printf("=== C Tests ===\n");
    test_lifecycle();
    test_operations();
    test_expand();
    printf("Passed: %d | Failed: %d\n", passed, failed);
    return failed > 0;
}
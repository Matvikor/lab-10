#include <stdio.h>
#include "stack_lib.h"

int main(void) {
    printf("=== Stack Library Demo ===\n");
    stack_t* s = stack_create(3);
    if (!s) { printf("Allocation failed.\n"); return 1; }

    printf("Pushing: 10, 20, 30\n");
    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);

    int val;
    printf("Peek: %d\n", (stack_peek(s, &val) == STACK_OK) ? val : -1);
    
    printf("Popping sequence: ");
    while (!stack_is_empty(s)) {
        stack_pop(s, &val);
        printf("%d ", val);
    }
    printf("\n");
    
    printf("Final size: %zu\n", stack_size(s));
    stack_destroy(s);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct stack_node {
    int data;
    struct stack_node* next;
};

struct stack {
    struct stack_node* top;
    int sz;
};

typedef struct stack Stack;

void stack_init(struct stack *st) {
    st->sz = 0;
    st->top = 0;
}
int stack_size(struct stack *st) {
    return st->sz;
}
bool stack_empty(struct stack *st) {
    return stack_size(st) == 0;
}
void stack_push(struct stack *st,int val) {
    struct stack_node *newNode = (struct stack_node*)malloc(sizeof(struct stack_node));
    newNode->data = val;
    newNode->next = st->top;
    st->top = newNode;
    st->sz++;
}
void stack_pop(struct stack *st) {
    assert(!stack_empty(st));
    struct stack_node *nextHead = st->top->next;
    free(st->top);
    st->top = nextHead;
    st->sz--;
}
int stack_top(struct stack *st) {
    assert(!stack_empty(st));
    return st->top->data;
}


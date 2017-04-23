#ifndef STACK_H
#define STACK_H


typedef struct Stack{
    int value;
    struct Stack* top;
}Stack;

Stack new_stack();
void push(Stack* m_stack, int a);
int pop(Stack* m_stack);
void free_stack(Stack* m_stack);
void check(Stack* m_stack);
#endif

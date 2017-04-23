#include<stdlib.h>
#include<stdio.h>
#include "stack.h"


Stack new_stack(){
    Stack ns;
    ns.top = NULL;
    ns.value = 0;
    return ns;
}

void push(Stack* m_stack, int a){
    Stack* tmp = m_stack;
    while ((*tmp).top != NULL){
        tmp = tmp->top;
    }

    (*tmp).top = (Stack*)malloc(sizeof(Stack));
    (*tmp).top->value = a;
    (*tmp).top->top = NULL;
}

void check(Stack* m_stack){
    Stack* tmp = m_stack;
    while ((*tmp).top != NULL){
        tmp = tmp->top;
        printf("%d", tmp->top->value);
    }
}

int pop(Stack* m_stack){
    if(m_stack->top == NULL){
        fprintf(stderr, "NULL STACK");
    }

    Stack *toremove = m_stack->top;
    Stack *newtop = m_stack;
    while (toremove->top != NULL){
        newtop = toremove;
        toremove = toremove->top;
    }
    newtop->top = NULL;
    int value = toremove->value;
    free(toremove);
    return value; 
}

void free_stack(Stack* m_stack){
    Stack *todelete = m_stack;
    Stack *next = m_stack->top;
    while(next != NULL){
        free(todelete); 
        next = next->top;
        todelete = next; 

    }
}


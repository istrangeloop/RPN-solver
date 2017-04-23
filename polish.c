#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include <time.h>


/*===============================================================
 *  
 *  função : getnterms
 *      .obtém o número de termos e de operações '?' na string de
 *      entrada
 *  input :
 *      .len : tamanho da string de entrada
 *      .input : a string de entrada
 *      .n_terms : ponteiro para o número de termos na string
 *      .n_ops : ponteiro para o número de operações na string
 *  output : 
 *      .n_terms : recebe n_spaces+1, número de espaços da string
 *      contando o último também
 *      .n_ops: recebe n_points, número de pontos de interrogação
 *      da string
 *
 * ============================================================*/

void getnterms(int len, char* input, int* n_terms, int* n_ops){
    int i, n_spaces = 0, n_points = 0;
    for(i = 0; i < len; i++){
        if(input[i] == ' ')
            n_spaces++;
        if(input[i] == '?')
            n_points++;
    }
    n_spaces++;
    
    *n_terms = n_spaces;
    *n_ops = n_points;
}

/*===============================================================
 *  
 *  função : fill_vector
 *      .preenche o vetor que contém a operação
 *  input :
 *      .input : a string de entrada
 *      .n_vec : ponteiro para o vetor que contém a operação
 *      .n_terms : número de termos na string, para loop.
 *  output : 
 *      .n_vec: recebe os operandos em ordem, e -1 no lugar dos
 *      operadores
 *
 * ============================================================*/

void fill_vector(char* input, int* n_vec, int n_terms){
    int i, j = 0; 
    char* split = strtok(input, " ");
    
    for(i = 0; i < n_terms; i++){
        if(*split == '?'){ 
            n_vec[i] = -1;
            j++;
        }
        else n_vec[i] = atoi(split);
        split = strtok(NULL, " ");
    }
}

/*===============================================================
 *  
 *  função : polish
 *      .avalia a expressão em notação polonesa com ajuda de uma
 *      pilha.
 *  input :
 *      .n_vec : o vetor com os números de entrada.
 *      .bitmask : mask de auxílio a bruteforce, cada bit corres-
 *      ponde a um operador + ou * a ser testado.
 *      .n_terms : número de termos na string, para loop.
 *  output : 
 *      .answer : resultado da operação.
 *
 * ============================================================*/

int polish(int* n_vec, int bitmask, int n_terms, int n_ops){
    int i, n = n_ops-1, op1, op2, newop, answer;
    Stack pilha = new_stack();
    for(i = 0; i < n_terms; i++){
        if(n_vec[i] == -1){
            op1 = pop(&pilha);
            op2 = pop(&pilha);
            newop = bitmask & (1 << n) ? (op1 * op2) : (op1 + op2);
            push(&pilha, newop);
            n--;
        }
        else push(&pilha, n_vec[i]);
    }
    answer = pop(&pilha);
    free(pilha.top);
    return answer;
}

/*===============================================================
 *  
 *  função : makestring
 *      .transforma a bitmask correspondente ao resultado correto
 *      na string de output do programa.
 *  input :
 *      .mask : a bitmask com a ordem certa dos operadores
 *      .output : ponteiro para a string de saída.
 *      .n_ops : número de operações na string, para loop.
 *  output : 
 *      .output : a string de operadores
 *
 * ============================================================*/

void makestring(int mask, char* output, int n_ops){
    int n = n_ops-1;
    while(n >= 0){
        output[n_ops - n - 1] = (mask & (1 << n)) ? '*' : '+';
        n--;
    }
    output[n_ops] = '\0';
}

int main(){
    
    char input[201]; 
    int n_terms, n_ops;
    fgets(input, 201, stdin);
    int result;
    scanf("%d", &result);    
    
    //obtem o numero de termos e de operações no vetor
    getnterms(strlen(input), input, &n_terms, &n_ops);

    //vetor dos números a serem empilhados
    int* n_vec;
    n_vec = malloc(sizeof(int)*n_terms);
    fill_vector(input, n_vec, n_terms);

    //numero total de combinações possíveis
    unsigned long long int n_possibilities = 1 << n_ops;
    int answer = 0;
    unsigned long long int bitmask;
    char* output;
    output = malloc(sizeof(char)*(n_ops+1));
    //testa tudo
    for(bitmask = 0; bitmask < n_possibilities; bitmask++){
        answer = polish(n_vec, bitmask, n_terms, n_ops);
        if(answer == result){
            makestring(bitmask, output, n_ops);
            printf("%s\n", output);
        }
    }
    free(output);
    free(n_vec);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>

void nivelfacil(int *vidas) {
    
    int num[4];
    int resposta_certa[4];
    char operacoes[5] = {'+', '-', '*', '/'};
    char op;

    // Geração de números aleatórios
    for(int i = 0; i < 4; i++){
        num[i] = rand() % 101;
    }

    // Realização das operações
    for(int i = 0; i < 3; i++) {
        if(operacoes[i] == '+') {
            resposta_certa[i] = num[i] + num[i+1];
            op = operacoes[i];
        } else if(operacoes[i] == '-') {
            resposta_certa[i] = num[i] - num[i+1];
            op = operacoes[i];
        } else if(operacoes[i] == '*') {
            resposta_certa[i] = num[i] * num[i+1];
            op = operacoes[i];
        } else if(operacoes[i] == '/') { 
            resposta_certa[i] = num[i] / num[i+1];
            op = operacoes[i];
        }
    }
    
    }

nint main () {
    int vidas = 3;
    nivelfacil(&vidas);
    printf("O jogo de nível fácil foi concluído.\n");
    return 0;
}

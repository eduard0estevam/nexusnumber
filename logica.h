// logica.h

#ifndef LOGICA_H
#define LOGICA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"
#include "questoes_main.c"

// Estrutura para armazenar perguntas e respostas
typedef struct {
    char pergunta[256];
    char resposta[256];
} Questao;

// Estrutura para armazenar pontuação com nome do jogador
typedef struct {
    char nome[50];
    int pontuacao;
} Pontuacao;

// Funções auxiliares
void trocar(Questao *a, Questao *b);
void embaralhar(Questao questoes[], int n);
void nivelPerguntas(int *vidas, Questao questoes[], int total_questoes);
void nivelFacil(int *vidas, Questao questoes[], int total_questoes);
void nivelMedio(int *vidas, Questao questoes[], int total_questoes);
void nivelDificil(int *vidas, Questao questoes[], int total_questoes);

#endif

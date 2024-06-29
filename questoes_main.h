// questoes_main.c

#ifndef QUESTOES_MAIN_H
#define QUESTOES_MAIN_H

#include "raylib.h"
#include "logica.h"

void exibirPerguntaGrafica(Questao questao, int vidas, int pontos, Font font, Color textColor);
void dividirTextoEmLinhas(char *texto, char *textoFormatado, int larguraMaxima, Font font, int tamanhoFonte);

#endif

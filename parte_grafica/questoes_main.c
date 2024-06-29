// questoes_main.c

#include "raylib.h"
#include "logica.h"
#include "questoes_grafico.h"

void exibirPerguntaGrafica(Questao questao, int vidas, int pontos, Font font, Color textColor) {
    char perguntaFormatada[512] = {0};
    dividirTextoEmLinhas(questao.pergunta, perguntaFormatada, SCREEN_WIDTH - 100, font, 20);
    DrawTextEx(font, perguntaFormatada, (Vector2){20, 110}, 20, 2, textColor);

    Vector2 posicaoResposta = {200, 170};
    Vector2 posicaoVidas = {200, 260};
    Vector2 posicaoPontos = {200, 280};

    DrawTextEx(font, "Sua resposta: ", posicaoResposta, 20, 2, textColor);
    DrawTextEx(font, respostaUsuario, (Vector2){posicaoResposta.x + 120, posicaoResposta.y}, 20, 2, textColor);
    DrawTextEx(font, TextFormat("Vidas: %d", vidas), posicaoVidas, 20, 2, textColor);
    DrawTextEx(font, TextFormat("Pontos: %d", pontos), posicaoPontos, 20, 2, textColor);
}

void dividirTextoEmLinhas(char *texto, char *textoFormatado, int larguraMaxima, Font font, int tamanhoFonte) {
    int larguraAtual = 0;
    int tamPalavra = 0;
    char palavra[256];
    char linha[1024] = "";
    char tempTexto[256];
    strcpy(tempTexto, texto);
    char *ptrPalavra = strtok(tempTexto, " ");

    while (ptrPalavra != NULL) {
        tamPalavra = MeasureTextEx(font, ptrPalavra, tamanhoFonte, 2).x;

        if (larguraAtual + tamPalavra >= larguraMaxima) {
            strcat(linha, "\n");
            strcat(textoFormatado, linha);
            strcpy(linha, "");
            larguraAtual = 0;
        }

        strcat(linha, ptrPalavra);
        strcat(linha, " ");
        larguraAtual += tamPalavra + MeasureTextEx(font, " ", tamanhoFonte, 2).x;

        ptrPalavra = strtok(NULL, " ");
    }

    strcat(textoFormatado, linha);
}

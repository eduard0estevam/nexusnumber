#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"

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
void trocar(Questao *a, Questao *b) {
    Questao temp = *a;
    *a = *b;
    *b = temp;
}

void embaralhar(Questao questoes[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        trocar(&questoes[i], &questoes[j]);
    }
}

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

void dividirTextoEmLinhas(char *texto, char *textoFormatado, int larguraMaxima, Font font, int tamanhoFonte) {
    int larguraAtual = 0;
    int tamPalavra = 0;
    char palavra[256];
    char linha[1024] = "";
    char tempTexto[256];
    strcpy(tempTexto, texto); // Criar uma cópia para não modificar o texto original
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

    // Adicionar a última linha
    strcat(textoFormatado, linha);
}

int main(void) {
    // Inicializa a janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NexusNumber");

    // Carrega a fonte customizada
    Font customFont = LoadFont("Daydream.ttf");

    // Carrega as imagens de fundo
    Texture2D background = LoadTexture("./imagens/background2.png");
    Texture2D kelryImage = LoadTexture("./imagens/kelry.png");
    Texture2D easyBackground = LoadTexture("./imagens/facil.png");

    // Define as cores
    Color textColor = WHITE;
    Color enterButtonColor = GREEN;
    Color enterButtonTextColor = BLACK;
    Color exitButtonColor = VIOLET;
    Color exitButtonTextColor = BLACK;
    Color levelButtonColor = ORANGE;
    Color levelButtonTextColor = BLACK;

    // Define as variáveis para os botões
    Rectangle enterButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50 };
    Rectangle exitButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 50 };
    Rectangle easyButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50 };
    Rectangle mediumButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 50 };
    Rectangle hardButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 90, 200, 50 };

    // Variáveis para controle do loop principal
    bool exitGame = false;
    bool gameStarted = false;
    bool showingLevelButtons = false;
    bool loading = false;
    bool loadingComplete = false;
    int selectedLevel = 0;
    int loadingTimer = 0;

    // Variáveis para o jogo
    int vidas = 3;
    int pontos = 0;
    Questao questoesFaceis[10] = {
        {"Pergunta 1:\n2, 6, 12, 20, 30, ? Qual eh o próximo número na sequencia?", "42"},
        {"Pergunta 2:\nA soma das idades de Ana e Bia eh 44. Ana eh 8 anos mais velha que Bia. Qual eh a idade de Ana?", "26"},
        {"Pergunta 3:\n13, 18 = 31\n7, 25 = 32\n12, 30 = 42\n26, 13 = ?", "39"},
        {"Pergunta 4:\nQual eh o proximo numero na sequencia: 1, 4, 9, 16, 25, ...?", "36"},
        {"Pergunta 5:\nJoao tem o dobro da idade de Pedro. Se a diferença de suas idades eh de 15 anos, quantos anos Joao tem?", "30"},
        {"Pergunta 6:\n4, 8 e 16: Qual eh o proximo numero?", "32"},
        {"Pergunta 7:\n + B = 60\nA - B = 40\n A / B = ?", "5"},
        {"Pergunta 8:\nEm um quadrado formado por 16 palitos, com quantos palitos eu posso fazer 2 quadrados ?", "4"},
        {"Pergunta 9:\nA media aritmetica de cinco numeros eh 12. Se um dos numeros eh 16, qual eh a media dos outros quatro numeros?", "11"},
        {"Pergunta 10:\n6 = 30\n 3 = 15\n 7 = 35\n 2 = ?", "10"},
    };
    int perguntaAtual = 0;
    char respostaUsuario[256] = {0};
    bool respostaCorreta = false;
    bool mostrandoPergunta = false;

    while (!WindowShouldClose() && !exitGame) {
        // Verifica se o botão "Entrar" foi clicado
        if (!gameStarted && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, enterButton)) {
                // Lógica para iniciar "carregamento"
                gameStarted = true;
                loading = true;
                loadingTimer = GetTime(); // Inicia a contagem de tempo para "Carregando..."
            }
            if (CheckCollisionPointRec(mousePoint, exitButton)) {
                // Lógica para sair do jogo
                exitGame = true;
            }
        }

        // Verifica se o tempo de "Carregando..." acabou
        if (loading && !loadingComplete) {
            int currentTime = GetTime();
            if (currentTime - loadingTimer >= 5) { // Mostra "Carregando..." por 5 segundos
                loading = false;
                showingLevelButtons = true; // Mostra os botões de nível após o carregamento
                loadingComplete = true; // Marca o carregamento como completo
            }
        }

        // Verifica se um dos botões de nível foi clicado
        if (showingLevelButtons && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, easyButton)) {
                selectedLevel = 1; // Fácil
                background = easyBackground; // Muda o fundo para o nível fácil
                showingLevelButtons = false; // Oculta os botões de nível
                mostrandoPergunta = true; // Inicia a exibição das perguntas
                embaralhar(questoesFaceis, 10);
            }
            else if (CheckCollisionPointRec(mousePoint, mediumButton)) {
                selectedLevel = 2; // Médio
                // Defina a lógica do nível médio aqui
                showingLevelButtons = false; // Oculta os botões de nível
            }
            else if (CheckCollisionPointRec(mousePoint, hardButton)) {
                selectedLevel = 3; // Difícil
                // Defina a lógica do nível difícil aqui
                showingLevelButtons = false; // Oculta os botões de nível
            }
        }

        // Lógica para exibir perguntas e receber respostas no nível fácil
        if (mostrandoPergunta && selectedLevel == 1) {
            if (IsKeyPressed(KEY_ENTER)) {
                if (strcmp(respostaUsuario, questoesFaceis[perguntaAtual].resposta) == 0) {
                    pontos += 10;
                    respostaCorreta = true;
                } else {
                    vidas--;
                    respostaCorreta = false;
                }
                perguntaAtual++;
                if (perguntaAtual >= 10 || vidas <= 0) {
                    mostrandoPergunta = false; // Termina as perguntas quando acabarem ou o jogador perder todas as vidas
                } else {
                    memset(respostaUsuario, 0, sizeof(respostaUsuario)); // Limpa a resposta do usuário
                }
            } else {
                int key = GetKeyPressed();
                if (key >= 32 && key <= 125 && strlen(respostaUsuario) < sizeof(respostaUsuario) - 1) {
                    int len = strlen(respostaUsuario);
                    respostaUsuario[len] = (char)key;
                    respostaUsuario[len + 1] = '\0';
                }
            }
        }

        // Desenho da tela
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);

        if (!loading && !gameStarted) {
            DrawTextEx(customFont, "NexusNumber", (Vector2){SCREEN_WIDTH / 2 - MeasureTextEx(customFont, "NexusNumber", 40, 2).x / 2, SCREEN_HEIGHT / 4}, 40, 2, textColor);
        }

        if (loadingComplete && showingLevelButtons && !loading) {
            DrawTextEx(customFont, "Selecione a dificuldade", (Vector2){SCREEN_WIDTH / 2 - MeasureTextEx(customFont, "Selecione a dificuldade", 25, 2).x / 2, SCREEN_HEIGHT / 4}, 25, 2, textColor);
        }

        if (!gameStarted) {
            DrawRectangleRec(enterButton, enterButtonColor);
            DrawRectangleRec(exitButton, exitButtonColor);
            DrawTextEx(customFont, "Entrar", (Vector2){enterButton.x + enterButton.width / 2 - MeasureTextEx(customFont, "Entrar", 20, 2).x / 2, enterButton.y + 15}, 20, 2, enterButtonTextColor);
            DrawTextEx(customFont, "Sair", (Vector2){exitButton.x + exitButton.width / 2 - MeasureTextEx(customFont, "Sair", 20, 2).x / 2, exitButton.y + 15}, 20, 2, exitButtonTextColor);
        }
        else if (showingLevelButtons && !loading) {
            DrawRectangleRec(easyButton, levelButtonColor);
            DrawRectangleRec(mediumButton, levelButtonColor);
            DrawRectangleRec(hardButton, levelButtonColor);
            DrawTextEx(customFont, "Facil", (Vector2){easyButton.x + easyButton.width / 2 - MeasureTextEx(customFont, "Facil", 20, 2).x / 2, easyButton.y + 15}, 20, 2, levelButtonTextColor);
            DrawTextEx(customFont, "Medio", (Vector2){mediumButton.x + mediumButton.width / 2 - MeasureTextEx(customFont, "Medio", 20, 2).x / 2, mediumButton.y + 15}, 20, 2, levelButtonTextColor);
            DrawTextEx(customFont, "Dificil", (Vector2){hardButton.x + hardButton.width / 2 - MeasureTextEx(customFont, "Dificil", 20, 2).x / 2, hardButton.y + 15}, 20, 2, levelButtonTextColor);
        }

        if (loading) {
            DrawTexture(kelryImage, SCREEN_WIDTH / 2 - kelryImage.width / 2, SCREEN_HEIGHT / 2 - kelryImage.height / 2 - 50, WHITE);
            DrawTextEx(customFont, "Carregando...", (Vector2){SCREEN_WIDTH / 2 - MeasureTextEx(customFont, "Carregando...", 30, 2).x / 2, SCREEN_HEIGHT / 2 + 120}, 30, 2, textColor);
        }

        // Desenha perguntas e recebe respostas no nível fácil
    // Desenha perguntas e recebe respostas no nível fácil
if (mostrandoPergunta && selectedLevel == 1) {
    char perguntaFormatada[512] = {0};
    dividirTextoEmLinhas(questoesFaceis[perguntaAtual].pergunta, perguntaFormatada, SCREEN_WIDTH - 100, customFont, 20);
    DrawTextEx(customFont, perguntaFormatada, (Vector2){20,110}, 20, 2, textColor);
    
    // Ajuste as posições de "Sua resposta", "Vidas" e "Pontos" aqui
    Vector2 posicaoResposta = {200, 170}; // Posição da "Sua resposta"
    
    Vector2 posicaoVidas = {200, 260};   // Posição das "Vidas"
    Vector2 posicaoPontos = {200, 280};  // Posição dos "Pontos"
    
    DrawTextEx(customFont, "Sua resposta: ", posicaoResposta, 20, 2, textColor);
    DrawTextEx(customFont, respostaUsuario, (Vector2){posicaoResposta.x + 120, posicaoResposta.y}, 20, 2, textColor);
    DrawTextEx(customFont, TextFormat("Vidas: %d", vidas), posicaoVidas, 20, 2, textColor);
    DrawTextEx(customFont, TextFormat("Pontos: %d", pontos), posicaoPontos, 20, 2, textColor);

    if (respostaCorreta) {
        DrawTextEx(customFont, "Correto!", (Vector2){20, 350}, 20, 2, GREEN);
    } else {
        DrawTextEx(customFont, "Errado! Tente novamente.", (Vector2){20, 350}, 20, 2, RED);
    }
}


        EndDrawing();
    }

    // Fecha a janela e limpa recursos
    UnloadFont(customFont);
    UnloadTexture(background);
    UnloadTexture(kelryImage);
    UnloadTexture(easyBackground);
    CloseWindow();

    return 0;
}

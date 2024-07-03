#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"

// Estrutura para armazenar perguntas e respostas
typedef struct {
    char pergunta[256];
    char resposta[256];
} Questao;

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

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

void MenuPrincipal(Font customFont, Texture2D background, Rectangle enterButton, Rectangle exitButton, Color enterButtonColor, Color enterButtonTextColor, Color exitButtonColor, Color exitButtonTextColor, Color titleColor) {
    DrawTexture(background, 0, 0, WHITE);
    DrawTextEx(customFont, "NexusNumber", (Vector2){SCREEN_WIDTH / 2 - 230, 170}, 50, 2, titleColor);
    DrawRectangleRec(enterButton, enterButtonColor);
    DrawTextEx(customFont, "Entrar", (Vector2){enterButton.x + 30, enterButton.y + 10}, 30, 2, enterButtonTextColor);
    DrawRectangleRec(exitButton, exitButtonColor);
    DrawTextEx(customFont, "Sair", (Vector2){exitButton.x + 50, exitButton.y + 10}, 30, 2, exitButtonTextColor);
}

void Carregando(Font customFont, Texture2D loadingImage, Color titleColor) {
    ClearBackground(BLACK);
    DrawTexture(loadingImage, (SCREEN_WIDTH - loadingImage.width) / 2, (SCREEN_HEIGHT - loadingImage.height) / 2, WHITE);
    DrawTextEx(customFont, "Carregando...", (Vector2){SCREEN_WIDTH / 2 - 155, SCREEN_HEIGHT / 2 + 240}, 40, 2, titleColor);
}

void MostrarNiveis(Font customFont, Texture2D background, Rectangle easyButton, Rectangle mediumButton, Rectangle hardButton, Color levelButtonColor, Color levelButtonTextColor, Color titleColor) {
    DrawTexture(background, 0, 0, WHITE);
    DrawTextEx(customFont, "Escolha o Nivel", (Vector2){SCREEN_WIDTH / 2 - 250, 160}, 40, 2, titleColor);
    DrawRectangleRec(easyButton, levelButtonColor);
    DrawTextEx(customFont, "Facil", (Vector2){easyButton.x + 45, easyButton.y + 10}, 30, 2, levelButtonTextColor);
    DrawRectangleRec(mediumButton, levelButtonColor);
    DrawTextEx(customFont, "Medio", (Vector2){mediumButton.x + 45, mediumButton.y + 10}, 30, 2, levelButtonTextColor);
    DrawRectangleRec(hardButton, levelButtonColor);
    DrawTextEx(customFont, "Dificil", (Vector2){hardButton.x + 36, hardButton.y + 10}, 30, 2, levelButtonTextColor);
}

void MostrarPergunta(Font customFont, Font chalkboyFont, Texture2D background, Questao questoes[], int perguntaAtual, char respostaUsuario[], Color textColor) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTextEx(chalkboyFont, questoes[perguntaAtual].pergunta, (Vector2){50, 100}, 30, 2, textColor);
    DrawTextEx(customFont, "Sua resposta:", (Vector2){50, 300}, 30, 2, textColor);
    DrawTextEx(customFont, respostaUsuario, (Vector2){50, 350}, 30, 2, textColor);

    // Captura a resposta do usuário
    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 125 && strlen(respostaUsuario) < 255) {
            int len = strlen(respostaUsuario);
            respostaUsuario[len] = (char)key;
            respostaUsuario[len + 1] = '\0';
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && strlen(respostaUsuario) > 0) {
        respostaUsuario[strlen(respostaUsuario) - 1] = '\0';
    }
}

int main(void) {
    // Inicializa a janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NexusNumber");

    // Carrega a fonte customizada
    Font customFont = LoadFont("04B_30__.TTF");
    Font chalkboyFont = LoadFontEx("Neat Chalk.ttf", 30, NULL, 0); // Fonte para o nível fácil, medio e dificil

    // Carrega as imagens de fundo e a imagem de carregamento
    Texture2D background = LoadTexture("./imagens/menu.png");
    Texture2D easyBackground = LoadTexture("./imagens/facil.png");
    Texture2D loadingImage = LoadTexture("./imagens/carregamento.png"); // Nova textura de carregamento
    Texture2D mediumBackground = LoadTexture("./imagens/medio.png");
    Texture2D hardBackground = LoadTexture("./imagens/hard11.png");

    // Define as cores
    Color textColor = WHITE;
    Color enterButtonColor = PINK;
    Color enterButtonTextColor = WHITE;
    Color exitButtonColor = PINK;
    Color exitButtonTextColor = WHITE;
    Color levelButtonColor = PINK;
    Color levelButtonTextColor = WHITE;

    // Define a cor do título NexusNumber usando hexadecimal #E91E63
    Color titleColor = (Color){233, 30, 99, 255};

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
    float loadingTimer = 0;

    // Variáveis para o jogo
    int vidas = 3;
    int pontos = 0;
    Questao questoesFaceis[10] = { 
        {"Pergunta 1:\n2, 6, 12, 20, 30, ? Qual eh o pr0ximo\n numero na sequencia?", "42"},
        {"Pergunta 2:\nA soma das idades de Ana e Bia eh 44. Ana eh 8 anos mais velha que Bia. Qual\n eh a idade de Ana?", "26"},
        {"Pergunta 3:\n13, 18 = 31\n7, 25 = 32\n12, 30 = 42\n26, 13 = ?", "39"},
        {"Pergunta 4:\nQual eh o proximo numero na sequencia\n: 1, 4, 9, 16, 25, ...?\n", "36"},
        {"Pergunta 5:\nJoao tem o dobro da idade de Pedro.\n Se a diferença\n de suas idades eh de 15 anos, quantos\n anos Joao tem?", "30"},
        {"Pergunta 6:\n4, 8 e 16: Qual eh o proximo numero?", "32"},
        {"Pergunta 7:\n + B = 60\nA - B = 40\n A / B = ?", "5"},
        {"Pergunta 8:\nEm um quadrado formado por 16 palitos, com \nquantos palitos eu posso fazer 2 quadrados ?", "4"},
        {"Pergunta 9:\nA media aritmetica de cinco numeros eh 12.\n Se um dos numeros eh 16, qual\n eh a media dos outros\n quatro numeros?", "11"},
        {"Pergunta 10:\n6 = 30\n 3 = 15\n 7 = 35\n 2 = ?", "10"},
    };
    Questao questoesMedias[5] =  {
        {"Pergunta 1:\nEm um saco ha 5 bolas vermelhas, 4 bolas azuis e 3 bolas verdes. Qual a probabilidade de se retirar uma bola azul?", "1/3"},
        {"Pergunta 2:\nSe o dobro de um número eh 24, qual eh a metade desse numero?", "12"},
        {"Pergunta 3:\nSe 5 maquinas podem completar um trabalho em 8 horas, quantas horas levarao 8 maquinas para completar o mesmo trabalho?", "5"},
        {"Pergunta 4:\nUm produto custa R$ 120,00. Apos um desconto de 25%, qual eh o novo preco?", "90"},
        {"Pergunta 5:\nQual eh a soma de 1/3 e 1/4?", "7/12"},
    };
    Questao questoesDificeis[5] = {
        {"Pergunta 1:\n9, 16 = 7\n4, 36 = 8\n121, 81 = 20\n 25, 49 = ?", "12"},
        {"Pergunta 2:\nEm um sistema de codificação, AB representa os algarismos do dia do nascimento de uma pessoa e CD os algarismos de seu mês de nascimento. Qual eh o mês de nascimento dessa pessoa se a data for trinta de julho?", "07"},
        {"Pergunta 3:\nSe 3 gatos caçam 3 ratos em 3 minutos, em quantos minutos levarão 100 gatos para caçar 100 ratos?", "3"},
        {"Pergunta 4:\nUm carro viaja a 60 km/h. Em quantas horas levará para percorrer 180 km?", "3"},
        {"Pergunta 5:\nSe a=1, b=2, c=3, ..., z=26, qual eh a soma das letras da palavra CAT?", "24"},
    };
    
    int perguntaAtual = 0;
    char respostaUsuario[256] = {0};
    bool respostaCorreta = false;
    bool mostrandoPergunta = false;

    // Seed para a função rand()
    srand(time(NULL));

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
            float currentTime = GetTime();
            if (currentTime - loadingTimer >= 5.0f) { // Mostra "Carregando..." por 5 segundos
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
                background = mediumBackground; // Muda o fundo para o nível médio
                showingLevelButtons = false; // Oculta os botões de nível
                mostrandoPergunta = true; // Inicia a exibição das perguntas
                embaralhar(questoesMedias, 5);
            }
            else if (CheckCollisionPointRec(mousePoint, hardButton)) {
                selectedLevel = 3; // Difícil
                background = hardBackground; // Muda o fundo para o nível difícil
                showingLevelButtons = false; // Oculta os botões de nível
                mostrandoPergunta = true; // Inicia a exibição das perguntas
                embaralhar(questoesDificeis, 5);
            }
        }

        // Lógica para exibir perguntas e receber respostas
        if (mostrandoPergunta) {
            Questao *questoes;
            int questoesCount;
            if (selectedLevel == 1) {
                questoes = questoesFaceis;
                questoesCount = 10;
            } else if (selectedLevel == 2) {
                questoes = questoesMedias;
                questoesCount = 5;
            } else if (selectedLevel == 3) {
                questoes = questoesDificeis;
                questoesCount = 5;
            }

            if (perguntaAtual < questoesCount) {
                // Renderiza a pergunta e a resposta do usuário
                MostrarPergunta(customFont, chalkboyFont, background, questoes, perguntaAtual, respostaUsuario, textColor);

                if (IsKeyPressed(KEY_ENTER)) {
                    if (strcmp(respostaUsuario, questoes[perguntaAtual].resposta) == 0) {
                        respostaCorreta = true;
                        pontos++;
                    } else {
                        respostaCorreta = false;
                        vidas--;
                    }
                    perguntaAtual++;
                    respostaUsuario[0] = '\0'; // Limpa a resposta do usuário
                }
            } else {
                // Todas as perguntas foram respondidas
                mostrandoPergunta = false;
                // Mostrar a pontuação final ou reiniciar o jogo
            }
        }

        // Desenha na tela
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Verifica se está no menu principal
        if (!gameStarted) {
            MenuPrincipal(customFont, background, enterButton, exitButton, enterButtonColor, enterButtonTextColor, exitButtonColor, exitButtonTextColor, titleColor);
        }
        
        // Verifica se está mostrando "Carregando..."
        if (loading && !loadingComplete) {
            Carregando(customFont, loadingImage, titleColor);
        }
        
        // Verifica se está mostrando os botões de nível
        if (showingLevelButtons) {
            MostrarNiveis(customFont, background, easyButton, mediumButton, hardButton, levelButtonColor, levelButtonTextColor, titleColor);
        }

        EndDrawing();
    }

    // Unload textures and fonts
    UnloadTexture(background);
    UnloadTexture(easyBackground);
    UnloadTexture(loadingImage);
    UnloadTexture(mediumBackground);
    UnloadTexture(hardBackground);
    UnloadFont(customFont);
    UnloadFont(chalkboyFont);

    CloseWindow();

    return 0;
}

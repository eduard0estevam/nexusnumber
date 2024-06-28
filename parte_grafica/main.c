#include <stdio.h>
#include "raylib.h"

#define SCREEN_WIDTH 727
#define SCREEN_HEIGHT 487

int main(void)
{
    // Inicializa a janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NexusNumber");

    // Carrega a fonte customizada
    Font customFont = LoadFont("Daydream.ttf");

    // Carrega a imagem de fundo
    Texture2D background = LoadTexture("./imagens/background2.png");

    // Carrega a imagem kelry.png
    Texture2D kelryImage = LoadTexture("./imagens/kelry.png");

    // Define as cores
    Color textColor = WHITE;
    Color enterButtonColor = GREEN;
    Color enterButtonTextColor = BLACK;
    Color exitButtonColor = PINK;
    Color exitButtonTextColor = BLACK;
    Color levelButtonColor = ORANGE;
    Color levelButtonTextColor = BLACK;

    // Define as variáveis para os botões
    Rectangle enterButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50 };
    Rectangle exitButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 50 };

    // Botões de níveis
    Rectangle easyButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50 };
    Rectangle mediumButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 50 };
    Rectangle hardButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 90, 200, 50 };

    // Variáveis para controle do loop principal
    bool exitGame = false;
    bool gameStarted = false;
    bool showingLevelButtons = false;
    bool loading = false;
    bool loadingComplete = false; // Indica se o carregamento está completo
    int selectedLevel = 0; // 0 - Nenhum, 1 - Fácil, 2 - Médio, 3 - Difícil
    int loadingTimer = 0; // Contador de tempo para "Carregando..."

    while (!WindowShouldClose() && !exitGame) // Loop principal do jogo
    {
        // Verifica se o botão "Entrar" foi clicado
        if (!gameStarted && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, enterButton))
            {
                // Lógica para iniciar "carregamento"
                gameStarted = true;
                loading = true;
                loadingTimer = GetTime(); // Inicia a contagem de tempo para "Carregando..."
            }
            if (CheckCollisionPointRec(mousePoint, exitButton))
            {
                // Lógica para sair do jogo
                exitGame = true;
            }
        }

        // Verifica se o tempo de "Carregando..." acabou
        if (loading && !loadingComplete)
        {
            int currentTime = GetTime();
            if (currentTime - loadingTimer >= 5) // Mostra "Carregando..." por 5 segundos
            {
                loading = false;
                showingLevelButtons = true; // Mostra os botões de nível após o carregamento
                loadingComplete = true; // Marca o carregamento como completo
            }
        }

        // Desenho da tela
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        // Desenha a imagem de fundo
        DrawTexture(background, 0, 0, WHITE);

        // Desenha o título do jogo apenas se não estiver carregando e o jogo não começou
        if (!loading && !gameStarted)
        {
            DrawTextEx(customFont, "NexusNumber", (Vector2){SCREEN_WIDTH / 2 - MeasureTextEx(customFont, "NexusNumber", 40, 2).x / 2, SCREEN_HEIGHT / 4}, 40, 2, textColor);
        }

        // Se o carregamento estiver completo, mostra "Selecione a dificuldade"
        if (loadingComplete && showingLevelButtons && !loading)
        {
            DrawTextEx(customFont, "Selecione a dificuldade", (Vector2){SCREEN_WIDTH / 2 - MeasureTextEx(customFont, "Selecione a dificuldade", 25, 2).x / 2, SCREEN_HEIGHT / 4}, 25, 2, textColor);
        }

        // Se o jogo não começou, desenha os botões "Entrar" e "Sair"
        if (!gameStarted)
        {
            DrawRectangleRec(enterButton, enterButtonColor);
            DrawRectangleRec(exitButton, exitButtonColor);

            DrawTextEx(customFont, "Entrar", (Vector2){enterButton.x + enterButton.width / 2 - MeasureTextEx(customFont, "Entrar", 20, 2).x / 2, enterButton.y + 15}, 20, 2, enterButtonTextColor);
            DrawTextEx(customFont, "Sair", (Vector2){exitButton.x + exitButton.width / 2 - MeasureTextEx(customFont, "Sair", 20, 2).x / 2, exitButton.y + 15}, 20, 2, exitButtonTextColor);
        }
        else if (showingLevelButtons && !loading)
        {
            // Desenha os botões de nível
            DrawRectangleRec(easyButton, levelButtonColor);
            DrawRectangleRec(mediumButton, levelButtonColor);
            DrawRectangleRec(hardButton, levelButtonColor);

            // Desenha os textos nos botões de nível
            DrawTextEx(customFont, "Facil", (Vector2){easyButton.x + easyButton.width / 2 - MeasureTextEx(customFont, "Facil", 20, 2).x / 2, easyButton.y + 15}, 20, 2, levelButtonTextColor);
            DrawTextEx(customFont, "Medio", (Vector2){mediumButton.x + mediumButton.width / 2 - MeasureTextEx(customFont, "Medio", 20, 2).x / 2, mediumButton.y + 15}, 20, 2, levelButtonTextColor);
            DrawTextEx(customFont, "Dificil", (Vector2){hardButton.x + hardButton.width / 2 - MeasureTextEx(customFont, "Dificil", 20, 2).x / 2, hardButton.y + 15}, 20, 2, levelButtonTextColor);
        }

        // Mostra o texto "Carregando..." após clicar em "Entrar"
        if (loading)
        {
            // Desenha a imagem kelry.png sem escala modificada
            DrawTexture(kelryImage, SCREEN_WIDTH / 2 - kelryImage.width / 2, SCREEN_HEIGHT / 2 - kelryImage.height / 2 - 50, WHITE);

            // Desenha o texto "Carregando..."
            DrawTextEx(customFont, "Carregando...", (Vector2){SCREEN_WIDTH / 2 - MeasureTextEx(customFont, "Carregando...", 30, 2).x / 2, SCREEN_HEIGHT / 2 + 120}, 30, 2, textColor);
        }

        EndDrawing();
    }

    // Fecha a janela e limpa recursos
    UnloadFont(customFont); // Descarrega a fonte
    UnloadTexture(background); // Descarrega a textura
    UnloadTexture(kelryImage); // Descarrega a imagem kelry.png
    CloseWindow();

    return 0;
}

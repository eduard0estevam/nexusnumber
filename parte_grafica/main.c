#include "raylib.h"

#define SCREEN_WIDTH 1001
#define SCREEN_HEIGHT 559

int main(void)
{
    // Inicializa a janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NexusNumber");

    // Carrega a fonte customizada
    Font customFont = LoadFont("Daydream.ttf");

    // Carrega a imagem de fundo
    Texture2D background = LoadTexture("backgroun2.png");

    // Define as cores
    Color textColor = WHITE;
    Color enterButtonColor = WHITE;
    Color enterButtonTextColor = DARKPURPLE;
    Color exitButtonColor = WHITE;
    Color exitButtonTextColor = PINK;

    // Define as variáveis para os botões
    Rectangle enterButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50 };
    Rectangle exitButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 50 };

    // Variável para controle do loop principal
    bool exitGame = false;

    while (!WindowShouldClose() && !exitGame) // Loop principal do jogo
    {
        // Verifica se o botão "Entrar" foi clicado
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, enterButton))
            {
                // Lógica para entrar no jogo
                // Aqui você pode adicionar a lógica para iniciar o jogo
                TraceLog(LOG_INFO, "Entrar no jogo");
            }
            if (CheckCollisionPointRec(mousePoint, exitButton))
            {
                // Lógica para sair do jogo
                exitGame = true;
            }
        }

        // Desenho da tela
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha a imagem de fundo
        DrawTexture(background, 0, 0, WHITE);

        // Desenha o título do jogo
        DrawTextEx(customFont, "NexusNumber", (Vector2){SCREEN_WIDTH / 2 - MeasureTextEx(customFont, "NexusNumber", 40, 2).x / 2, SCREEN_HEIGHT / 4}, 40, 2, textColor);

        // Desenha os botões
        DrawRectangleRec(enterButton, enterButtonColor);
        DrawRectangleRec(exitButton, exitButtonColor);

        DrawTextEx(customFont, "Entrar", (Vector2){enterButton.x + enterButton.width / 2 - MeasureTextEx(customFont, "Entrar", 20, 2).x / 2, enterButton.y + 15}, 20, 2, enterButtonTextColor);
        DrawTextEx(customFont, "Sair", (Vector2){exitButton.x + exitButton.width / 2 - MeasureTextEx(customFont, "Sair", 20, 2).x / 2, exitButton.y + 15}, 20, 2, exitButtonTextColor);

        EndDrawing();
    }

    // Fecha a janela e limpa recursos
    UnloadFont(customFont); // Descarrega a fonte
    UnloadTexture(background); // Descarrega a textura
    CloseWindow();

    return 0;
}

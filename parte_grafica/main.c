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
    DrawTextEx(customFont, "Sair", (Vector2){exitButton.x + 50, enterButton.y + 10}, 30, 2, exitButtonTextColor);
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

    // Desenhar seta de voltar
    DrawTextEx(customFont, "< Voltar", (Vector2){10, 10}, 20, 2, titleColor);
}

void MostrarPergunta(Font customFont, Font chalkboyFont, Texture2D background, Questao questoes[], int perguntaAtual, char respostaUsuario[], Color textColor, Color titleColor) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);

    // Desenhar seta de voltar e botão de reiniciar
    DrawTextEx(customFont, "< Voltar", (Vector2){10, 10}, 20, 2, titleColor);
    DrawTextEx(customFont, "Reiniciar", (Vector2){SCREEN_WIDTH - 100, 10}, 20, 2, titleColor);

    // Dividir a pergunta em múltiplas linhas
    char pergunta[256];
    strcpy(pergunta, questoes[perguntaAtual].pergunta);
    char *linha = strtok(pergunta, "\n");
    int y = 150;
    while (linha != NULL) {
        DrawTextEx(chalkboyFont, linha, (Vector2){50, y}, 27, 2, textColor);
        y += 30; // Ajustar o espaçamento entre linhas conforme necessário
        linha = strtok(NULL, "\n");
    }

    DrawTextEx(chalkboyFont, "Sua resposta:", (Vector2){350, 300}, 27, 2, textColor);
    DrawTextEx(chalkboyFont, respostaUsuario, (Vector2){350, 340}, 27, 2, textColor);

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

void MenuPausa(Font customFont, Texture2D pauseImage, Color titleColor) {
    ClearBackground(BLACK);
    DrawTexture(pauseImage, (SCREEN_WIDTH - pauseImage.width) / 2, (SCREEN_HEIGHT - pauseImage.height) / 2, WHITE);
    DrawTextEx(customFont, "Jogo Pausado", (Vector2){SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20}, 40, 2, titleColor);
    DrawTextEx(customFont, "Pressione P para continuar", (Vector2){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 20}, 20, 2, titleColor);
}

void TelaGameOver(Font customFont, Texture2D gameOverImage, Color titleColor) {
    ClearBackground(BLACK);
    DrawTexture(gameOverImage, (SCREEN_WIDTH - gameOverImage.width) / 2, (SCREEN_HEIGHT - gameOverImage.height) / 2, WHITE);
    DrawTextEx(customFont, "GameOver! Tente novamente...", (Vector2){SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20}, 40, 2, titleColor);
    DrawTextEx(customFont, "Clique na tela para reiniciar.", (Vector2){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 20}, 20, 2, titleColor);
}

int main(void) {
    // Inicializa a janela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NexusNumber");

    InitAudioDevice();

    // Carrega a fonte customizada
    Font customFont = LoadFont("04B_30__.TTF");
    Font chalkboyFont = LoadFontEx("Neat Chalk.ttf", 30, NULL, 0); // Fonte para o nível fácil, médio e difícil

    // Carrega as imagens de fundo e a imagem de carregamento
    Texture2D background = LoadTexture("./imagens/menu.png");
    Texture2D easyBackground = LoadTexture("./imagens/facil.png");
    Texture2D loadingImage = LoadTexture("./imagens/carregamento.png"); // Nova textura de carregamento
    Texture2D mediumBackground = LoadTexture("./imagens/medio.png");
    Texture2D hardBackground = LoadTexture("./imagens/hard11.png");
    Texture2D pauseImage = LoadTexture("./imagens/pause.png"); // Imagem de pausa
    Texture2D gameOverImage = LoadTexture("./imagens/gameover.png"); // Imagem de game over
    Music music = LoadMusicStream("./audio/musica.ogg");
    SetMusicVolume(music, 0.5f); // Define o volume da música
    PlayMusicStream(music); // Inicia a reprodução da música
    Sound clickSound = LoadSound("./audio/click.wav"); // Substitua o caminho com o local correto do seu arquivo de áudio
    SetSoundVolume(clickSound, 0.5f); // Ajuste o volume do efeito sonoro conforme necessário

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
    bool paused = false; // Variável para controle de pausa
    bool gameOver = false; // Variável para controle de game over
    int selectedLevel = 0;
    float loadingTimer = 0;

    // Variáveis para o jogo
    int vidas = 3;
    int pontos = 0;
    Questao questoesFaceis[10] = { 
        {"1- 2, 6, 12, 20, 30, ? Qual eh o proximo numero\nna sequencia?", "42"},
        {"2- A soma das idades de Ana e Bia eh 44. Ana eh\n 8 anos mais velha que Bia. Qual\n eh a idade de Ana?", "26"},
        {"3- 13, 18 = 31\n7, 25 = 32\n12, 30 = 42\n26, 13 = ?", "39"},
        {"4- Qual eh o proximo numero\n na sequencia: 1, 4, 9, 16, 25, ...?\n", "36"},
        {"5- Joao tem o dobro da idade de Pedro.\n Se a diferenca de suas\n idades eh de 15 anos, quantos\n anos Joao tem?", "30"},
        {"6- 4, 8 e 16: Qual eh o proximo numero?", "32"},
        {"7- A + B = 60\nA - B = 40\n A / B = ?", "5"},
        {"8- Em um quadrado formado por 16 palitos\ncom quantos palitos eu posso\n fazer 2 quadrados ?", "4"},
        {"9- A media aritmetica de cinco numeros eh 12.\n Se somarmos 3 a cada um desses numeros, qual\n sera a nova media?", "15"},
        {"10- Qual o valor de x na equacao: 3x + 2 = 17?", "5"}
    };

    Questao questoesMedias[5] = {
        {"1- Em um saco ha 5 bolas vermelhas, 4 bolas azuis e 3 bolas verdes. Qual a\nprobabilidade de se retirar uma bola azul?", "1/3"},
        {"2- Se o dobro de um numero eh 24, qual eh a metade desse numero?", "12"},
        {"3- Se 5 maquinas podem completar um trabalho em 8 horas, quantas horas levarao 8\nmaquinas para completar o mesmo trabalho?", "5"},
        {"4- Um produto custa R$ 120,00. Apos um desconto de 25%, qual eh o novo preco?", "90"},
        {"5- Qual eh a soma de 1/3 e 1/4?", "7/12"}
    };

    Questao questoesDificeis[10] = {
        {"1- 9, 16 = 7\n4, 36 = 8\n121, 81 = 20\n25, 49 = ?", "12"},
        {"2- Em um sistema de codificação, AB eh o dia do\nnascimento de uma pessoa e CD eh seu mês de nascimento.\nQual eh o mes de nascimento dessa pessoa se a data for trinta de julho?", "07"},
        {"3- Se 3 gatos caçam 3 ratos em 3 minutos, em quantos minutos levarão 100\ngatos para caçar 100 ratos?", "3"},
        {"4- Um carro viaja a 60 km/h. Em quantas horas levará para percorrer 180 km?", "3"},
        {"5- Se a=1, b=2, c=3, ..., z=26, qual eh a soma das letras da palavra CAT?", "24"},
        {"6- Se uma torneira enche um tanque em 2 horas e outra torneira enche o\nmesmo tanque em 3 horas, quanto tempo levarão as duas torneiras juntas\npara encher o tanque?", "1.2"},
        {"7- Se um trem viaja a uma velocidade constante de 90 km/h e percorre uma\ndistância de 270 km, quanto tempo o trem levará para completar a\nviagem?", "3"},
        {"8- Qual é a raiz quadrada de 144?", "12"},
        {"9- Em um grupo de 15 pessoas, 9 gostam de chocolate e 7 gostam de\nbaunilha. Se 4 pessoas gostam de ambos, quantas pessoas não gostam de\nnenhum dos sabores?", "3"},
        {"10- Se a média aritmética de três números é 15 e dois desses números são 10\ne 20, qual é o terceiro número?", "15"}
    };

    // Embaralha as perguntas
    srand(time(NULL));
    embaralhar(questoesFaceis, 10);
    embaralhar(questoesMedias, 5);
    embaralhar(questoesDificeis, 10);

    int perguntaAtual = 0;
    char respostaUsuario[256] = "";

    // Loop principal do jogo
    while (!exitGame && !WindowShouldClose()) {
        
        UpdateMusicStream(music);

        BeginDrawing();
       
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_P)) {
            paused = !paused;
        }

        if (paused) {
            MenuPausa(customFont, pauseImage, titleColor);
        } else if (gameOver) {
            TelaGameOver(customFont, gameOverImage, titleColor);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // Reinicia o jogo
                gameStarted = false;
                showingLevelButtons = false;
                loading = false;
                loadingComplete = false;
                paused = false;
                gameOver = false;
                vidas = 3;
                pontos = 0;
                perguntaAtual = 0;
                respostaUsuario[0] = '\0';
            }
        } else {
            if (!gameStarted) { //MENU PRINCIPAL
                MenuPrincipal(customFont, background, enterButton, exitButton, enterButtonColor, enterButtonTextColor, exitButtonColor, exitButtonTextColor, titleColor);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, enterButton)) {
                        gameStarted = true;
                        showingLevelButtons = true;
                        PlaySound(clickSound); // Reproduz o efeito sonoro de clique
                    } else if (CheckCollisionPointRec(mousePoint, exitButton)) {
                        exitGame = true;
                    }
                }
            } else if (showingLevelButtons) { //MENU DOS NIVEIS
                MostrarNiveis(customFont, background, easyButton, mediumButton, hardButton, levelButtonColor, levelButtonTextColor, titleColor);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, easyButton)) {
                        selectedLevel = 1;
                        loading = true;
                        showingLevelButtons = false;
                        PlaySound(clickSound);
                    } else if (CheckCollisionPointRec(mousePoint, mediumButton)) {
                        selectedLevel = 2;
                        loading = true;
                        showingLevelButtons = false;
                        PlaySound(clickSound);
                    } else if (CheckCollisionPointRec(mousePoint, hardButton)) {
                        selectedLevel = 3;
                        loading = true;
                        showingLevelButtons = false;
                        PlaySound(clickSound);
                    } else if (mousePoint.x >= 10 && mousePoint.x <= 110 && mousePoint.y >= 10 && mousePoint.y <= 30) {
                        // Volta para o menu principal
                        gameStarted = false;
                        showingLevelButtons = false;
                    }
                }
            } else if (loading) {
                Carregando(customFont, loadingImage, titleColor);
                loadingTimer += GetFrameTime();
                if (loadingTimer >= 3.0f) { // Simula um carregamento de 3 segundos
                    loadingComplete = true;
                    loading = false;
                    loadingTimer = 0;
                }
            } else if (loadingComplete) {
                if (selectedLevel == 1) {
                    MostrarPergunta(customFont, chalkboyFont, easyBackground, questoesFaceis, perguntaAtual, respostaUsuario, textColor, titleColor);
                } else if (selectedLevel == 2) {
                    MostrarPergunta(customFont, chalkboyFont, mediumBackground, questoesMedias, perguntaAtual, respostaUsuario, textColor, titleColor);
                } else if (selectedLevel == 3) {
                    MostrarPergunta(customFont, chalkboyFont, hardBackground, questoesDificeis, perguntaAtual, respostaUsuario, textColor, titleColor);
                }

                // Verifica clique na seta de voltar
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (mousePoint.x >= 10 && mousePoint.x <= 110 && mousePoint.y >= 10 && mousePoint.y <= 30) {
                        // Volta para o menu de níveis
                        showingLevelButtons = true;
                        loadingComplete = false;
                        respostaUsuario[0] = '\0';
                    }

                    // Verifica clique no botão de reiniciar
                    if (mousePoint.x >= SCREEN_WIDTH - 100 && mousePoint.x <= SCREEN_WIDTH - 20 && mousePoint.y >= 10 && mousePoint.y <= 30) {
                        // Reinicia o nível atual
                        vidas = 3;
                        perguntaAtual = 0;
                        respostaUsuario[0] = '\0';
                    }
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    if ((selectedLevel == 1 && strcmp(respostaUsuario, questoesFaceis[perguntaAtual].resposta) == 0) ||
                        (selectedLevel == 2 && strcmp(respostaUsuario, questoesMedias[perguntaAtual].resposta) == 0) ||
                        (selectedLevel == 3 && strcmp(respostaUsuario, questoesDificeis[perguntaAtual].resposta) == 0)) {
                        pontos += 10;
                    } else {
                        vidas -= 1;
                    }
                    perguntaAtual++;
                    respostaUsuario[0] = '\0'; // Limpa a resposta do usuário
                    if (perguntaAtual >= 10 || vidas <= 0) {
                        if (vidas <= 0) {
                            gameOver = true;
                        } else {
                            gameStarted = false;
                        }
                    }
                }
            }
        }

        EndDrawing();
    }

    // Descarrega os recursos
    UnloadFont(customFont);
    UnloadTexture(background);
    UnloadTexture(easyBackground);
    UnloadTexture(loadingImage); // Nova textura de carregamento
    UnloadTexture(mediumBackground);
    UnloadTexture(hardBackground);
    UnloadTexture(pauseImage); // Nova textura de pausa
    UnloadTexture(gameOverImage); // Nova textura de game over
    UnloadMusicStream(music);
    UnloadSound(clickSound);

    CloseWindow();

    return 0;
}

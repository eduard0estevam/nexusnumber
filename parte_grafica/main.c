#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"

// Variáveis globais
int vidas = 3;
int pontos = 0;
float tempoJogo = 0.0f;
bool vitoria = false;
bool erro = false;  // Variável para controlar a exibição da mensagem de erro
float tempoErro = 0.0f;  // Variável para controlar o tempo de exibição da mensagem de erro
bool rascunhoAtivo = false;  // Variável para controlar a tela de rascunho
bool rascunhoMovendo = false; // Variável para controlar se a tela de rascunho está sendo movida
Vector2 rascunhoPos = {100, 100}; // Posição inicial da tela de rascunho
Vector2 mouseOffset = {0, 0}; // Offset do mouse ao arrastar

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
    DrawTextEx(customFont, "Entrar", (Vector2){enterButton.x + 28, enterButton.y + 10}, 30, 2, enterButtonTextColor);
    DrawRectangleRec(exitButton, exitButtonColor);
    DrawTextEx(customFont, "Sair", (Vector2){exitButton.x + 50, enterButton.y + 80}, 30, 2, exitButtonTextColor);
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
    DrawTextEx(customFont, "< Voltar", (Vector2){10, 10}, 22, 2, titleColor);
}

void MostrarPergunta(Font customFont, Font chalkboyFont, Texture2D background, Questao questoes[], int perguntaAtual, char respostaUsuario[], int pontos, int vidas, Color textColor, Color titleColor, Rectangle rascunhoButton, Color buttonColor, Color buttonTextColor) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);

    // Desenhar seta de voltar e botão de reiniciar
    DrawTextEx(customFont, "< Voltar", (Vector2){10, 10}, 22, 2, textColor);
    DrawTextEx(customFont, "Reiniciar", (Vector2){SCREEN_WIDTH - 180, 10}, 22, 2, textColor);

    // Desenhar botão de rascunho
    DrawRectangleRec(rascunhoButton, buttonColor);
    DrawTextEx(customFont, "Rascunho", (Vector2){rascunhoButton.x + 10, rascunhoButton.y + 10}, 22, 2, buttonTextColor);

    // Dividir a pergunta em múltiplas linhas
    char pergunta[256];
    strcpy(pergunta, questoes[perguntaAtual].pergunta);
    char *linha = strtok(pergunta, "\n");
    int y = 150;
    while (linha != NULL) {
        DrawTextEx(chalkboyFont, linha, (Vector2){125, y}, 27, 2, textColor);
        y += 30; // Ajustar o espaçamento entre linhas conforme necessário
        linha = strtok(NULL, "\n");
    }

    DrawTextEx(chalkboyFont, "Sua resposta:", (Vector2){380, 280}, 27, 2, textColor);
    DrawTextEx(chalkboyFont, respostaUsuario, (Vector2){600, 280}, 27, 2, textColor);

    // Mostrar pontuação e vidas
    char strPontos[20], strVidas[20];
    sprintf(strPontos, "Pontos: %d", pontos);
    sprintf(strVidas, "Vidas: %d", vidas);
    DrawTextEx(chalkboyFont, strPontos, (Vector2){380, SCREEN_HEIGHT - 310}, 22, 2, textColor);
    DrawTextEx(chalkboyFont, strVidas, (Vector2){380, SCREEN_HEIGHT - 270}, 22, 2, textColor);

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
    DrawTextEx(customFont, "GameOver!", (Vector2){SCREEN_WIDTH / 2 - 380, SCREEN_HEIGHT / 2 - 200}, 52, 2, titleColor);
    DrawTextEx(customFont, "Clique na tela para reiniciar.", (Vector2){SCREEN_WIDTH / 2 - 390, SCREEN_HEIGHT / 2 - 120}, 20, 2, titleColor);
}

void TelaVitoria(Font customFont, Texture2D vitoriaImage, int pontos, float tempoJogo, Color titleColor) {
    ClearBackground(BLACK);
    DrawTexture(vitoriaImage, (SCREEN_WIDTH - vitoriaImage.width) / 2, (SCREEN_HEIGHT - vitoriaImage.height) / 2, WHITE);
    DrawTextEx(customFont, "Parabens! Você venceu!", (Vector2){SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100}, 40, 2, titleColor);

    char strPontos[50], strTempo[50];
    sprintf(strPontos, "Pontuacao final: %d", pontos);
    sprintf(strTempo, "Tempo de jogo: %.2f segundos", tempoJogo);
    DrawTextEx(customFont, strPontos, (Vector2){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 20}, 30, 2, titleColor);
    DrawTextEx(customFont, strTempo, (Vector2){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 60}, 30, 2, titleColor);
}

void MostrarMensagemErro(Font customFont, Questao questoes[], int perguntaAtual, int selectedLevel, Color textColor) {
    DrawTextEx(customFont, "Errado! A resposta era:", (Vector2){440, 310}, 23, 2, RED);
    DrawTextEx(customFont, questoes[perguntaAtual].resposta, (Vector2){640, 350}, 27, 2, RED);
}

void TelaRascunho(Font customFont, Color titleColor, Texture2D folhaCaderno) {
    DrawTexture(folhaCaderno, rascunhoPos.x, rascunhoPos.y, WHITE);
    DrawTextEx(customFont, "Rascunho", (Vector2){rascunhoPos.x + 10, rascunhoPos.y + 10}, 40, 2, titleColor);
    DrawTextEx(customFont, "Clique com o mouse para desenhar", (Vector2){rascunhoPos.x + 10, rascunhoPos.y + 60}, 20, 2, titleColor);
    DrawTextEx(customFont, "Pressione V para voltar", (Vector2){rascunhoPos.x + 10, rascunhoPos.y + 90}, 20, 2, titleColor);

    // Desenhar com o mouse
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, (Rectangle){rascunhoPos.x, rascunhoPos.y, 444, 385})) {
            DrawCircleV(mousePos, 5, BLACK);
        }
    }

    // Movendo a tela de rascunho
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), (Rectangle){rascunhoPos.x, rascunhoPos.y, 444, 30})) {
        rascunhoMovendo = true;
        mouseOffset = (Vector2){GetMousePosition().x - rascunhoPos.x, GetMousePosition().y - rascunhoPos.y};
    }

    if (rascunhoMovendo) {
        rascunhoPos = (Vector2){GetMousePosition().x - mouseOffset.x, GetMousePosition().y - mouseOffset.y};
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            rascunhoMovendo = false;
        }
    }
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
    Texture2D hardBackground = LoadTexture("./imagens/hardi.png");
    Texture2D pauseImage = LoadTexture("./imagens/pause.png"); // Imagem de pausa
    Texture2D gameOverImage = LoadTexture("./imagens/gameover.png"); // Imagem de game over
    Texture2D vitoriaImage = LoadTexture("./imagens/vitoria.png"); // Imagem de vitória
    Texture2D folhaCaderno = LoadTexture("./imagens/folha_caderno.png"); // Imagem da folha de caderno
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
    Rectangle rascunhoButton = { SCREEN_WIDTH - 150, 50, 120, 40 };

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

    Questao questoesFaceis[10] = { 
        {"1- 2, 6, 12, 20, 30, ? Qual eh o proximo numero\nna sequencia?", "42"},
        {"2- A soma das idades de Ana e Bia eh 44. Ana eh\n 8 anos mais velha que Bia. Qual\n eh a idade de Ana?", "26"},
        {"3- 13, 18 = 31 | 7, 25 = 32 | 12, 30 = 42 | 26, 13 = ?", "39"},
        {"4- Qual eh o proximo numero\n na sequencia: 1, 4, 9, 16, 25, ...?\n", "36"},
        {"5- Joao tem o dobro da idade de Pedro. Se\n a diferenca de suas idades eh de 15 anos, quantos\n anos Joao tem?", "30"},
        {"6- 4, 8 e 16: Qual eh o proximo numero?", "32"},
        {"7- A + B = 60 | A - B = 40 | A / B = ?", "5"},
        {"8- Em um quadrado formado por 16 palitos\ncom quantos palitos eu posso\n fazer 2 quadrados ?", "4"},
        {"9- A media aritmetica de cinco numeros eh 12.\n Se somarmos 3 a cada um desses numeros, qual\n sera a nova media?", "15"},
        {"10- Qual o valor de x na equacao: 3x + 2 = 17?", "5"}
    };

    Questao questoesMedias[5] = {
        {"1- Em um saco ha 5 bolas vermelhas, 4 bolas azuis\n e 3 bolas verdes. Qual a probabilidade de se\n retirar uma bola azul?", "1/3"},
        {"2- Se o dobro de um numero eh 24, qual eh a metade\n desse numero?", "12"},
        {"3- Se 5 maquinas podem completar um trabalho em\n 8 horas, quantas horas levarao 8\nmaquinas para completar o mesmo trabalho?", "5"},
        {"4- Um produto custa R$ 120,00.\n Apos um desconto de 25%, qual eh o novo preco?", "90"},
        {"5- Qual eh a soma de 1/3 e 1/4?", "7/12"}
    };

    Questao questoesDificeis[5] = {
        {"1- 9, 16 = 7 | 4, 36 = 8 | 121, 81 = 20 |25, 49 = ?", "12"},
        {"2- Em um sistema de codificacao, AB eh o dia do\n nascimento de uma pessoa e CD eh seu mes\n de nascimento.Qual eh o mes de nascimento dessa pessoa se a\n data for trinta de julho?", "07"},
        {"3- Se 3 gatos caca, 3 ratos em 3 minutos, em\n quantos minutos levarão 100 gatos para cacar\n 100 ratos?", "3"},
        {"4- Um carro viaja a 60 km/h. Em quantas horas\n levara para percorrer 180 km?", "3"},
        {"5- Se a=1, b=2, c=3, ..., z=26, qual eh a soma\n das letras da palavra CAT?", "24"},
    };

    // Embaralha as perguntas
    srand(time(NULL));
    embaralhar(questoesFaceis, 10);
    embaralhar(questoesMedias, 5);
    embaralhar(questoesDificeis, 5);

    int perguntaAtual = 0;
    char respostaUsuario[256] = "";

    // Loop principal do jogo
    while (!exitGame && !WindowShouldClose()) {
        
        UpdateMusicStream(music);
        tempoJogo += GetFrameTime();

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
                tempoJogo = 0.0f;
            }
        } else if (vitoria) {
            TelaVitoria(customFont, vitoriaImage, pontos, tempoJogo, titleColor);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // Reinicia o jogo
                gameStarted = false;
                showingLevelButtons = false;
                loading = false;
                loadingComplete = false;
                paused = false;
                vitoria = false;
                vidas = 3;
                pontos = 0;
                perguntaAtual = 0;
                respostaUsuario[0] = '\0';
                tempoJogo = 0.0f;
            }
        } else {
            if (!gameStarted) { //MENU PRINCIPAL (aqui é verificado o clique dos botoes)
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
                        PlaySound(clickSound);
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
                    MostrarPergunta(customFont, chalkboyFont, easyBackground, questoesFaceis, perguntaAtual, respostaUsuario, pontos, vidas, textColor, titleColor, rascunhoButton, enterButtonColor, enterButtonTextColor);
                } else if (selectedLevel == 2) {
                    MostrarPergunta(customFont, chalkboyFont, mediumBackground, questoesMedias, perguntaAtual, respostaUsuario, pontos, vidas, textColor, titleColor, rascunhoButton, enterButtonColor, enterButtonTextColor);
                } else if (selectedLevel == 3) {
                    MostrarPergunta(customFont, chalkboyFont, hardBackground, questoesDificeis, perguntaAtual, respostaUsuario, pontos, vidas, textColor, titleColor, rascunhoButton, enterButtonColor, enterButtonTextColor);
                }

                // Verifica clique na seta de voltar
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (mousePoint.x >= 10 && mousePoint.x <= 110 && mousePoint.y >= 10 && mousePoint.y <= 30) {
                        // Volta para o menu de níveis
                        showingLevelButtons = true;
                        loadingComplete = false;
                        respostaUsuario[0] = '\0';
                        PlaySound(clickSound);  // Reproduz o som de clique
                    }

                    // Verifica clique no botão de reiniciar
                    if (mousePoint.x >= SCREEN_WIDTH - 150 && mousePoint.x <= SCREEN_WIDTH - 50 && mousePoint.y >= 10 && mousePoint.y <= 30) {
                        // Reinicia o nível atual
                        vidas = 3;
                        perguntaAtual = 0;
                        respostaUsuario[0] = '\0';
                        if (selectedLevel == 1) {
                            embaralhar(questoesFaceis, 10);
                        } else if (selectedLevel == 2) {
                            embaralhar(questoesMedias, 5);
                        } else if (selectedLevel == 3) {
                            embaralhar(questoesDificeis, 5);
                        }
                        PlaySound(clickSound);  // Reproduz o som de clique
                    }

                    // Verifica clique no botão de rascunho
                    if (CheckCollisionPointRec(mousePoint, rascunhoButton)) {
                        rascunhoAtivo = true;
                        PlaySound(clickSound);  // Reproduz o som de clique
                    }
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    if ((selectedLevel == 1 && strcmp(respostaUsuario, questoesFaceis[perguntaAtual].resposta) == 0) ||
                        (selectedLevel == 2 && strcmp(respostaUsuario, questoesMedias[perguntaAtual].resposta) == 0) ||
                        (selectedLevel == 3 && strcmp(respostaUsuario, questoesDificeis[perguntaAtual].resposta) == 0)) {
                        pontos += 10;
                        erro = false;
                    } else {
                        vidas -= 1;
                        erro = true;
                        tempoErro = 0.0f;
                    }
                    perguntaAtual++;
                    respostaUsuario[0] = '\0'; // Limpa a resposta do usuário
                    if (perguntaAtual >= 10 || vidas <= 0) {
                        if (vidas <= 0) {
                            gameOver = true;
                        } else {
                            vitoria = true;
                        }
                    }
                }

                if (erro) {
                    tempoErro += GetFrameTime();
                    MostrarMensagemErro(customFont, questoesFaceis, perguntaAtual - 1, selectedLevel, RED);
                    if (tempoErro >= 3.0f) {
                        erro = false;
                    }
                }
            }

            // Verifica se o rascunho está ativo
            if (rascunhoAtivo) {
                TelaRascunho(customFont, titleColor, folhaCaderno);
                if (IsKeyPressed(KEY_V)) {
                    rascunhoAtivo = false;
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
    UnloadTexture(vitoriaImage); // Nova textura de vitória
    UnloadTexture(folhaCaderno); // Nova textura de folha de caderno
    UnloadMusicStream(music);
    UnloadSound(clickSound);

    CloseWindow();

    return 0;
}

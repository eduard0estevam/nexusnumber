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
bool erro = false;
float tempoErro = 0.0f;
bool rascunhoAtivo = false;
bool rascunhoMovendo = false;
bool aceitandoResposta = true;
bool tempoParado = false;
bool mostrandoRanking = false;
bool entrandoNome = false;
bool loading = false;
bool loadingComplete = false;
bool paused = false;
bool gameOver = false;
bool showingLevelButtons = false; // Variável global adicionada
bool musicaVitoriaTocando = false; // Variável para controlar a música de vitória
bool respostaCerta = false; // Variável para controlar a mensagem de resposta certa
char nomeJogador[256] = "";
Vector2 rascunhoPos = {100, 100};
Vector2 mouseOffset = {0, 0};
RenderTexture2D rascunhoTarget;

// Variáveis para animação de carregamento
float loadingTimer = 0.0f;
int loadingDots = 0;

void LimparRascunho();

// Estrutura para armazenar perguntas e respostas
typedef struct {
    char pergunta[256];
    char resposta[256];
} Questao;

typedef struct {
    char nome[256];
    int pontuacao;
} Jogador;

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

void MenuPrincipal(Font customFont, Texture2D background, Rectangle enterButton, Rectangle exitButton, Rectangle rankingButton, Color enterButtonColor, Color enterButtonTextColor, Color exitButtonColor, Color exitButtonTextColor, Color rankingButtonColor, Color rankingButtonTextColor, Color titleColor) {
    DrawTexture(background, 0, 0, WHITE);
    DrawTextEx(customFont, "NexusNumber", (Vector2){SCREEN_WIDTH / 2 - 230, 170}, 50, 2, titleColor);
    DrawRectangleRec(enterButton, enterButtonColor);
    DrawTextEx(customFont, "Entrar", (Vector2){enterButton.x + 28, enterButton.y + 10}, 30, 2, enterButtonTextColor);
    DrawRectangleRec(exitButton, exitButtonColor);
    DrawTextEx(customFont, "Sair", (Vector2){exitButton.x + 50, exitButton.y + 10}, 30, 2, exitButtonTextColor);
    DrawRectangleRec(rankingButton, rankingButtonColor);
    DrawTextEx(customFont, "Ranking", (Vector2){rankingButton.x + 15, rankingButton.y + 10}, 30, 2, rankingButtonTextColor);
}

void Carregando(Font customFont, Texture2D loadingImage, Color titleColor) {
    ClearBackground(BLACK);
    DrawTexture(loadingImage, (SCREEN_WIDTH - loadingImage.width) / 2, (SCREEN_HEIGHT - loadingImage.height) / 2, WHITE);
    
    // Atualizar pontos de carregamento
    if (loadingTimer >= 0.5f) {
        loadingDots = (loadingDots + 1) % 4; // Atualiza entre 0 e 3 pontos
        loadingTimer = 0.0f;
    }
    loadingTimer += GetFrameTime();

    // Construir string de carregamento com pontos
    char loadingText[20];
    snprintf(loadingText, sizeof(loadingText), "Carregando%s", (loadingDots == 1 ? "." : (loadingDots == 2 ? ".." : (loadingDots == 3 ? "..." : ""))));
    
    DrawTextEx(customFont, loadingText, (Vector2){SCREEN_WIDTH / 2 - 155, SCREEN_HEIGHT / 2 + 200}, 40, 2, titleColor);
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

    DrawTextEx(customFont, "< Voltar", (Vector2){10, 10}, 22, 2, titleColor);
}

void EntradaNomeJogador(Font customFont, Color titleColor, Texture2D background, Sound clickSound) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTextEx(customFont, "Digite seu nome:", (Vector2){SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 90}, 30, 2, PINK);
    DrawRectangle(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 45, 400, 40, WHITE);
    DrawTextEx(customFont, nomeJogador, (Vector2){SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 40}, 30, 2, PINK);

    // Adiciona botão "Voltar"
    DrawTextEx(customFont, "< Voltar", (Vector2){10, 10}, 22, 2, titleColor);

    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 125 && strlen(nomeJogador) < 255) {
            int len = strlen(nomeJogador);
            nomeJogador[len] = (char)key;
            nomeJogador[len + 1] = '\0';
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && strlen(nomeJogador) > 0) {
        nomeJogador[strlen(nomeJogador) - 1] = '\0';
    }
    if (IsKeyPressed(KEY_ENTER) && strlen(nomeJogador) > 0) {
        entrandoNome = false;
        loading = true;
    }

    // Verifica se o botão "Voltar" foi pressionado
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePoint = GetMousePosition();
        if (mousePoint.x >= 10 && mousePoint.x <= 110 && mousePoint.y >= 10 && mousePoint.y <= 30) {
            entrandoNome = false;
            showingLevelButtons = true;
            PlaySound(clickSound);
        }
    }
}

void MostrarRanking(Font customFont, Color titleColor, Texture2D background) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);
    DrawTextEx(customFont, "Ranking", (Vector2){SCREEN_WIDTH / 2 - 90, 40}, 40, 2, titleColor);

    FILE *file = fopen("pontuacoes.txt", "r");
    if (file == NULL) {
        DrawTextEx(customFont, "Nenhum ranking disponível.", (Vector2){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2}, 30, 2, titleColor);
        return;
    }

    char linha[256];
    int y = 100;
    while (fgets(linha, sizeof(linha), file)) {
        DrawTextEx(customFont, linha, (Vector2){50, y}, 20, 2, titleColor);
        y += 30;
    }
    fclose(file);

    DrawTextEx(customFont, "Pressione ENTER para voltar", (Vector2){SCREEN_WIDTH / 2 - 215, SCREEN_HEIGHT - 60}, 20, 2, titleColor);
    if (IsKeyPressed(KEY_ENTER)) {
        mostrandoRanking = false;
    }
}

void SalvarPontuacao(char *nome, int pontuacao) {
    FILE *file = fopen("pontuacoes.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s - %d\n", nome, pontuacao);
        fclose(file);
    }
}

void MostrarPergunta(Font customFont, Font chalkboyFont, Texture2D background, Questao questoes[], int perguntaAtual, char respostaUsuario[], int pontos, int vidas, Color textColor, Color titleColor, Rectangle rascunhoButton, Color buttonColor, Color buttonTextColor) {
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);

    DrawTextEx(customFont, "< Voltar", (Vector2){10, 10}, 22, 2, textColor);
    DrawTextEx(customFont, "Reiniciar", (Vector2){SCREEN_WIDTH - 180, 10}, 22, 2, textColor);

    DrawRectangleRec(rascunhoButton, buttonColor);
    DrawTextEx(customFont, "Rascunho", (Vector2){rascunhoButton.x + 5, rascunhoButton.y + 10}, 22, 2, buttonTextColor);

    char pergunta[256];
    strcpy(pergunta, questoes[perguntaAtual].pergunta);
    char *linha = strtok(pergunta, "\n");
    int y = 150;
    while (linha != NULL) {
        DrawTextEx(chalkboyFont, linha, (Vector2){125, y}, 27, 2, textColor);
        y += 30;
        linha = strtok(NULL, "\n");
    }

    if (respostaCerta) {
        DrawTextEx(chalkboyFont, "Resposta certa!", (Vector2){380, 270}, 27, 2, GREEN);
    }

    DrawTextEx(chalkboyFont, "Sua resposta:", (Vector2){380, 300}, 27, 2, textColor);
    DrawTextEx(chalkboyFont, respostaUsuario, (Vector2){600, 300}, 27, 2, textColor);

    char strPontos[20], strVidas[20];
    sprintf(strPontos, "Pontos: %d", pontos);
    sprintf(strVidas, "Vidas: %d", vidas);
    DrawTextEx(chalkboyFont, strPontos, (Vector2){380, SCREEN_HEIGHT - 306}, 22, 2, textColor);
    DrawTextEx(chalkboyFont, strVidas, (Vector2){380, SCREEN_HEIGHT - 270}, 22, 2, textColor);

    if (aceitandoResposta) {
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
}

void MenuPausa(Font customFont, Texture2D pauseImage, Color titleColor) {
    ClearBackground(BLACK);
    DrawTexture(pauseImage, (SCREEN_WIDTH - pauseImage.width) / 2, (SCREEN_HEIGHT - pauseImage.height) / 2, WHITE);
    DrawTextEx(customFont, "Jogo Pausado", (Vector2){SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 20}, 40, 2, titleColor);
    DrawTextEx(customFont, "Pressione P para continuar", (Vector2){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 20}, 20, 2, titleColor);
}

void TelaGameOver(Font customFont, Texture2D gameOverImage, int pontos, float tempoJogo, Color titleColor) {
    ClearBackground(BLACK);
    DrawTexture(gameOverImage, (SCREEN_WIDTH - gameOverImage.width) / 2, (SCREEN_HEIGHT - gameOverImage.height) / 2, WHITE);
    DrawTextEx(customFont, "GameOver!", (Vector2){SCREEN_WIDTH / 2 - 378, SCREEN_HEIGHT / 2 - 140}, 60, 2, PINK);
    DrawTextEx(customFont, "Clique na tela para reiniciar.", (Vector2){SCREEN_WIDTH / 2 - 390, SCREEN_HEIGHT / 2 - 60}, 20, 2, PINK);

    int minutos = (int)tempoJogo / 60;
    int segundos = (int)tempoJogo % 60;
    char strPontos[50], strTempo[50];
    sprintf(strPontos, "Pontuacao final: %d", pontos);
    sprintf(strTempo, "Tempo de jogo: %02d:%02d", minutos, segundos);
    DrawTextEx(customFont, strPontos, (Vector2){SCREEN_WIDTH / 2 - 370, SCREEN_HEIGHT / 2 - 180}, 23, 2, PINK);
    DrawTextEx(customFont, strTempo, (Vector2){SCREEN_WIDTH / 2 - 378, SCREEN_HEIGHT / 2 - 220}, 23, 2, PINK);
}

void TelaVitoria(Font customFont, Texture2D vitoriaImage, int pontos, float tempoJogo, Color titleColor, Sound musicavitoria, Music *music) {
    ClearBackground(BLACK);
    DrawTexture(vitoriaImage, (SCREEN_WIDTH - vitoriaImage.width) / 2, (SCREEN_HEIGHT - vitoriaImage.height) / 2, WHITE);
    DrawTextEx(customFont, "Parabens! Voce venceu!", (Vector2){SCREEN_WIDTH / 2 - 135, SCREEN_HEIGHT / 2 - 50}, 30, 2, PINK);
    DrawTextEx(customFont, "Clique na tela para continuar", (Vector2){SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 160}, 20, 2, PINK);

    int minutos = (int)tempoJogo / 60;
    int segundos = (int)tempoJogo % 60;
    char strPontos[50], strTempo[50];
    sprintf(strPontos, "Pontuacao final: %d", pontos);
    sprintf(strTempo, "Tempo de jogo: %02d:%02d", minutos, segundos);
    DrawTextEx(customFont, strPontos, (Vector2){SCREEN_WIDTH / 2 - 135, SCREEN_HEIGHT / 2 + 8}, 30, 2, PINK);
    DrawTextEx(customFont, strTempo, (Vector2){SCREEN_WIDTH / 2 - 135, SCREEN_HEIGHT / 2 + 60}, 30, 2, PINK);

    if (!musicaVitoriaTocando) {
        StopMusicStream(*music);
        PlaySound(musicavitoria);
        musicaVitoriaTocando = true;
    }
}

void MostrarMensagemErro(Font customFont, Questao questoes[], int perguntaAtual, int selectedLevel, Color textColor) {
    DrawTextEx(customFont, "Errado! A resposta era:", (Vector2){390, 265}, 23, 2, PINK);
    DrawTextEx(customFont, questoes[perguntaAtual].resposta, (Vector2){620, 299}, 27, 2, PINK);
}

void TelaRascunho(Font customFont, Color titleColor, Texture2D folhaCaderno) {
    DrawTexture(folhaCaderno, rascunhoPos.x, rascunhoPos.y, WHITE);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, (Rectangle){rascunhoPos.x, rascunhoPos.y, 800, 600})) {
            BeginTextureMode(rascunhoTarget);
            DrawCircleV((Vector2){mousePos.x - rascunhoPos.x, mousePos.y - rascunhoPos.y}, 5, BLACK);
            EndTextureMode();
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), (Rectangle){rascunhoPos.x, rascunhoPos.y, 800, 30})) {
        rascunhoMovendo = true;
        mouseOffset = (Vector2){GetMousePosition().x - rascunhoPos.x, GetMousePosition().y - rascunhoPos.y};
    }

    if (rascunhoMovendo) {
        rascunhoPos = (Vector2){GetMousePosition().x - mouseOffset.x, GetMousePosition().y - mouseOffset.y};
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            rascunhoMovendo = false;
        }
    }

    DrawTextureRec(rascunhoTarget.texture, (Rectangle){0, 0, rascunhoTarget.texture.width, -rascunhoTarget.texture.height}, rascunhoPos, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){SCREEN_WIDTH - 250, 10, 200, 40}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        LimparRascunho();
    }
}

void LimparRascunho() {
    BeginTextureMode(rascunhoTarget);
    ClearBackground(RAYWHITE);
    EndTextureMode();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "NexusNumber");
    InitAudioDevice();

    Font customFont = LoadFont("04B_30__.TTF");
    Font chalkboyFont = LoadFontEx("Neat Chalk.ttf", 30, NULL, 0);

    Texture2D background = LoadTexture("./imagens/menu111.png");
    Texture2D easyBackground = LoadTexture("./imagens/facill.png");
    Texture2D loadingImage = LoadTexture("./imagens/carregamento11.png");
    Texture2D mediumBackground = LoadTexture("./imagens/medio.png");
    Texture2D hardBackground = LoadTexture("./imagens/difficil.png");
    Texture2D pauseImage = LoadTexture("./imagens/pause.png");
    Texture2D gameOverImage = LoadTexture("./imagens/gameover.png");
    Texture2D vitoriaImage = LoadTexture("./imagens/vvenceuu.png");
    Texture2D folhaCaderno = LoadTexture("./imagens/rascunhoo.png");
    Texture2D rankingBackground = LoadTexture("./imagens/ranking11.png");
    Texture2D nomeBackground = LoadTexture("./imagens/nome111.png");

    Music music = LoadMusicStream("./audio/musica.ogg");
    SetMusicVolume(music, 0.5f);
    PlayMusicStream(music);
    Sound clickSound = LoadSound("./audio/click.wav");
    Sound venceuSound = LoadSound("./audio/acerto.wav");
    Sound musicavitoria = LoadSound("./audio/musicavitoria.ogg");
    SetSoundVolume(clickSound, 0.5f);
    SetSoundVolume(venceuSound, 0.5f);
    SetSoundVolume(musicavitoria, 0.5f);

    Color textColor = WHITE;
    Color enterButtonColor = PINK;
    Color enterButtonTextColor = WHITE;
    Color exitButtonColor = PINK;
    Color exitButtonTextColor = WHITE;
    Color rankingButtonColor = PINK;
    Color rankingButtonTextColor = WHITE;
    Color levelButtonColor = PINK;
    Color levelButtonTextColor = WHITE;
    Color titleColor = (Color){233, 30, 99, 255};

    Rectangle enterButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50 };
    Rectangle exitButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 50 };
    Rectangle rankingButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 90, 200, 50 };
    Rectangle easyButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 50, 200, 50 };
    Rectangle mediumButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 50 };
    Rectangle hardButton = { SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 90, 200, 50 };
    Rectangle rascunhoButton = { SCREEN_WIDTH - 620, 10, 170, 40 };

    bool exitGame = false;
    bool gameStarted = false;
    int selectedLevel = 0;
    float loadingTimer = 0;

    Questao questoesFaceis[10] = { 
        {"1- 2, 6, 12, 20, 30, ? Qual eh o proximo numero\nna sequencia?", "42"},
        {"2- A soma das idades de Ana e Bia eh 44. Ana eh\n 8 anos mais velha que Bia. Qual\n eh a idade de Ana?", "26"},
        {"3- 13 ? 18 = 31 | 7 ? 25 = 32 | 12 ? 30 = 42 | 26 ? 13 = ?", "39"},
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
        {"2- No meu jardim tem 4 pes de manga e 3 pes\n de acerola quantos pes eu tenho?", "2"},
        {"3- Se 3 gatos caca, 3 ratos em 3 minutos, em\n quantos minutos levarao 100 gatos para cacar\n 100 ratos?", "3"},
        {"4- Um carro viaja a 60 km/h. Em quantas horas\n levara para percorrer 180 km?", "3"},
        {"5- Se a=1, b=2, c=3, ..., z=26, qual eh a soma\n das letras da palavra CAT?", "24"},
    };

    srand(time(NULL));
    embaralhar(questoesFaceis, 10);
    embaralhar(questoesMedias, 5);
    embaralhar(questoesDificeis, 5);

    int perguntaAtual = 0;
    char respostaUsuario[256] = "";

    rascunhoTarget = LoadRenderTexture(800, 600);
    BeginTextureMode(rascunhoTarget);
    ClearBackground(RAYWHITE);
    EndTextureMode();

    while (!exitGame && !WindowShouldClose()) {
        UpdateMusicStream(music);
        if (!tempoParado) {
            tempoJogo += GetFrameTime();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_P)) {
            paused = !paused;
            aceitandoResposta = false;
        }

        if (paused) {
            MenuPausa(customFont, pauseImage, titleColor);
        } else if (mostrandoRanking) {
            MostrarRanking(customFont, titleColor, rankingBackground);
        } else if (entrandoNome) {
            EntradaNomeJogador(customFont, titleColor, nomeBackground, clickSound);
        } else if (gameOver) {
            TelaGameOver(customFont, gameOverImage, pontos, tempoJogo, titleColor);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
                tempoParado = false;
                respostaCerta = false; // Resetar a mensagem de resposta certa
            }
        } else if (vitoria) {
            TelaVitoria(customFont, vitoriaImage, pontos, tempoJogo, titleColor, musicavitoria, &music);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                gameStarted = false;
                showingLevelButtons = false;
                loading = false;
                loadingComplete = false;
                paused = false;
                vitoria = false;
                musicaVitoriaTocando = false; // Parar a música quando sair da tela de vitória
                vidas = 3;
                pontos = 0;
                perguntaAtual = 0;
                respostaUsuario[0] = '\0';
                tempoJogo = 0.0f;
                tempoParado = false;
                StopSound(musicavitoria); // Parar a música quando sair da tela de vitória
                PlayMusicStream(music); // Retomar a música principal
                respostaCerta = false; // Resetar a mensagem de resposta certa
            }
        } else {
            if (!gameStarted) {
                MenuPrincipal(customFont, background, enterButton, exitButton, rankingButton, enterButtonColor, enterButtonTextColor, exitButtonColor, exitButtonTextColor, rankingButtonColor, rankingButtonTextColor, titleColor);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, enterButton)) {
                        gameStarted = true;
                        showingLevelButtons = true;
                        PlaySound(clickSound);
                    } else if (CheckCollisionPointRec(mousePoint, exitButton)) {
                        exitGame = true;
                        PlaySound(clickSound);
                    } else if (CheckCollisionPointRec(mousePoint, rankingButton)) {
                        mostrandoRanking = true;
                        PlaySound(clickSound);
                    }
                }
            } else if (showingLevelButtons) {
                MostrarNiveis(customFont, background, easyButton, mediumButton, hardButton, levelButtonColor, levelButtonTextColor, titleColor);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (CheckCollisionPointRec(mousePoint, easyButton)) {
                        selectedLevel = 1;
                        entrandoNome = true;
                        showingLevelButtons = false;
                        PlaySound(clickSound);
                    } else if (CheckCollisionPointRec(mousePoint, mediumButton)) {
                        selectedLevel = 2;
                        entrandoNome = true;
                        showingLevelButtons = false;
                        PlaySound(clickSound);
                    } else if (CheckCollisionPointRec(mousePoint, hardButton)) {
                        selectedLevel = 3;
                        entrandoNome = true;
                        showingLevelButtons = false;
                        PlaySound(clickSound);
                    } else if (mousePoint.x >= 10 && mousePoint.x <= 110 && mousePoint.y >= 10 && mousePoint.y <= 30) {
                        gameStarted = false;
                        showingLevelButtons = false;
                        PlaySound(clickSound);
                    }
                }
            } else if (loading) {
                Carregando(customFont, loadingImage, titleColor);
                loadingTimer += GetFrameTime();
                if (loadingTimer >= 3.0f) {
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

                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePoint = GetMousePosition();
                    if (mousePoint.x >= 10 && mousePoint.x <= 110 && mousePoint.y >= 10 && mousePoint.y <= 30) {
                        showingLevelButtons = true;
                        loadingComplete = false;
                        respostaUsuario[0] = '\0';
                        PlaySound(clickSound);
                       
                    }

                    if (mousePoint.x >= SCREEN_WIDTH - 150 && mousePoint.x <= SCREEN_WIDTH - 50 && mousePoint.y >= 10 && mousePoint.y <= 30) {
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
                        PlaySound(clickSound);
                    }

                    if (CheckCollisionPointRec(mousePoint, rascunhoButton)) {
                        rascunhoAtivo = true;
                        aceitandoResposta = false;
                        PlaySound(clickSound);
                    }

                }

                if (IsKeyPressed(KEY_ENTER)) {
                    if (aceitandoResposta && (
                        (selectedLevel == 1 && strcmp(respostaUsuario, questoesFaceis[perguntaAtual].resposta) == 0) ||
                        (selectedLevel == 2 && strcmp(respostaUsuario, questoesMedias[perguntaAtual].resposta) == 0) ||
                        (selectedLevel == 3 && strcmp(respostaUsuario, questoesDificeis[perguntaAtual].resposta) == 0))) {
                        pontos += 10;
                        erro = false;
                        respostaCerta = true; // Definir a mensagem de resposta certa
                        PlaySound(venceuSound); // Toca o som quando a resposta está correta
                    } else {
                        vidas -= 1;
                        erro = true;
                        respostaCerta = false; // Limpar a mensagem de resposta certa em caso de erro
                        tempoErro = 0.0f;
                    }
                    perguntaAtual++;
                    respostaUsuario[0] = '\0';
                    if (perguntaAtual >= 10 || vidas <= 0) {
                        tempoParado = true;
                        SalvarPontuacao(nomeJogador, pontos);
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

            if (rascunhoAtivo) {
                TelaRascunho(customFont, titleColor, folhaCaderno);
                if (IsKeyPressed(KEY_V)) {
                    rascunhoAtivo = false;
                    aceitandoResposta = true;
                }

                if (IsKeyPressed(KEY_C)) {
                    LimparRascunho();
                }
            }
        }

        EndDrawing();
    }

    UnloadFont(customFont);
    UnloadTexture(background);
    UnloadTexture(easyBackground);
    UnloadTexture(loadingImage);
    UnloadTexture(mediumBackground);
    UnloadTexture(hardBackground);
    UnloadTexture(pauseImage);
    UnloadTexture(gameOverImage);
    UnloadTexture(vitoriaImage);
    UnloadTexture(folhaCaderno);
    UnloadTexture(rankingBackground);
    UnloadTexture(nomeBackground);
    UnloadMusicStream(music);
    UnloadSound(clickSound);
    UnloadSound(venceuSound);
    UnloadSound(musicavitoria); // Descarregar o som ao finalizar
    UnloadRenderTexture(rascunhoTarget);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

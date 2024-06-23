#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

// Estrutura para armazenar perguntas e respostas
typedef struct {
    char pergunta[256];
    char resposta[256];
} Questao;

// Variáveis globais
int vidas = 3;
int num[20];
int resposta[10];
int resposta_certa[10];
char op;
int operacao;
int tentativas = 1;
int dificuldade_jogo;
int i;

// Prototypes
void limparTela();
void esperar(int segundos);
char exibirMenuPrincipal();
char exibirMenuNivel();
void executarJogo(char nivelDoJogo);
void nivelfacil(int *vidas);
void nivelmedio(int *vidas);
void niveldificil(int *vidas);
void trocar(Questao *a, Questao *b);
void embaralhar(Questao questoes[], int n);
void nivelPerguntas(int *vidas, Questao questoes[], int total_questoes);

int main() {
    char escolhaMenu;
    char nivelDoJogo;

    srand(time(NULL));

    while (1) {
        escolhaMenu = exibirMenuPrincipal();

        if (escolhaMenu == '1') {
            limparTela();
            printf("\n\n\n\n                                                  Bem-vindo ao Nexus Number!\n\n");
            esperar(2);
            limparTela();
            nivelDoJogo = exibirMenuNivel();
            executarJogo(nivelDoJogo);
        } else if (escolhaMenu == '2') {
            exit(0);
        }
    }

    return 0;
}

void limparTela() {
    system("cls");
}

void esperar(int segundos) {
    Sleep(segundos * 1000);
}

char exibirMenuPrincipal() {
    printf("\n\n\n\n                                                      Nexus Number    \n\n\n\n\n\n\n");
    printf("                                                   1 - Iniciar Jogo    \n\n");
    printf("                                                       2 - Sair\n");

    return getch();
}

char exibirMenuNivel() {
    printf("\n\n\n\n                                                Escolha o nivel do jogo: \n\n\n");
    printf("                                                       1 - Facil\n\n");
    printf("                                                       2 - Medio\n\n");
    printf("                                                       3 - Dificil\n\n");

    return getch();
}

void executarJogo(char nivelDoJogo) {
    switch (nivelDoJogo) {
        case '1':
            nivelfacil(&vidas);
            break;
        case '2':
            nivelmedio(&vidas);
            break;
        case '3':
            niveldificil(&vidas);
            break;
        default:
            // Nada acontece se o nível não for 1, 2 ou 3.
            break;
    }
}

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

void nivelPerguntas(int *vidas, Questao questoes[], int total_questoes) {
    srand(time(NULL));
    embaralhar(questoes, total_questoes);

    for (int i = 0; i < total_questoes; i++) {
        int correta = 0;

        while (!correta) {
            limparTela();
            char resposta[256];
            printf("%s\n", questoes[i].pergunta);
            printf("Sua resposta: ");
            scanf("%s", resposta);

            if (strcmp(resposta, questoes[i].resposta) == 0) {
                printf("Correto!\n");
                correta = 1;
            } else {
                printf("Errado! Tente novamente.\n");
                getchar();
                getchar();
            }

            if (correta) {
                printf("Pressione Enter para continuar...");
                getchar();
                getchar();
            }
        }
    }
}

void nivelfacil(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\n4, 8 e 16: Qual eh o proximo numero?", "32"},
        {"Pergunta 2:\n6 = 30\n3 = 15\n7 = 35\n2 = ?", "10"},
        {"Pergunta 3:\nA + B = 60\nA - B = 40\nA / B = ?", "5"},
        {"Pergunta 4:\n13, 18 = 31\n7, 25 = 32\n12, 30 = 42\n26, 13 = ?", "39"},
        {"Pergunta 5:\n7, 15, 31: Qual eh o proximo numero?", "63"},
    };

    nivelPerguntas(vidas, questoes, 5);
}

void nivelmedio(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1 do medio:\nExemplo?", "Resposta"},
        {"Pergunta 2 do medio:\nExemplo?", "Resposta"},
        {"Pergunta 3 do medio:\nExemplo?", "Resposta"},
        {"Pergunta 4 do medio:\nExemplo?", "Resposta"},
    };

    nivelPerguntas(vidas, questoes, 5);
}

void niveldificil(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1 do dificil:\nExemplo?", "Resposta"},
        {"Pergunta 2 do dificil:\nExemplo?", "Resposta"},
        {"Pergunta 3 do dificil:\nExemplo?", "Resposta"},
        {"Pergunta 4 do dificil:\nExemplo?", "Resposta"},
    };

    nivelPerguntas(vidas, questoes, 5);
}

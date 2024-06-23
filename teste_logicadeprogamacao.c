#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Estrutura para armazenar perguntas e respostas
typedef struct {
    char pergunta[256];
    char resposta[256];
} Questao;

// Função para trocar duas questões
void trocar(Questao *a, Questao *b) {
    Questao temp = *a;
    *a = *b;
    *b = temp;
}

// Função para embaralhar as questões
void embaralhar(Questao questoes[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        trocar(&questoes[i], &questoes[j]);
    }
}

// Função para imprimir a matriz 4x4
void imprimirMatriz(int matriz[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matriz[i][j] == -1) {
                printf("? ");
            } else {
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

// Função para validar a resposta da matriz
int validarMatriz(int matriz[4][4], int resposta[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matriz[i][j] != -1 && matriz[i][j] != resposta[i][j]) {
                return 0; // Resposta errada
            }
        }
    }
    return 1; // Resposta correta
}

// Função para limpar a tela
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para obter a altura da janela do terminal
int alturaTerminal() {
    #ifdef _WIN32
        return 25; // Ajuste conforme necessário para Windows
    #else
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);
        return w.ws_row;
    #endif
}

// Função para centralizar o texto verticalmente
void centralizarTextoVertical(int altura_texto) {
    int altura_terminal = alturaTerminal();
    int linha_central = (altura_terminal - altura_texto) / 2;

    for (int i = 0; i < linha_central; i++) {
        printf("\n");
    }
}

// Função do nível fácil
void nivelFacil() {
   Questao questoes[5] = {
        {"Pergunta 1:\n4, 8 e 16: Qual é o próximo número?", "32"},
        {"Pergunta 2:\n6 = 30\n 3 = 15\n 7 = 35\n 2 = ?", "10"},
        {"Pergunta 3:\nA + B = 60\nA - B = 40\n A / B = ?", "5"},
        {"Pergunta 4:\n13,18 = 31\n7,25 = 32\n12, 30 = 42\n26, 13 = ?", "39"},
        {"Pergunta 5:\nComplete a matriz 4x4:\n"
         "0, 2, 1, 0, 0\n"
         "1, 4, 1, 1, 1\n"
         "2, 6, 1, 0, 2\n"
         "3, ?, ?, ?, ?\n", "8, 1, 1, 3"},
    };

    srand(time(NULL));
    embaralhar(questoes, 5);

    for (int i = 0; i < 5; i++) {
        int correta = 0;

        while (!correta) {
            limparTela();
            if (i == 4) {
                int matriz[4][4] = {
                    {2, 1, 0, 0},
                    {4, 1, 1, 1},
                    {6, 1, 0, 2},
                    {-1, -1, -1, -1}
                };

                int resposta[4][4] = {
                    {2, 1, 0, 0},
                    {4, 1, 1, 1},
                    {6, 1, 0, 2},
                    {0, 0, 0, 0}
                };

                printf("%s\n", questoes[i].pergunta);
                imprimirMatriz(matriz);

                printf("Preencha a linha 3 (separados por espaço): ");
                for (int j = 0; j < 4; j++) {
                    scanf("%d", &resposta[3][j]);
                }

                if (validarMatriz(matriz, resposta)) {
                    printf("Correto!\n");
                    correta = 1;
                } else {
                    printf("Errado! Tente novamente.\n");
                    getchar();
                    getchar();
                }
            } else {
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
            }
            if (correta) {
                printf("Pressione Enter para continuar...");
                getchar();
                getchar();
            }
        }
    }
}

// Função para exibir o submenu de dificuldade
void selecionarDificuldade() {
    int escolha;
    int valido = 0;

    while (!valido) {
        limparTela();

        centralizarTextoVertical(6); // 6 linhas de texto aproximadamente

        printf("\t\t\t\tSelecione a dificuldade do jogo:\n\n");
        printf("\t\t\t\t1. Facil\n");
        printf("\t\t\t\t2. Medio\n");
        printf("\t\t\t\t3. Dificil\n\n");
        printf("\t\t\t\tEscolha uma opcao (1-3): ");
        scanf("%d", &escolha);

        // Limpar buffer de entrada após a leitura do scanf
        while(getchar() != '\n');

        switch (escolha) {
            case 1:
                nivelFacil();
                valido = 1;
                break;
            case 2:
                // printf("Nível médio ainda não implementado.\n");
                // valido = 1;
                break;
            case 3:
                // printf("Nível difícil ainda não implementado.\n");
                valido = 1;
                break;
            default:
                // printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }
}

// Função para exibir o menu principal
void mostrarMenu() {
    int escolha;
    int valido = 0;

    while (!valido) {
        limparTela();

        centralizarTextoVertical(6); // 6 linhas de texto aproximadamente

        printf("\t\t\t\tNexusNumbers!\n\n");
        printf("\t\t\t\t1. Iniciar Jogo\n");
        printf("\t\t\t\t2. Sair\n\n");
        printf("\t\t\t\tEscolha uma opcaoo (1-2): ");
        scanf("%d", &escolha);

        // Limpar buffer de entrada após a leitura do scanf
        while(getchar() != '\n');

        switch (escolha) {
            case 1:
                selecionarDificuldade();
                valido = 1;
                break;
            case 2:
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                getchar();
                getchar();
                break;
        }
    }
}

int main() {
    mostrarMenu();
    return 0;
}

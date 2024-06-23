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

// Função do nível fácil
void nivelFacil() {
   Questao questoes[5] = {
        {"Pergunta 1: 4, 8 e 16: Qual eh o proximo numero?", "32"}, //perguntas e respostas
        {"Pergunta 2: 6 = 30\n 3 = 15\n 7 = 35\n 2 = ?\n", "10"},
        {"Pergunta 3: A + B = 60\nA - B = 40\n A / B = ?", "5"},
        {"Pergunta 4: 13,18 = 31\n7,25 = 32\n12, 30 = 42\n26, 13 = ?\n", "39"},
        {"Pergunta 5: Complete a matriz 4x4:\n"
         "Linha 0: 2, 1, 0, 0\n"
         "Linha 1: 4, 1, 1, 1\n"
         "Linha 2: 6, 1, 0, 2\n"
         "Linha 3: ?, ?, ?, ?\n"
         "Coluna 0: 2, 4, 6, ?\n"
         "Coluna 1: 1, 1, 1, ?\n"
         "Coluna 2: 0, 1, 0, ?\n"
         "Coluna 3: 0, 1, 2, ?\n", "8, 1, 1, 3"},
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

                if (validarMatriz((int[4][4]){{2, 1, 0, 0}, {4, 1, 1, 1}, {6, 1, 0, 2}, {8, 1, 1, 3}}, resposta)) {
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
        printf("Selecione a dificuldade do jogo:\n");
        printf("1. Facil\n");
        printf("2. Medio\n");
        printf("3. Dificil\n");
        printf("Escolha uma opcao (1-3): ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                nivelFacil();
                valido = 1;
                break;
            case 2:
                //printf("Nível médio ainda não implementado.\n");
                //valido = 1;
                break;
            case 3:
                //printf("Nível difícil ainda não implementado.\n");
                valido = 1;
                break;
            default:
                //printf("Opção inválida! Tente novamente.\n");
              //getchar();
               // getchar();
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
        printf("Bem-vindo ao NexusNumbers!\n");
        printf("1. Iniciar Jogo\n");
        printf("2. Sair\n");
        printf("Escolha uma opcao (1-2): ");
        scanf("%d", &escolha);

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




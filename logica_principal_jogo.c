#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

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

void nivelfacil(int *vidas) {
    // Implementação do nível fácil
    printf("Nível Fácil - Implementação Pendente\n");
    // Exemplo de lógica básica
    for(i = 0; i<4;i++){
        num[i] = (rand () % 50) + 1;
    }
    // Adicione a lógica do jogo aqui
}

void nivelmedio(int *vidas) {
    // Implementação do nível médio
    printf("Nível Médio - Implementação Pendente\n");
    // Exemplo de lógica básica
    for(i = 0; i<6;i++){
        num[i] = (rand () % 100) + 1;
    }
    // Adicione a lógica do jogo aqui
}

void niveldificil(int *vidas) {
    // Implementação do nível difícil
    printf("Nível Difícil - Implementação Pendente\n");
    // Exemplo de lógica básica
    for(i = 0; i<8;i++){
        num[i] = (rand () % 200) + 1;
    }
    // Adicione a lógica do jogo aqui
}

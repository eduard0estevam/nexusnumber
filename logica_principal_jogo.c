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
int pontos = 0;
int tentativas = 1;
int dificuldade_jogo;
int i;

// Protótipos das variáveis
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
void salvarPontuacao(int pontos);
void carregarPontuacoesAltas();
void exibirPontuacoesAltas();

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
            limparTela();
            exibirPontuacoesAltas();
            esperar(5);
            limparTela();
        } else if (escolhaMenu == '3') {
            exit(0);
        }
    }

    return 0;
}
//função para limpar a tela

void limparTela() {
    system("cls");
}
//função para "esperar" o carregamento da tela
void esperar(int segundos) {
    Sleep(segundos * 1000);
}
//menu principal do jogo
char exibirMenuPrincipal() {
    printf("\n\n\n\n                                                      Nexus Number    \n\n\n\n\n\n\n");
    printf("                                                   1 - Iniciar Jogo    \n\n");
    printf("                                                   2 - Pontuacoes Altas\n\n");
    printf("                                                   3 - Sair\n");

    return getch();
}
//submenu de escoloha da dificuldade do jogo
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
            // Nada acontece se o nível não for 1, 2 ou 3 //
            break;
    }
    printf("Jogo terminado! Sua pontuacao final eh: %d\n", pontos);
    salvarPontuacao(pontos);
    pontos = 0; // Resetar a pontuação para o próximo jogo
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

        while (!correta && *vidas > 0) {
            limparTela();
            char resposta[256];
            printf("Vidas restantes: %d\n", *vidas);
            printf("Pontuacao: %d\n", pontos);
            printf("%s\n", questoes[i].pergunta);
            printf("Sua resposta: ");
            scanf("%s", resposta);

            if (strcmp(resposta, questoes[i].resposta) == 0) {
                printf("Correto!\n");
                correta = 1;
                pontos += 10; // Incrementa a pontuação por resposta correta
            } else {
                printf("Errado! Tente novamente.\n");
                (*vidas)--;
                if (*vidas > 0) {
                    esperar(2);
                }
            }

            if (correta) {
                printf("Pressione Enter para continuar...");
                getchar(); // Espera pelo Enter
                getchar();
            }
        }

        if (*vidas == 0) {
            printf("Voce perdeu todas as suas vidas. Fim de jogo!\n");
            break;
        }
    }
}

void nivelfacil(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\n2, 6, 12, 20, 30, ? Qual eh o proximo numero na sequencia?", "42"},
        {"Pergunta 2:\nA soma das idades de Ana e Bia é 44. Ana eh 8 anos mais velha que Bia. Qual eh a idade de Ana?", "26"},
        {"Pergunta 3:\n13,18 = 31\n7,25 = 32\n12, 30 = 42\n26, 13 = ?", "39"},
        {"Pergunta 4:\nQual é o próximo número na sequência: 1, 4, 9, 16, 25, ...?", "36"},
        {"Pergunta 5:\nJoao tem o dobro da idade de Pedro. Se a diferenca de suas idades eh de 15 anos, quantos anos Joao tem?", "30"},
        {"Pergunta 6:\n4, 8 e 16: Qual eh o proximo numero?", "32"},
        {"Pergunta 7:\n + B = 60\nA - B = 40\n A / B = ?", "5"},
        {"Pergunta 8:\nEm um quadrado formado por 16 palitos, com quantos palitos eu posso fazer 2 quadrados ?", "4"},
        {"Pergunta 9:\nA média aritmetica de cinco numeros é 12. Se um dos numeros é 16, qual eh a media dos outros quatro números?", "11"},
        {"Pergunta 10:\n6 = 30\n 3 = 15\n 7 = 35\n 2 = ?", "10"},
    };

    nivelPerguntas(vidas, questoes, 10);
}

void nivelmedio(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\nEm um saco há 5 bolas vermelhas, 4 bolas azuis e 3 bolas verdes. Qual a probabilidade de se retirar uma bola azul?", "1/3"},
        {"Pergunta 3:\nSe o dobro de um número é 24, qual é metade desse número?", " 6"},
        {"Pergunta 5:\nSe 5 maquinas podem completar um trabalho em 8 horas, quantas horas levarao 8 maquinas para completar o mesmo trabalho?", "5"},
        {"Pergunta 6:\nUm produto custa R$ 120,00. Após um desconto de 25%%, qual é o novo preço?", "90"},
        {"Pergunta 7:\nSe a=1, b=2, c=3, ..., z=26, qual é a soma das letras da palavra "CAT?"", "24"},
        {"Pergunta 8:\nQual é a soma de 1/3 e 1/4?", "7/12"},
    };

    nivelPerguntas(vidas, questoes, 5);
}

void niveldificil(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\nDuas tartarugas caminham em direção a um lago. A primeira percorre 30 metros por dia e chega ao lago em 16 dias. A segunda tartaruga percorre 20 metros por dia. Quando a primeira tartaruga chegou ao lago, quantos dias ela teve que esperar para a segunda tartaruga chegar?", "8"},
        {"Pergunta 2:\nEm um sistema de codificação, AB representa os algarismos do dia do nascimento de uma pessoa e CD os algarismos de seu mês de nascimento. Qual é o mês de nascimento dessa pessoa se a data for trinta de julho?", "07"},
        {"Pergunta 3:\nSe 3 gatos caçam 3 ratos em 3 minutos, em quantos minutos levarão 100 gatos para caçar 100 ratos?", "3"},
        {"Pergunta 4:\nExemplo?", "Resposta"},
    };

    nivelPerguntas(vidas, questoes, 10);
}

void salvarPontuacao(int pontos) {
    FILE *arquivo = fopen("pontuacoes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuacoes.\n");
        return;
    }
    fprintf(arquivo, "%d\n", pontos);
    fclose(arquivo);
}

void carregarPontuacoesAltas() {
    FILE *arquivo = fopen("pontuacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuacoes.\n");
        return;
    }

    int pontuacao;
    printf("Pontuacoes Altas:\n");
    while (fscanf(arquivo, "%d", &pontuacao) != EOF) {
        printf("%d\n", pontuacao);
    }

    fclose(arquivo);
}

void exibirPontuacoesAltas() {
    carregarPontuacoesAltas();
}

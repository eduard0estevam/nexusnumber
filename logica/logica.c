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

int compararDecrescente(const void *a, const void *b);

// Estrutura para armazenar pontuação com nome do jogador
typedef struct {
    char nome[50];
    int pontuacao;
} Pontuacao;

// Variáveis globais
int vidas = 3; // Quantidade de vidas
int pontos = 0; // Pontuação a ser acumulada pelo jogador

// Protótipos das funções
void limparTela();
void esperar(int segundos);
char exibirMenuPrincipal();
char exibirMenuNivel();
void executarJogo(char nivelDoJogo);
void nivelFacil(int *vidas);
void nivelMedio(int *vidas);
void nivelDificil(int *vidas);
void trocar(Questao *a, Questao *b);
void embaralhar(Questao questoes[], int n);
void nivelPerguntas(int *vidas, Questao questoes[], int total_questoes);
void salvarPontuacao(char nome[], int pontos);
void carregarPontuacoesAltas();
void exibirPontuacoesAltas();

// Função principal
int main() {
    char nomeJogador[50];
    char nivelDoJogo;

    printf("\n\n\n\n                                                  Bem-vindo ao Nexus Number!\n\n");
    printf("Insira seu nome: ");
    fgets(nomeJogador, sizeof(nomeJogador), stdin);
    nomeJogador[strcspn(nomeJogador, "\n")] = '\0'; // Remover o '\n' do final da string lida

    vidas = 3;
    pontos = 0;

    srand(time(NULL));

    nivelDoJogo = exibirMenuNivel();
    limparTela();
    executarJogo(nivelDoJogo);
    printf("\n%s, sua pontuacao final eh: %d\n", nomeJogador, pontos);
    salvarPontuacao(nomeJogador, pontos);
    pontos = 0; // Resetar a pontuação para o próximo jogo

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
    printf("                                                   2 - Pontuacoes Altas\n\n");
    printf("                                                   3 - Sair\n");

    return getch();
}

char exibirMenuNivel() {
    printf("\n\n\n\n                                                Escolha o nível do jogo: \n\n\n");
    printf("                                                       1 - Facil\n\n");
    printf("                                                       2 - Medio\n\n");
    printf("                                                       3 - Dificil\n\n");

    return getch();
}

void executarJogo(char nivelDoJogo) {
    switch (nivelDoJogo) {
        case '1':
            nivelFacil(&vidas);
            break;
        case '2':
            nivelMedio(&vidas);
            break;
        case '3':
            nivelDificil(&vidas);
            break;
        default:
            // Nada acontece se o nível não for 1, 2 ou 3
            break;
    }
    printf("Jogo terminado! Sua pontuacao final eh: %d\n", pontos);
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
            fgets(resposta, sizeof(resposta), stdin);
            resposta[strcspn(resposta, "\n")] = '\0'; // Remover o '\n' do final da string lida

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

void nivelFacil(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\n2, 6, 12, 20, 30, ? Qual eh o próximo número na sequencia?", "42"},
        {"Pergunta 2:\nA soma das idades de Ana e Bia eh 44. Ana eh 8 anos mais velha que Bia. Qual eh a idade de Ana?", "26"},
        {"Pergunta 3:\n13, 18 = 31\n7, 25 = 32\n12, 30 = 42\n26, 13 = ?", "39"},
        {"Pergunta 4:\nQual eh o proximo numero na sequencia: 1, 4, 9, 16, 25, ...?", "36"},
        {"Pergunta 5:\nJoao tem o dobro da idade de Pedro. Se a diferença de suas idades eh de 15 anos, quantos anos Joao tem?", "30"},
        {"Pergunta 6:\n4, 8 e 16: Qual eh o proximo numero?", "32"},
        {"Pergunta 7:\n + B = 60\nA - B = 40\n A / B = ?", "5"},
        {"Pergunta 8:\nEm um quadrado formado por 16 palitos, com quantos palitos eu posso fazer 2 quadrados ?", "4"},
        {"Pergunta 9:\nA media aritmetica de cinco numeros eh 12. Se um dos numeros eh 16, qual eh a media dos outros quatro numeros?", "11"},
        {"Pergunta 10:\n6 = 30\n 3 = 15\n 7 = 35\n 2 = ?", "10"},
    };

    nivelPerguntas(vidas, questoes, 10);
}

void nivelMedio(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\nEm um saco ha 5 bolas vermelhas, 4 bolas azuis e 3 bolas verdes. Qual a probabilidade de se retirar uma bola azul?", "1/3"},
        {"Pergunta 2:\nSe o dobro de um número eh 24, qual eh a metade desse numero?", "12"},
        {"Pergunta 3:\nSe 5 maquinas podem completar um trabalho em 8 horas, quantas horas levarao 8 maquinas para completar o mesmo trabalho?", "5"},
        {"Pergunta 4:\nUm produto custa R$ 120,00. Apos um desconto de 25%%, qual eh o novo preco?", "90"},
        {"Pergunta 5:\nQual eh a soma de 1/3 e 1/4?", "7/12"},
    };

    nivelPerguntas(vidas, questoes, 5);
}

void nivelDificil(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\n9, 16 = 7\n4, 36 = 8\n121, 81 = 20\n 25, 49 = ?", "12"},
        {"Pergunta 2:\nEm um sistema de codificação, AB representa os algarismos do dia do nascimento de uma pessoa e CD os algarismos de seu mês de nascimento. Qual eh o mês de nascimento dessa pessoa se a data for trinta de julho?", "07"},
        {"Pergunta 3:\nSe 3 gatos caçam 3 ratos em 3 minutos, em quantos minutos levarão 100 gatos para caçar 100 ratos?", "3"},
        {"Pergunta 4:\nUm carro viaja a 60 km/h. Em quantas horas levará para percorrer 180 km?", "3"},
        {"Pergunta 5:\nSe a=1, b=2, c=3, ..., z=26, qual eh a soma das letras da palavra CAT?", "24"},
    };

    nivelPerguntas(vidas, questoes, 5);
}

void salvarPontuacao(char nome[], int novaPontuacao) {
    FILE *arquivo = fopen("pontuacoes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuacoes.\n");
        return;
    }

    fprintf(arquivo, "%s;%d\n", nome, novaPontuacao);

    fclose(arquivo);
}

void carregarPontuacoesAltas() {
    FILE *arquivo = fopen("pontuacoes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuacoes.\n");
        return;
    }

    Pontuacao pontuacoes[100];
    int count = 0;

    while (count < 100 && fscanf(arquivo, "%49[^;];%d\n", pontuacoes[count].nome, &pontuacoes[count].pontuacao) == 2) {
        count++;
    }

    fclose(arquivo);

    // Ordenar pontuações em ordem decrescente
    qsort(pontuacoes, count, sizeof(Pontuacao), compararDecrescente);

    // Exibir as pontuações
    printf("Pontuacoes:\n");
    for (int i = 0; i < count; i++) {
        printf("%s - %d\n", pontuacoes[i].nome, pontuacoes[i].pontuacao);
    }
}

void exibirPontuacoesAltas() {
    carregarPontuacoesAltas();
}

int compararDecrescente(const void *a, const void *b) {
    const Pontuacao *pontuacaoA = (const Pontuacao *)a;
    const Pontuacao *pontuacaoB = (const Pontuacao *)b;

    return (pontuacaoB->pontuacao - pontuacaoA->pontuacao);
}

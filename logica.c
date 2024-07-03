#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <locale.h>



// Estrutura para armazenar perguntas e respostas
typedef struct {
    char pergunta[256];
    char resposta[256];
} Questao;

// Variáveis globais
int vidas = 3; //quantidade de vidas
int pontos = 0; //pontuação a ser acumulada pelo jogador
int tentativas = 1;//numero de tentativas
int dificuldade_jogo; //dificuldade do jogo a ser escolhida pelo jogador 
int i;
int j;

// Protótipos das funções iniciais do game
// eles servem para voce conseguir  organizar as funções
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

int main(int argc, char** argv) {
	
	setlocale(LC_ALL, "portuguese");
	
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
    printf("                                                   2 - Pontuações Altas\n\n");
    printf("                                                   3 - Sair\n");

    return getch();
}
//submenu de escoloha da dificuldade do jogo
char exibirMenuNivel() {
    printf("\n\n\n\n                                                Escolha o nível do jogo: \n\n\n");
    printf("                                                       1 - Fácil\n\n");
    printf("                                                       2 - Médio\n\n");
    printf("                                                       3 - Difícil\n\n");

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
    printf("Jogo terminado! Sua pontuação final é: %d\n", pontos);
    salvarPontuacao(pontos);
    pontos = 0; // Resetar a pontuação para o próximo jogo
}
// vai pegar os endereços e com o ponteiro vai pegar o conteudo do endero a(questoes[i]) e do endereço b(questoes[variavelrandomica])
void trocar(Questao *a, Questao *b) {
    Questao temp = *a;
    *a = *b;
    *b = temp;
}
// vai puchar uma função do nivel selecionado e vai passar array ( sequencia de dados) e o int n vai pegar o tamanho do array 
void embaralhar(Questao questoes[], int n) {
    // o for vai rodar todas as questões do nivel selecionado.
    for (i = n - 1; i > 0; i--) {
        int variavelrandomica = rand() % (i + 1);
        // vai chamar a função troca  e vai passar para a função trocar os endereçõs das questoes que serão trocadas.
        trocar(&questoes[i], &questoes[variavelrandomica]);
    }
}

//Trata a lógica das perguntas, verifica as respostas e atualiza a pontuação e o número de vidas.

void nivelPerguntas(int *vidas, Questao questoes[], int total_questoes) {
    srand(time(NULL));
    embaralhar(questoes, total_questoes);

    for (i = 0; i < total_questoes; i++) {
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
            printf("Você perdeu todas as suas vidas. Fim de jogo!\n");
            break;
        }
    }
}

void nivelfacil(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\n2, 6, 12, 20, 30, ? Qual é o próximo numero na sequência?", "42"},
        {"Pergunta 2:\nA soma das idades de Ana e Bia é 44. Ana é 8 anos mais velha que Bia. Qual é a idade de Ana?", "26"},
        {"Pergunta 3:\n13,18 = 31\n7,25 = 32\n12, 30 = 42\n26, 13 = ?", "39"},
        {"Pergunta 4:\nQual é o proximo número na sequência: 1, 4, 9, 16, 25, ...?", "36"},
        {"Pergunta 5:\nJoão tem o dobro da idade de Pedro. Se a diferença de suas idades é de 15 anos, quantos anos João tem?", "30"},
        {"Pergunta 6:\n4, 8 e 16: Qual é o próximo número?", "32"},
        {"Pergunta 7:\n + B = 60\nA - B = 40\n A / B = ?", "5"},
        {"Pergunta 8:\nEm um quadrado formado por 16 palitos, com quantos palitos eu posso fazer 2 quadrados ?", "4"},
        {"Pergunta 9:\nA média aritmética de cinco números é 12. Se um dos números é 16, qual é a média dos outros quatro números?", "11"},
        {"Pergunta 10:\n6 = 30\n 3 = 15\n 7 = 35\n 2 = ?", "10"},
    };

    nivelPerguntas(vidas, questoes, 10);
}

void nivelmedio(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\nEm um saco há 5 bolas vermelhas, 4 bolas azuis e 3 bolas verdes. Qual a probabilidade de se retirar uma bola azul?", "1/3"},
        {"Pergunta 2:\nSe o dobro de um número é 24, qual é a metade desse número?", " 6"},
        {"Pergunta 3:\nSe 5 máquinas podem completar um trabalho em 8 horas, quantas horas levarão 8 máquinas para completar o mesmo trabalho?", "5"},
        {"Pergunta 4:\nUm produto custa R$ 120,00. Apos um desconto de 25%%, qual é o novo preço?", "90"},
        {"Pergunta 5:\nQual é a soma de 1/3 e 1/4?", "7/12"},
    };

    nivelPerguntas(vidas, questoes, 5);
}

void niveldificil(int *vidas) {
    Questao questoes[] = {
        {"Pergunta 1:\nDois caracóis estão se movendo em direção a um jardim. O primeiro caracol percorre 30 metros por dia e leva 16 dias para chegar ao jardim. O segundo caracol se move a uma velocidade de 20 metros por dia. Após quantos dias o segundo caracol alcançará o jardim, considerando que o primeiro caracol já está lá?", "8"},
        {"Pergunta 2:\nEm um sistema de codificação, AB representa os algarismos do dia do nascimento de uma pessoa e CD os algarismos de seu mês de nascimento. Qual é o mês de nascimento dessa pessoa se a data for trinta de julho?", "07"},
        {"Pergunta 3:\nSe 3 gatos caçam 3 ratos em 3 minutos, em quantos minutos levarão 100 gatos para caçar 100 ratos?", "3"},
        {"Pergunta 4:\nUm carro viaja a 60 km/h. Em quantas horas levará para percorrer 180 km?", "3"},
        {"Pergunta 5:\nSe a=1, b=2, c=3, ..., z=26, qual é a soma das letras da palavra CAT?", "24"},

    };

    nivelPerguntas(vidas, questoes, 5);
}

//carrega a pontuação dos jogadores e salva num arquivo de texto
void salvarPontuacao(int novaPontuacao) {
    FILE *arquivo = fopen("pontuacoes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuacoes.\n"); //o arquivo ainda nao existe
        return;
    }

     fprintf(arquivo, "%d\n", novaPontuacao);
    
    fclose(arquivo);
}

void carregarPontuacoesAltas() {
    FILE *arquivo = fopen("pontuacoes.txt", "r");//aqui ele vai ler todas as pontuacoes que foram salvas na funcao "salvarPontuacao"
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de pontuações.\n");
        return;
    }

    int pontuacoes[100];
    int count = 0;

//le as pontuações do arquivo e armazená-las no array pontuacoes
    while (fscanf(arquivo, "%d", &pontuacoes[count]) != EOF && count < 100) {
        count++;
    }

     fclose(arquivo);

    // Ordenar as pontuações em ordem decrescente
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (pontuacoes[i] < pontuacoes[j]) {
                int temp = pontuacoes[i];
                pontuacoes[i] = pontuacoes[j];
                pontuacoes[j] = temp;
            }
        }
    }

    // Exibir as pontuações
    printf("Pontuações Altas:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", pontuacoes[i]);
    }
}


void exibirPontuacoesAltas() {
    carregarPontuacoesAltas();
}


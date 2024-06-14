#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>

void nivelfacil(int *vidas) {
     for(int i = 0; i<4; i++){
        
        //random de numeros
        num[]= rand ()% 101;
   if(operacoes == '+')
   for(int contador = 0; contador < 4; contador++) {

    resposta_certa[i] = num[i] + num[i+1];
                op = operacoes[0]; {
      
    } if else(operacoes == '-') {
         resposta_certa[i] = num[i] - num[i+1];
                op = operacoes[1];
    } else if(operacoes == '*') {
       resposta_certa[i] = num[i] * num[i+1];
                op = operacoes[2];
    } else if(operacoes == '/') { 
      resposta_certa[i] = num[i] / num[i+1];
                op = operacoes[3];
    }

   }
      }
void nivelmedio(int *vidas) {
    i
}

void niveldificil(int *vidas) {
    int respostacorreta = 1; 
    char valor_resposta[55];

    printf("Calcule f(x) = 1 / (x^2 + x)\n");

    fgets(valor_resposta, 55, stdin);

    int resposta = atoi(valor_resposta);

    if(resposta == respostacorreta) {
        printf("Resposta Correta\n");
    } else {
        printf("Resposta Errada! Você perdeu uma vida.\n");
        (*vidas)--;
    }
}

int main(){
   //comando para a geração de códigos aleatórios
    srand(time(NULL));
    int num[20];
    int resposta[10];
    int resposta_certa[10];
    //verificação das opções dadas e a seleção da dificuldade de jogo
    char op;
    int opcao_jogo;
    int dificuldade_jogo;
    char operacoes[5]="+-*/";
    int operacao;
    int true = 1;
    int tentativas = 1;
    int vidas = 4;

   

        printf("*************************************\n");
        printf("*           Nexus Number            *\n");
        printf("*************************************\n");
        printf("1. Iniciar Jogo\n");
        printf("2. Sair\n");
        getchar();
        fgets(opcao_jogo,50,stdin);

        opcao_jogo[strcspn(opcao_jogo, "\n")] = 0;

        if(strcmp(opcao_jogo,"2") == 0){
            break;

            if(opcao_jogo == '1') {
               printf("Insira a dificuldade do jogo:\n");
               printf("1. Facil\n");
               printf("2. Medio\n");
               printf("3. Dificil\n");
               scanf("%d", dificuldade_jogo);
                if("dificuldade == 1") {
                  do
                  {
                     /* code */
                  } while (/* condition */);
                  
                }
                printf(" diga o resultado da equacao %d",num[i]);
                printf("%c",op);
                printf("%d\n",num[i+1]);
                scanf("%d",&resposta[i]);
                if(resposta[i]==resposta_certa[i]){
                    printf("voce acertou\n");
                    tentativas = 0;
                }else{
                    printf("voce errou tente de novo\n");
                }
            }
        }
    }
    return 0;
}

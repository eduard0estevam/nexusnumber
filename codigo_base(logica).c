#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
// variaveis globais 
    int vidas = 3;
   int num[20];
   int resposta[10];
   int resposta_certa[10];
   char teste_jogo[7]="";
   char op;
   int operacao;
   int true = 1;
   int tentativas = 1;
   int dificuldade_jogo;

// struct para o primeiro nivel 
void nivelfacil(int *vidas){
//funçao randomica para ser selecionado os numeros inteiros aleatorios da primeira questao
   for(int i = 0; i<4;i++){
      num[i]= (rand ()% 50)+1;
   }
   
// Realização das operações do primeiro nivel 
    for(int i = 0; i < 2; i++) {
// função que vai escolher aleatoriamente qual calculo será realizado 
        operacao = (rand() % 4 )+ 1;
// teste que vai fazer o calculo escolhido
        if(operacao == 1){
            resposta_certa[i] = num[i] + num[i+1];
            printf("aaaaaaaaaaaaaaaaaaaaaaaaa\n");
            op = '+';
            // laço para tentativas de acerto do jogador 
            while(vidas!=0){
                printf(" diga o resultado da equacao %d %c %d\n",num[i],op,num[i+1]);
                 scanf("%d",&resposta[i]);
                    if(resposta[i]==resposta_certa[i]){
                        printf("voce acertou\n");
                        break;
                    }else{
                        printf("voce errou tente de novo\n");
                        vidas--;
                    }
            }
        }else if(operacao == 2) {
            resposta_certa[i] = num[i] - num[i+1];
            op = '-';
           while(vidas!=0){
                printf(" diga o resultado da equacao %d %c %d\n",num[i],op,num[i+1]);
                 scanf("%d",&resposta[i]);
                    if(resposta[i]==resposta_certa[i]){
                        printf("voce acertou\n");
                        break;
                    }else{
                        printf("voce errou tente de novo\n");
                        vidas--;
                    }
            }
        }else if(operacao == 3) {
            resposta_certa[i] = num[i] * num[i+1];
            op = '*';
            while(vidas!=0){
                printf(" diga o resultado da equacao %d %c %d\n",num[i],op,num[i+1]);
                 scanf("%d",&resposta[i]);
                    if(resposta[i]==resposta_certa[i]){
                        printf("voce acertou\n");
                        break;
                    }else{
                        printf("voce errou tente de novo\n");
                        vidas--;
                    }
        }
        }else if(operacao == 4) { 
            resposta_certa[i] = num[i] / num[i+1];
            op = '/';
            while(vidas!=0){
                printf(" diga o resultado da equacao %d %c %d\n",num[i],op,num[i+1]);
                 scanf("%d",&resposta[i]);
                    if(resposta[i]==resposta_certa[i]){
                        printf("voce acertou\n");
                        break;
                    }else{
                        printf("voce errou tente de novo\n");
                        vidas--;
                    }
            }
        }
}
}

int main(){
    int true;
    srand(time(NULL));
    while(1){
        printf("*************************************\n");
        printf("*           Nexus Number            *\n");
        printf("*************************************\n");
        printf("1. Iniciar Jogo\n");
        printf("2. Sair\n");
       scanf("%d",&true);

        if(true == 2){
            break;
        }
        if( true == 1) {
               printf("Insira a dificuldade do jogo:\n");
               printf("1. Facil\n");
               printf("2. Medio\n");
               printf("3. Dificil\n");
               scanf("%d", &dificuldade_jogo);
                if(dificuldade_jogo == 1) {
                    nivelfacil(&vidas);
                }
            }
        }
   return 0;
    }
     
    

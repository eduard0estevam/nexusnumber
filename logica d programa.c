#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
int main(){
//funçao que inicia a semente da randomização
   srand(time(NULL));
// atribui as variaves que serão necessarias
   int num[20];
   int resposta[10];
   int resposta_certa[10];
   char teste_jogo[7]="";
   char operacao;
   int true = 1;
   int tentativas = 1;
   
//funçao randomica para ser selecionado 10 numeros inteiros aleatorios
   for(int i = 0; i<4;i++){
      num[i]= rand ()% 101;
   }

   //primeiro laço que eu acredito ser o laço q vai ficar como laço principal
while(true==1){
printf("voce quer jogar o jogo digite sim ou nao\n");
fgets(teste_jogo,7,stdin);
//teste para caso a pessoa queira sair.
if(!strcmp(teste_jogo,"sim")!=1){
   true = 0;
}
// laço para realizar as equacoes do primeiro nivel de forma que as operações sejam de forma randomica
for(int i = 0; i<4;i++){
   operacao = operacao[rand()%4];
   switch (operacao)
   {
   case '+':
      resposta_certa[i] = num[i] + num[i+1];
      break;
   
   case '-':
      resposta_certa[i] = num[i] - num[i+1];
      break;
   case '*':
      resposta_certa[i] = num[i] * num[i+1];
      break;
   case '/':
      resposta_certa[i] = num[i] / num[i+1];

   default:
      break;
   }
   while(tentativas==1){
   printf(" diga o resultado da equação %d %c %d ",num[i],operacao,num[i+1]);
   scanf("%d",&resposta[i]);
   if(resposta[i]==resposta_certa[i]){
      printf("voce acertou\n");
      tentativas = 0;
   }else{
      printf("voce errou\n");
   }
   }
}
}
 return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
int main(){
//funçao que inicia a semente da randomização
   srand(time(NULL));
// atribui as variaves que eu acredito que serão necessarias
   int num[20];
   int respota[10];
   int resposta_certa[10];
   char teste_jogo[7]="";
   char operacao;
   
//funçao randomica para ser selecionado 10 numeros inteiros aleatorios
   for(int i = 0; i<4;i++){
      num[i]= rand % 101;
   }
// laço para realizar as equacoes do primeiro nivel 
 for(int i = 0; i<4;i++){
   operacao = operacao[rand()%4];
   switch (operacao)
   {
   case '+':
      resposta_certa[i] = num[i] + num[i+1];
      break;
   
   case ''
   default:
      break;
   }
   }
   //primeiro laço que eu acredito ser o laço q vai ficar como laço principal
while(1){
}
 return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
int main(){
//funçao que inicia a semente da randomização
   srand(time(NULL));
// atribui as variaves que eu acredito que serão necessarias
   int num[20];
   int respota[10];
   int resposta_certa[10];
   char teste_jogo[7]="";
   char operacao;
   
//funçao randomica para ser selecionado 10 numeros inteiros aleatorios
   for(int i = 0; i<4;i++){
      num[i]= rand % 101;
   }
// laço para realizar as equacoes do primeiro nivel 
 for(int i = 0; i<4;i++){
   operacao = operacao[rand()%4];
   switch (operacao)
   {
   case '+':
      resposta_certa[i] = num[i] + num[i+1];
      break;
   
   case ''
   default:
      break;
   }
   }
   //primeiro laço que eu acredito ser o laço q vai ficar como laço principal
while(1){
}
 return 0;
}

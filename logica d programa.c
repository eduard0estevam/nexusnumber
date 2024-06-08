#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
//funções para definir o nível de dificuldade do jogo//exemplo//

void nivelfacil(int *vidas); {

   int respostacorreta = 64;
    char valor_resposta[55];

    printf("Quanto eh 54 + 10?\n");

    fgets(valor_resposta, 55, stdin);

    int resposta = atoi(valor_resposta);

    if(resposta == respostacorreta) {
        printf("Resposta Correta\n");
    } else {
        printf("Resposta Errada! Voce perdeu uma vida.\n");
        (*vidas)--;
    }

}
void nivelmedio(int *vidas) {

    int respostacorreta = 205;
    char valor_resposta[55];

    printf("Quanto eh (40 *4) + (10 - 5 * 2) + 45 ?\n");

    fgets(valor_resposta, 55, stdin);

    int resposta = atoi(valor_resposta);

    if(resposta == respostacorreta) {
        printf("Resposta Correta\n");
    } else {
        printf("Resposta Errada! Voce perdeu uma vida.\n");
        (*vidas)--;
    }
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
/*aqui, a função void nao vai retornar nada, e vai definir a quantidade de vidas por niveis. a quantida de vidas eh, por exemplo, 4.
se errar uma questao, fica vida--, e essa subtração da vida se da pelo uso do ponteiro, que vai diretamente
localizar o numero de vidas e decrementar*/
int main(){
//funçao que inicia a semente da randomização
   srand(time(NULL));
// atribui as variaves que serão necessarias
   int num[20];
   int resposta[10];
   int resposta_certa[10];
   char teste_jogo[7]="";
   char op;
   char opcao_jogo[50];
   int opcao_jjogo;
   char operacoes[5]="+-*/";
   int operacao;
   int true = 1;
   int tentativas = 1;
   
//funçao randomica para ser selecionado os numeros inteiros aleatorios da primeira questao
   for(int i = 0; i<4;i++){
      num[i]= rand ()% 101;
   }

   //primeiro laço que eu acredito ser o laço q vai ficar como laço principal
while(true==1){
      printf("*************************************\n");
      printf("*           Nexus Number            *\n");
      printf("*************************************\n");
      printf("1. Iniciar Jogo\n");
      printf("2. Sair");
            getchar();
      fgets(opcao_jogo,50,stdin);

      opcao_jogo[strcspn(opcao_jogo, "\n")] = 0;

//teste para caso a pessoa queira sair.
if(strcmp(opcao_jogo,"1")){
   
   
}
// laço para realizar as equacoes do primeiro nivel de forma que as operações sejam de forma randomica
for(int i = 0; i<4;i++){
   operacao = (rand() % 4 )+ 1;
   switch (operacao)
   {
   case '1':
      resposta_certa[i] = num[i] + num[i+1];
      op = operacoes[0];
      printf("aaaaaaaaaaaaaaaaaaaaaaaaa\n");
      break;
   
   case '2':
      resposta_certa[i] = num[i] - num[i+1];
      op = operacoes[1];
      printf("bbbbbbbbbbbbbbbbbbbbbbb\n");
      break;
   case '3':
      resposta_certa[i] = num[i] * num[i+1];
      op = operacoes[2];
      printf("cccccccccccccccccccccccc\n");
      break;
   case '4':
      resposta_certa[i] = num[i] / num[i+1];
      op = operacoes[3];
      printf("dddddddddddddddddddddddddd\n");
      break;
   default:
      break;
   }
   while(tentativas==1){
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

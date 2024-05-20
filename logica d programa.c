#include <stdio.h>
//espaço de 3 linhas para as outras bibliotecas.


void main(){

// atribui as variaves que eu acredito que serão necessarias
int cont = 0 ;
int num[10] = {0,1,2,3,4,5,6,7,8,9};
int resultado[20];
char inicio_jog[7] = "inicio";

//primeiro laço que eu acredito ser o laço q vai ficar como geral
do{
 printf("%s\n",inicio_jog);
 printf("quer jogar ou nao\n");
 scanf("%d",&cont);
 if(cont==0){
    break;
 }
 }while(1);


}

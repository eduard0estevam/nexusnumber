#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int main(){

    char escolhaMenu; 
    char nivelDoJogo;
    

        printf("\n\n\n\n                                                      Nexus Number    \n\n\n\n\n\n\n");
        printf("                                                   1 - Iniciar Jogo    \n\n");
        printf("                                                       2 - Sair\n");
        
        

    while(1){

        escolhaMenu = getch(); //Lê um caractére sem aparecer na tela e sem precisar dar enter.
        
        if(escolhaMenu == '1'){
             system("cls"); // Limpa a tela antes de imprimir a próxima frase.
             printf("\n\n\n\n                                                  Bem-vindo ao Nexus Number!\n\n");

             Sleep(2000); // Espera 2 segundos antes de limpar e imprimir o próximo menu.

             system("cls");
             printf("\n\n\n\n                                                Escolha o nivel do jogo: \n\n\n");
             printf("                                                       1 - Facil\n\n");
             printf("                                                       2 - Medio\n\n");
             printf("                                                       3 - Dificil\n\n");
             nivelDoJogo = getch();
            
            if(nivelDoJogo == '1'){
                printf("Teste.\n");
            }else if(nivelDoJogo == '2'){
                printf("Teste 2.\n");
            }else if(nivelDoJogo == '3'){
                printf("Teste 3.\n");
            }else {
                //Nada acontece.
            }

             

        } else if(escolhaMenu == '2'){
            exit(0);
        
        } else {
           //Nada acontece caso a escolha não seja 1 ou 2.          
        }
    }

       
    
    return 0;
}

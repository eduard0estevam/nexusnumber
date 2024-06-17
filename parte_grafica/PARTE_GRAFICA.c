#include <stdio.h>
#include <conio.h>
#include <windows.h>

void textcolor (int color)
{
    /*(DEFINIÇÃO DA COR DO TEXTO) HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);*/
}

void exibirMenu(int opcao) {
    char *opcoes[] = {"Opcao 1", "Opcao 2", "Opcao 3", "Sair"};
    int numOpcoes = sizeof(opcoes) / sizeof(char *);

    printf("\n\nMenu:\n");
    for (int i = 0; i < numOpcoes; i++) {
        if (i == opcao) {
            textcolor(12); // 12 é o código para vermelho
            printf("%s\n", opcoes[i]);
            textcolor(7); // 7 é o código para branco
        } else {
            printf("%s\n", opcoes[i]);
        }
    }
}

int main() {
    int opcao = 0;
    int tecla;

    do {
        system("cls"); // Use 'system("cls")' para limpar a tela
        exibirMenu(opcao);

        tecla = getch();
        if (tecla == 72) { // Tecla para cima
            if (opcao > 0) opcao--;
        } else if (tecla == 80) { // Tecla para baixo
            if (opcao < 3) opcao++;
        }
    } while (tecla != 13); // Tecla Enter para selecionar a opção

    printf("\nVocê selecionou a opção %d\n", opcao + 1);

    return 0;
}

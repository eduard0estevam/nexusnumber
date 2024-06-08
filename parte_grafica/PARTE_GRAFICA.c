#include <stdio.h>
#include </include/conio.h>

void exibirMenu(int opcao) {
    char *opcoes[] = {"Opção 1", "Opção 2", "Opção 3", "Sair"};
    int numOpcoes = sizeof(opcoes) / sizeof(char *);

    printf("\n\nMenu:\n");
    for (int i = 0; i < numOpcoes; i++) {
        if (i == opcao) {
            textcolor(RED);
            cprintf("%s\n", opcoes[i]);
            textcolor(WHITE);
        } else {
            printf("%s\n", opcoes[i]);
        }
    }
}

int main() {
    int opcao = 0;
    int tecla;

    do {
        clrscr();
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

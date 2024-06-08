#include <stdio.h>

// Funções para cada nível de dificuldade
void nivelFacil(int *vidas) {



}
void nivelMedio(int *vidas) {



}
void nivelDificil(int *vidas) {



}

// Função principal
int main() {
    char opcaojogo[50];
    
    int vidas = 3;

    printf("*************************************\n");
    printf("*           Nexus Number            *\n");
    printf("*************************************\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Sair\n");
    printf("Escolha uma opcao: \n");
    scanf("%d", &opcao);

    if (opcao == 1) {

        nivelFacil(&vidas);
    } else {

        printf("Saindo do jogo...\n");
    }

    return 0;
}

// Função do nível fácil
void nivelFacil(int *vidas) {
    int resposta;
    int perguntasCorretas = 0;

    printf("Nivel Facil\n");

    // Primeira pergunta
printf("Quanto e 2 + 2? ");
    scanf("%d", &resposta);
    if (resposta == 4) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Segunda pergunta
    printf("Quanto e 5 - 3? ");
    scanf("%d", &resposta);
    if (resposta == 2) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Terceira pergunta
    printf("Quanto é 6 / 2? ");
    scanf("%d", &resposta);
    if (resposta == 3) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Quarta pergunta
    printf("Quanto é 3 * 3? ");
    scanf("%d", &resposta);
    if (resposta == 9) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    if (*vidas > 0 && perguntasCorretas == 4) {
        printf("Parabens! Voce passou para o nivel medio.\n");
        nivelMedio(vidas);
    } else if (*vidas > 0) {
        printf("Voce errou algumas perguntas. Tente novamente.\n");
        nivelFacil(vidas);
    } else {
        printf("Voce perdeu todas as suas vidas. Fim de jogo.\n");
    }
}

// Função do nível médio
void nivelMedio(int *vidas) {
    int resposta;
    int perguntasCorretas = 0;

    printf("Nivel Medio\n");

    // Primeira pergunta
    printf("Quanto é 12 + 8? ");
    scanf("%d", &resposta);
    if (resposta == 20) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Segunda pergunta
    printf("Quanto é 15 - 7? ");
    scanf("%d", &resposta);
    if (resposta == 8) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Terceira pergunta
    printf("Quanto é 14 / 2? ");
    scanf("%d", &resposta);
    if (resposta == 7) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Quarta pergunta
    printf("Quanto é 4 * 5? ");
    scanf("%d", &resposta);
    if (resposta == 20) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    if (*vidas > 0 && perguntasCorretas == 4) {
        printf("Parabens! Voce passou para o nivel dificil.\n");
        nivelDificil(vidas);
    } else if (*vidas > 0) {
        printf("Voce errou algumas perguntas. Tente novamente.\n");
        nivelMedio(vidas);
    } else {
        printf("Voce perdeu todas as suas vidas. Fim de jogo.\n");
    }
}

// Função do nível difícil
void nivelDificil(int *vidas) {
    int resposta;
    int perguntasCorretas = 0;

    printf("Nivel Dificil\n");

    // Primeira pergunta
    printf("Quanto é 23 + 19? ");
    scanf("%d", &resposta);
    if (resposta == 42) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Segunda pergunta
    printf("Quanto é 34 - 18? ");
    scanf("%d", &resposta);
    if (resposta == 16) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Terceira pergunta
    printf("Quanto é 36 / 6? ");
    scanf("%d", &resposta);
    if (resposta == 6) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    // Quarta pergunta
    printf("Quanto é 7 * 8? ");
    scanf("%d", &resposta);
    if (resposta == 56) {
        perguntasCorretas++;
    } else {
        (*vidas)--;
    }

    if (*vidas > 0 && perguntasCorretas == 4) {
        printf("Parabens! Voce completou todos os niveis.\n");
    } else if (*vidas > 0) {
        printf("Voce errou algumas perguntas. Tente novamente.\n");
        nivelDificil(vidas);
    } else {
        printf("Voce perdeu todas as suas vidas. Fim de jogo.\n");
    }
}

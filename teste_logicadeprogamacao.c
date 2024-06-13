#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0)); // para gerar números aleatórios diferentes a cada execução
    int num[4];
    for(int i = 0; i < 4; i++){
        num[i] = rand() % 101;
    }

    // Agora vamos usar os números gerados na equação (x + y * 2) = 3x
    // Vamos substituir y por num[0], por exemplo
    int x = num[1]; // Vamos usar num[1] como nosso valor de x
    int y = num[0]; // Substituindo y por num[0]

    // Agora vamos verificar se a equação é verdadeira com esses valores
    if (x + y * 2 == 3 * x) {
        printf("A equacao (x + y * 2) = 3x eh verdadeira para x = %d e y = %d\n", x, y);
    } else {
        printf("A equacao (x + y * 2) = 3x nao eh verdadeira para x = %d e y = %d\n", x, y);
    }

    return 0;
}


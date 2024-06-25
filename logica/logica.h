#ifndef logica_h
#define logica_h

typedef struct {
    char pergunta[256];
    char resposta[256];
} Questao;

#ifdef __cplusplus
extern "C" {
#endif

void iniciarJogo(char nivel);
int verificarResposta(const char *respostaJogador, const char *respostaCorreta);

#ifdef __cplusplus
}
#endif

#endif /* logica_h */

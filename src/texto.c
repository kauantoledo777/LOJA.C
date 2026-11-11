// texto.c - funcoes para tratar textos
#include <ctype.h>   // tolower
#include "texto.h"

// Copia um texto para outro deixando tudo minusculo
void paraMinusculo(char *origem, char *destino) {
    int i = 0;                                       // posicao atual
    while (origem[i] != '\0') {                      // ate o fim do texto
        destino[i] = tolower((unsigned char)origem[i]); // converte a letra
        i++;                                         // proxima letra
    }
    destino[i] = '\0';                               // finaliza o texto novo
}

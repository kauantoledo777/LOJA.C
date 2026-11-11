// entrada.c - leitura de dados digitados no teclado
#include <stdio.h>   // fgets
#include <stdlib.h>  // atoi, atof
#include <string.h>  // strcspn
#include "entrada.h"

// Le um texto com espacos e remove o "enter" do final
void lerTexto(char *destino, int tamanho) {
    fgets(destino, tamanho, stdin);              // le a linha digitada
    destino[strcspn(destino, "\n")] = '\0';      // troca o "enter" por fim de texto
}

// Le um numero inteiro
int lerInt() {
    char buffer[20];       // guarda o texto digitado
    lerTexto(buffer, 20);  // le como texto
    return atoi(buffer);   // converte texto para inteiro
}

// Le um numero com virgula ou ponto (ex: 49,90 ou 49.90)
float lerFloat() {
    char buffer[20];       // guarda o texto digitado
    int i;                 // contador do for
    lerTexto(buffer, 20);  // le como texto
    for (i = 0; buffer[i] != '\0'; i++) {  // percorre cada letra
        if (buffer[i] == ',') {            // se for virgula...
            buffer[i] = '.';               // ...troca por ponto
        }
    }
    return atof(buffer);   // converte texto para float
}

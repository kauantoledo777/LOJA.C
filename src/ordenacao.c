// ordenacao.c - ordenacao dos produtos (Bubble Sort)
#include <stdio.h>
#include <string.h>  // strcmp
#include "ordenacao.h"
#include "entrada.h"
#include "texto.h"
#include "tabela.h"   // para usar mostrarTabela

// Ordena uma COPIA da lista e mostra em tabela, sem alterar o arquivo
void ordenar(Produto *lista, int total) {
    Produto copia[MAX];   // copia para nao mexer na lista original
    Produto aux;          // auxiliar para trocar de lugar
    char a[50], b[50];    // nomes em minusculo
    int op, i, j, troca;
    printf("1 - Nome (A-Z)\n2 - Nome (Z-A)\n");
    printf("3 - Preco (menor -> maior)\n4 - Preco (maior -> menor)\n");
    printf("Escolha: ");
    op = lerInt();
    if (op < 1 || op > 4) {
        printf("Opcao invalida!\n");
        return;
    }
    for (i = 0; i < total; i++) {              // copia a lista
        copia[i] = lista[i];
    }
    for (i = 0; i < total - 1; i++) {          // Bubble Sort: repeticoes externas
        for (j = 0; j < total - i - 1; j++) {  // compara vizinhos
            troca = 0;                         // comeca sem trocar
            paraMinusculo(copia[j].nome, a);
            paraMinusculo(copia[j + 1].nome, b);
            if (op == 1 && strcmp(a, b) > 0) troca = 1;   // A-Z
            if (op == 2 && strcmp(a, b) < 0) troca = 1;   // Z-A
            if (op == 3 && copia[j].preco > copia[j + 1].preco) troca = 1; // menor -> maior
            if (op == 4 && copia[j].preco < copia[j + 1].preco) troca = 1; // maior -> menor
            if (troca == 1) {                  // troca os dois de lugar
                aux = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = aux;
            }
        }
    }
    mostrarTabela(copia, total);               // mostra a copia ordenada
}

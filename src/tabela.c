// tabela.c - mostra os produtos em formato de tabela
#include <stdio.h>
#include "tabela.h"

// Mostra os produtos em formato de tabela (nao altera o arquivo)
void mostrarTabela(Produto *lista, int total) {
    int i;
    if (total == 0) {
        printf("Nenhum produto para mostrar.\n");
        return;
    }
    printf("\n--------------------------------------------------------------------------------\n");
    printf("%-4s %-18s %-16s %-10s %-5s %-14s\n",
           "ID", "Produto", "Categoria", "Preco(R$)", "Qtd", "Fornecedor");
    printf("--------------------------------------------------------------------------------\n");
    for (i = 0; i < total; i++) {
        printf("%-4d %-18s %-16s %-10.2f %-5d %-14s\n",
               lista[i].id, lista[i].nome, lista[i].categoria,
               lista[i].preco, lista[i].quantidade, lista[i].fornecedor);
    }
    printf("--------------------------------------------------------------------------------\n");
}

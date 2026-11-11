// arquivo.c - leitura e gravacao dos dados em arquivo
#include <stdio.h>   // fopen, fprintf, fscanf, fclose
#include <stdlib.h>  // remove, rename
#include "arquivo.h"

// Salva todos os produtos: grava em arquivo temporario e depois substitui o original
// (tecnica para evitar corrupcao de dados)
void salvar(Produto *lista, int total) {
    FILE *arq = fopen(TEMP, "w");   // abre o temporario para escrita
    int i;                          // contador do for
    if (arq == NULL) {              // se nao conseguiu abrir...
        printf("Erro ao salvar o arquivo!\n");
        return;                     // ...sai da funcao
    }
    for (i = 0; i < total; i++) {   // para cada produto...
        fprintf(arq, "%d;%s;%s;%.2f;%d;%s\n",  // ...grava uma linha separada por ;
                lista[i].id, lista[i].nome, lista[i].categoria,
                lista[i].preco, lista[i].quantidade, lista[i].fornecedor);
    }
    fclose(arq);                    // fecha o temporario
    remove(ARQUIVO);                // apaga o arquivo original
    rename(TEMP, ARQUIVO);          // o temporario vira o original
}

// Cria a tabela inicial com os 4 produtos do enunciado
void criarTabela(Produto *lista, int *total) {
    Produto iniciais[4] = {   // produtos de exemplo
        {1, "Camiseta Basica", "Vestuario",       49.90, 30, "Moda Brasil"},
        {2, "Mouse Optico USB", "Informatica",    59.99, 15, "TecnoShop"},
        {3, "Shampoo 300ml",    "Higiene Pessoal", 22.50, 40, "Beleza Pura"},
        {4, "Cafe 500g",        "Alimentos",      18.00, 25, "Graos do Sul"}
    };
    int i;                            // contador do for
    for (i = 0; i < 4; i++) {         // copia os 4 produtos para a lista
        lista[i] = iniciais[i];
    }
    *total = 4;                       // atualiza a quantidade (usa ponteiro)
    salvar(lista, *total);            // grava no arquivo
    printf("Tabela criada com 4 produtos!\n");
}

// Le o arquivo e preenche o vetor; se o arquivo nao existir, cria a tabela
void carregar(Produto *lista, int *total) {
    FILE *arq = fopen(ARQUIVO, "r");  // abre para leitura
    *total = 0;                       // comeca com zero produtos
    if (arq == NULL) {                // arquivo nao existe...
        criarTabela(lista, total);    // ...cria a tabela inicial
        return;
    }
    // le linha por linha enquanto conseguir ler os 6 campos
    while (*total < MAX &&
           fscanf(arq, "%d;%49[^;];%29[^;];%f;%d;%29[^\n]\n",
                  &lista[*total].id, lista[*total].nome, lista[*total].categoria,
                  &lista[*total].preco, &lista[*total].quantidade,
                  lista[*total].fornecedor) == 6) {
        (*total)++;                   // conta mais um produto
    }
    fclose(arq);                      // fecha o arquivo
}

// Exporta os dados para CSV separado por virgula
void exportarCSV(Produto *lista, int total) {
    FILE *arq = fopen("loja.csv", "w");        // abre/cria o CSV
    int i;
    if (arq == NULL) {
        printf("Erro ao criar o CSV!\n");
        return;
    }
    fprintf(arq, "ID,Produto,Categoria,Preco,Quantidade,Fornecedor\n");  // cabecalho
    for (i = 0; i < total; i++) {
        fprintf(arq, "%d,%s,%s,%.2f,%d,%s\n",
                lista[i].id, lista[i].nome, lista[i].categoria,
                lista[i].preco, lista[i].quantidade, lista[i].fornecedor);
    }
    fclose(arq);
    printf("Arquivo loja.csv criado!\n");
}

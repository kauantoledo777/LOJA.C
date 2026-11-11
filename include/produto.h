// produto.h - define a estrutura Produto e as constantes do projeto
#ifndef PRODUTO_H   // evita incluir este arquivo duas vezes
#define PRODUTO_H

#define MAX 100            // maximo de produtos no vetor
#define ARQUIVO "loja.txt" // arquivo principal (tabela em texto)
#define TEMP "temp.txt"    // arquivo temporario (usado ao salvar)

// Estrutura que representa um produto
typedef struct {
    int id;              // codigo do produto (gerado automaticamente)
    char nome[50];       // nome do produto
    char categoria[30];  // categoria do produto
    float preco;         // preco em reais
    int quantidade;      // quantidade em estoque
    char fornecedor[30]; // nome do fornecedor
} Produto;

#endif

// cadastro.c - inserir, alterar e excluir produtos
#include <stdio.h>
#include <string.h>  // strcpy
#include "cadastro.h"
#include "entrada.h"
#include "tabela.h"
#include "arquivo.h"
#include "busca.h"

// Insere um novo produto
void inserir(Produto *lista, int *total) {
    Produto novo;   // produto que sera cadastrado
    int i;
    if (*total >= MAX) {                       // vetor cheio
        printf("Limite de produtos atingido!\n");
        return;
    }
    printf("Nome: ");
    lerTexto(novo.nome, 50);
    if (buscarPosicaoNome(lista, *total, novo.nome) != -1) {  // verifica duplicata
        printf("Esse produto ja esta cadastrado!\n");
        return;
    }
    printf("Categoria: ");
    lerTexto(novo.categoria, 30);
    printf("Preco: ");
    novo.preco = lerFloat();
    printf("Quantidade: ");
    novo.quantidade = lerInt();
    printf("Fornecedor: ");
    lerTexto(novo.fornecedor, 30);

    novo.id = gerarId(lista, *total);          // ID automatico
    for (i = 0; i < *total; i++) {             // confere se o ID ja existe
        if (lista[i].id == novo.id) {
            printf("ID duplicado!\n");
            return;
        }
    }
    lista[*total] = novo;                      // coloca no fim do vetor
    (*total)++;                                // aumenta a quantidade
    salvar(lista, *total);                     // grava no arquivo
    printf("Produto cadastrado com ID %d!\n", novo.id);
}

// Altera um produto existente
void alterar(Produto *lista, int total) {
    int id, pos, outro;
    char nome[50];
    mostrarTabela(lista, total);
    printf("ID do produto que deseja alterar: ");
    id = lerInt();
    pos = buscarPosicaoId(lista, total, id);   // acha a posicao do ID
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    printf("Novo nome: ");
    lerTexto(nome, 50);
    outro = buscarPosicaoNome(lista, total, nome);  // ve se o nome ja existe
    if (outro != -1 && outro != pos) {         // existe em OUTRO produto
        printf("Ja existe outro produto com esse nome!\n");
        return;
    }
    strcpy(lista[pos].nome, nome);             // copia o novo nome
    printf("Nova categoria: ");
    lerTexto(lista[pos].categoria, 30);
    printf("Novo preco: ");
    lista[pos].preco = lerFloat();
    printf("Nova quantidade: ");
    lista[pos].quantidade = lerInt();
    printf("Novo fornecedor: ");
    lerTexto(lista[pos].fornecedor, 30);
    salvar(lista, total);                      // grava no arquivo
    printf("Produto alterado!\n");
}

// Exclui um produto
void excluir(Produto *lista, int *total) {
    int id, pos, i;
    mostrarTabela(lista, *total);
    printf("ID do produto que deseja excluir: ");
    id = lerInt();
    pos = buscarPosicaoId(lista, *total, id);
    if (pos == -1) {
        printf("Produto nao encontrado!\n");
        return;
    }
    for (i = pos; i < *total - 1; i++) {       // puxa os proximos para tras
        lista[i] = lista[i + 1];
    }
    (*total)--;                                // diminui a quantidade
    salvar(lista, *total);                     // grava no arquivo
    printf("Produto excluido!\n");
}

// busca.c - buscas e geracao de ID
#include <stdio.h>
#include <string.h>  // strcmp, strstr
#include "busca.h"
#include "entrada.h"
#include "texto.h"
#include "tabela.h"   // para usar mostrarTabela

// Gera o proximo ID (maior ID existente + 1)
int gerarId(Produto *lista, int total) {
    int maior = 0;                    // guarda o maior ID
    int i;
    for (i = 0; i < total; i++) {
        if (lista[i].id > maior) {    // achou um ID maior
            maior = lista[i].id;
        }
    }
    return maior + 1;                 // proximo ID
}

// Procura produto pelo nome (sem diferenciar maiuscula). Retorna a posicao ou -1
int buscarPosicaoNome(Produto *lista, int total, char *nome) {
    char a[50], b[50];                // textos em minusculo
    int i;
    paraMinusculo(nome, a);           // nome digitado em minusculo
    for (i = 0; i < total; i++) {
        paraMinusculo(lista[i].nome, b);  // nome do produto em minusculo
        if (strcmp(a, b) == 0) {      // se forem iguais...
            return i;                 // ...devolve a posicao
        }
    }
    return -1;                        // nao encontrou
}

// Procura produto pelo ID. Retorna a posicao ou -1
int buscarPosicaoId(Produto *lista, int total, int id) {
    int i;
    for (i = 0; i < total; i++) {
        if (lista[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Busca por nome (tipo = 1) ou por categoria (tipo = 2), sem diferenciar maiuscula
void buscar(Produto *lista, int total, int tipo) {
    Produto achados[MAX];    // guarda os produtos encontrados
    int qtd = 0;             // quantos foram encontrados
    char texto[50], campo[50], busca[50];
    int i;
    printf("Digite o texto da busca: ");
    lerTexto(texto, 50);
    paraMinusculo(texto, busca);               // busca em minusculo
    for (i = 0; i < total; i++) {
        if (tipo == 1) {
            paraMinusculo(lista[i].nome, campo);       // compara com o nome
        } else {
            paraMinusculo(lista[i].categoria, campo);  // compara com a categoria
        }
        if (strstr(campo, busca) != NULL) {    // se contem o texto buscado
            achados[qtd] = lista[i];           // guarda o produto
            qtd++;
        }
    }
    mostrarTabela(achados, qtd);               // mostra os encontrados
}

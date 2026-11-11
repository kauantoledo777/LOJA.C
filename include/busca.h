// busca.h - buscas e geracao de ID
#ifndef BUSCA_H
#define BUSCA_H

#include "produto.h"

int gerarId(Produto *lista, int total);                          // proximo ID
int buscarPosicaoNome(Produto *lista, int total, char *nome);    // posicao pelo nome ou -1
int buscarPosicaoId(Produto *lista, int total, int id);          // posicao pelo ID ou -1
void buscar(Produto *lista, int total, int tipo);                // 1 = nome, 2 = categoria

#endif

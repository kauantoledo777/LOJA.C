// cadastro.h - inserir, alterar e excluir produtos
#ifndef CADASTRO_H
#define CADASTRO_H

#include "produto.h"

void inserir(Produto *lista, int *total);   // cadastra novo produto
void alterar(Produto *lista, int total);    // altera produto pelo ID
void excluir(Produto *lista, int *total);   // exclui produto pelo ID

#endif

// arquivo.h - leitura e gravacao dos dados em arquivo
#ifndef ARQUIVO_H
#define ARQUIVO_H
#include "produto.h"
void salvar(Produto *lista, int total);          // grava tudo (via arquivo temporario)
void criarTabela(Produto *lista, int *total);    // cria a tabela inicial com 4 produtos
void carregar(Produto *lista, int *total);       // le o arquivo para o vetor
void exportarCSV(Produto *lista, int total);     // exporta para CSV com virgula
#endif

// main.c - programa principal (menu)
#include <stdio.h>
#include <locale.h>   // setlocale
#include "produto.h"
#include "entrada.h"
#include "arquivo.h"
#include "tabela.h"
#include "cadastro.h"
#include "busca.h"
#include "ordenacao.h"

int main() {
    Produto lista[MAX];   // vetor de estruturas
    int total;            // quantidade de produtos cadastrados
    int opcao;            // opcao do menu

    setlocale(LC_ALL, "Portuguese");  // permite acentos
    carregar(lista, &total);          // le o arquivo (ou cria se nao existir)

    do {
        printf("\n===== CADASTRO DA LOJA =====\n");
        printf("1 - Criar tabela inicial\n");
        printf("2 - Listar\n");
        printf("3 - Inserir\n");
        printf("4 - Alterar\n");
        printf("5 - Excluir\n");
        printf("6 - Buscar por nome\n");
        printf("7 - Buscar por categoria\n");
        printf("8 - Ordenar\n");
        printf("9 - Exportar CSV\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        opcao = lerInt();

        switch (opcao) {   // chama a funcao escolhida
            case 1: criarTabela(lista, &total); break;
            case 2: mostrarTabela(lista, total); break;
            case 3: inserir(lista, &total); break;
            case 4: alterar(lista, total); break;
            case 5: excluir(lista, &total); break;
            case 6: buscar(lista, total, 1); break;
            case 7: buscar(lista, total, 2); break;
            case 8: ordenar(lista, total); break;
            case 9: exportarCSV(lista, total); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);  // repete ate escolher sair

    return 0;
}

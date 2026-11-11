/*
 * ATIVIDADE 04 - CADASTRO DE PRODUTOS
 */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 500
#define TAM_NOME 80
#define TAM_CATEGORIA 60
#define TAM_FORNECEDOR 80
#define ARQUIVO "produtos.txt"
#define TEMPORARIO "produtos.tmp"
#define CSV "produtos.csv"

/* Linha da tabela da loja. */
typedef struct {
    int id;
    char nome[TAM_NOME];
    char categoria[TAM_CATEGORIA];
    double preco;
    int quantidade;
    char fornecedor[TAM_FORNECEDOR];
} Produto;

/* Vetor de estruturas */
Produto lista[MAX_PRODUTOS];
int total = 0;
int proximoId = 1;

/* Le uma linha inteira, para evitar problemas de scanf com \n */
void lerTexto(const char *mensagem, char *destino, size_t tamanho) {
    size_t i;
    int c;
    for (;;) {
        printf("%s", mensagem);
        if (fgets(destino, (int)tamanho, stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(0);
        }
        i = strlen(destino);
        if (i && destino[i - 1] == '\n') {
            destino[i - 1] = '\0';
        } else {
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
        /* O caractere '|' e reservado como separador no arquivo TXT */
        if (strchr(destino, '|') != NULL) {
            printf("Nao utilize o caractere | nos campos.\n");
        } else if (destino[0] == '\0') {
            printf("O campo nao pode ficar vazio.\n");
        } else {
            return;
        }
    }
}

/* Converte entrada numerica com validacao e aceita ponto ou virgula decimal */
double lerNumero(const char *mensagem, double minimo, double maximo) {
    char linha[120];
    char *fim;
    double valor;
    size_t i;
    for (;;) {
        lerTexto(mensagem, linha, sizeof(linha));
        for (i = 0; linha[i] != '\0'; i++) {
            if (linha[i] == ',') linha[i] = '.';
        }
        valor = strtod(linha, &fim);
        while (isspace((unsigned char)*fim)) fim++;
        if (fim != linha && *fim == '\0' && valor >= minimo && valor <= maximo) {
            return valor;
        }
        printf("Numero invalido. Tente novamente.\n");
    }
}

int lerInteiro(const char *mensagem, int minimo, int maximo) {
    char linha[100], extra;
    int valor;
    for (;;) {
        lerTexto(mensagem, linha, sizeof(linha));
        if (sscanf(linha, " %d %c", &valor, &extra) == 1 &&
            valor >= minimo && valor <= maximo) return valor;
        printf("Digite um numero inteiro valido.\n");
    }
}

/* Comparacao case-insensitive. */
int compararTexto(const char *a, const char *b) {
    while (*a && *b) {
        int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) return ca - cb;
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

/* localiza um produto pelo ID e devolve o indice ou -1 */
int indicePorId(int id) {
    int i;
    for (i = 0; i < total; i++) {
        if (lista[i].id == id) return i;
    }
    return -1;
}

/* Nao permite dois produtos com o mesmo nome e ignora caixa alta */
int nomeJaExiste(const char *nome, int idIgnorado) {
    int i;
    for (i = 0; i < total; i++) {
        if (lista[i].id != idIgnorado && compararTexto(lista[i].nome, nome) == 0)
            return 1;
    }
    return 0;
}

/* Grava o vetor em um arquivo temporario e depois substitui o original. */
int salvarProdutos(void) {
    FILE *arquivo = fopen(TEMPORARIO, "w");
    int i;
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        return 0;
    }
    for (i = 0; i < total; i++) {
        Produto *p = &lista[i]; /* Exemplo de uso de ponteiro */
        if (fprintf(arquivo, "%d|%s|%s|%.2f|%d|%s\n",
            p->id, p->nome, p->categoria, p->preco,
            p->quantidade, p->fornecedor) < 0) {
            fclose(arquivo);
            remove(TEMPORARIO);
            printf("Erro durante a escrita dos dados.\n");
            return 0;
        }
    }
    if (fclose(arquivo) != 0) {
        printf("Erro ao finalizar o arquivo temporario.\n");
        return 0;
    }
    /* Substitui o arquivo original pelo arquivo temporario */
    if (rename(TEMPORARIO, ARQUIVO) != 0) {
        printf("Erro ao substituir o arquivo de dados.\n");
        return 0;
    }
    return 1;
}

/* Insere os quatro exemplos da atividade quando nao ha arquivo salvo */
void criarExemplos(void) {
    Produto iniciais[] = {
        {1, "Camiseta Basica", "Vestuario", 49.90, 30, "Moda Brasil"},
        {2, "Mouse Optico USB", "Informatica", 59.99, 15, "TecnoShop"},
        {3, "Shampoo 300ml", "Higiene Pessoal", 22.50, 40, "Beleza Pura"},
        {4, "Cafe 500g", "Alimentos", 18.00, 25, "Graos do Sul"}
    };
    int i;
    total = (int)(sizeof(iniciais) / sizeof(iniciais[0]));
    for (i = 0; i < total; i++) lista[i] = iniciais[i];
    proximoId = 5;
    salvarProdutos();
}

/* Carrega as linhas do TXT; ignora linhas com formato incorreto */
void carregarProdutos(void) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    char linha[512];
    Produto p;
    if (arquivo == NULL) {
        criarExemplos();
        return;
    }
    total = 0;
    proximoId = 1;
    while (fgets(linha, sizeof(linha), arquivo) != NULL && total < MAX_PRODUTOS) {
        if (sscanf(linha, "%d|%79[^|]|%59[^|]|%lf|%d|%79[^\n]",
                   &p.id, p.nome, p.categoria, &p.preco,
                   &p.quantidade, p.fornecedor) == 6 &&
            p.id > 0 && p.preco >= 0 && p.quantidade >= 0 &&
            indicePorId(p.id) == -1 && !nomeJaExiste(p.nome, -1)) {
            lista[total++] = p;
            if (p.id >= proximoId) proximoId = p.id + 1;
        }
    }
    fclose(arquivo);
}

/* Imprime os produtos em formato de tabela. */
void cabecalho(void) {
    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("%-4s | %-23s | %-18s | %10s | %10s | %-20s\n",
           "ID", "Produto", "Categoria", "Preco(R$)", "Quantidade", "Fornecedor");
    printf("----------------------------------------------------------------------------------------------------------\n");
}
void imprimirProduto(const Produto *p) {
    printf("%-4d | %-23.23s | %-18.18s | %10.2f | %10d | %-20.20s\n",
           p->id, p->nome, p->categoria, p->preco,
           p->quantidade, p->fornecedor);
}
void listarProdutos(void) {
    int i;
    if (total == 0) { printf("Nenhum produto cadastrado.\n"); return; }
    cabecalho();
    for (i = 0; i < total; i++) imprimirProduto(&lista[i]);
    printf("\nTotal de produtos: %d\n", total);
}

/* Insere um novo produto com ID automatico, sem repeticao de nome. */
void cadastrarProduto(void) {
    Produto novo;
    if (total >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    do {
        lerTexto("Nome: ", novo.nome, sizeof(novo.nome));
        if (nomeJaExiste(novo.nome, -1))
            printf("Ja existe um produto com esse nome.\n");
        else break;
    } while (1);
    lerTexto("Categoria: ", novo.categoria, sizeof(novo.categoria));
    novo.preco = lerNumero("Preco: ", 0, 1000000000);
    novo.quantidade = lerInteiro("Quantidade: ", 0, 1000000000);
    lerTexto("Fornecedor: ", novo.fornecedor, sizeof(novo.fornecedor));
    novo.id = proximoId++;
    lista[total++] = novo;
    if (salvarProdutos()) printf("Produto cadastrado! ID: %d\n", novo.id);
}

/* Busca parcial pelo nome ou pela categoria, sem diferenciar letras maiusculas. */
int contemTexto(const char *texto, const char *busca) {
    size_t i, j, n = strlen(texto), m = strlen(busca);
    if (m > n) return 0;
    for (i = 0; i + m <= n; i++) {
        for (j = 0; j < m; j++) {
            if (tolower((unsigned char)texto[i+j]) !=
                tolower((unsigned char)busca[j])) break;
        }
        if (j == m) return 1;
    }
    return 0;
}
void buscarProdutos(void) {
    int opcao, i, encontrados = 0;
    char termo[100];
    opcao = lerInteiro("Buscar por: 1-Nome / 2-Categoria: ", 1, 2);
    lerTexto("Termo de busca: ", termo, sizeof(termo));
    for (i = 0; i < total; i++) {
        const char *campo = (opcao == 1) ? lista[i].nome : lista[i].categoria;
        if (contemTexto(campo, termo)) {
            if (encontrados == 0) cabecalho();
            imprimirProduto(&lista[i]);
            encontrados++;
        }
    }
    if (!encontrados) printf("Nenhum produto encontrado.\n");
    else printf("Encontrados: %d\n", encontrados);
}

/* Altera todos os campos, mantendo o ID original. */
void alterarProduto(void) {
    int id = lerInteiro("ID do produto a alterar: ", 1, 2000000000);
    int indice = indicePorId(id);
    Produto atualizado;
    if (indice < 0) { printf("ID nao encontrado.\n"); return; }
    imprimirProduto(&lista[indice]);
    atualizado = lista[indice];
    do {
        lerTexto("Novo nome: ", atualizado.nome, sizeof(atualizado.nome));
        if (nomeJaExiste(atualizado.nome, id))
            printf("Outro produto ja utiliza esse nome.\n");
        else break;
    } while (1);
    lerTexto("Nova categoria: ", atualizado.categoria, sizeof(atualizado.categoria));
    atualizado.preco = lerNumero("Novo preco: ", 0, 1000000000);
    atualizado.quantidade = lerInteiro("Nova quantidade: ", 0, 1000000000);
    lerTexto("Novo fornecedor: ", atualizado.fornecedor, sizeof(atualizado.fornecedor));
    lista[indice] = atualizado;
    if (salvarProdutos()) printf("Produto alterado com sucesso.\n");
}

/* Exclui do vetor deslocando os elementos seguintes. */
void excluirProduto(void) {
    int id = lerInteiro("ID do produto a excluir: ", 1, 2000000000);
    int indice = indicePorId(id), i;
    char resposta[10];
    if (indice < 0) { printf("ID nao encontrado.\n"); return; }
    imprimirProduto(&lista[indice]);
    lerTexto("Confirmar exclusao? (s/n): ", resposta, sizeof(resposta));
    if (tolower((unsigned char)resposta[0]) != 's') {
        printf("Exclusao cancelada.\n");
        return;
    }
    for (i = indice; i < total - 1; i++) lista[i] = lista[i + 1];
    total--;
    if (salvarProdutos()) printf("Produto excluido com sucesso.\n");
}

/* Bubble Sort, a tabela continua na ordem */
void ordenarProdutos(void) {
    int modo, i, j;
    Produto copia[MAX_PRODUTOS];
    Produto auxiliar;
    if (total == 0) { printf("Nao ha produtos para ordenar.\n"); return; }
    printf("1 - Nome A-Z\n");
    printf("2 - Nome Z-A\n");
    printf("3 - Preco menor para maior\n");
    printf("4 - Preco maior para menor\n");
    modo = lerInteiro("Escolha: ", 1, 4);
    for (i = 0; i < total; i++) copia[i] = lista[i];
    for (i = 0; i < total - 1; i++) {
        int houveTroca = 0;
        for (j = 0; j < total - 1 - i; j++) {
            int trocar = 0;
            if (modo == 1) trocar = compararTexto(copia[j].nome, copia[j+1].nome) > 0;
            if (modo == 2) trocar = compararTexto(copia[j].nome, copia[j+1].nome) < 0;
            if (modo == 3) trocar = copia[j].preco > copia[j+1].preco;
            if (modo == 4) trocar = copia[j].preco < copia[j+1].preco;
            if (trocar) {
                auxiliar = copia[j];
                copia[j] = copia[j+1];
                copia[j+1] = auxiliar;
                houveTroca = 1;
            }
        }
        if (!houveTroca) break;
    }
    cabecalho();
    for (i = 0; i < total; i++) imprimirProduto(&copia[i]);
    printf("(A ordenacao foi apenas na tela; arquivo original preservado.)\n");
}

/* Escapa aspas para que nomes com virgulas continuem validos no CSV */
void campoCSV(FILE *arquivo, const char *texto) {
    const char *p = texto;
    fputc('"', arquivo);
    while (*p) {
        if (*p == '"') fputc('"', arquivo);
        fputc(*p++, arquivo);
    }
    fputc('"', arquivo);
}
void exportarCSV(void) {
    FILE *arquivo = fopen(CSV, "w");
    int i;
    if (!arquivo) { printf("Nao foi possivel criar o CSV.\n"); return; }
    fputs("ID,Produto,Categoria,Preco,Quantidade,Fornecedor\n", arquivo);
    for (i = 0; i < total; i++) {
        Produto *p = &lista[i];
        fprintf(arquivo, "%d,", p->id);
        campoCSV(arquivo, p->nome); fputc(',', arquivo);
        campoCSV(arquivo, p->categoria);
        fprintf(arquivo, ",%.2f,%d,", p->preco, p->quantidade);
        campoCSV(arquivo, p->fornecedor); fputc('\n', arquivo);
    }
    if (fclose(arquivo) == 0) printf("Arquivo %s gerado com sucesso.\n", CSV);
    else printf("Erro ao finalizar CSV.\n");
}

/* Menu principal: cada opcao chama uma funcao independente. */
int main(void) {
    int opcao;
    carregarProdutos();
    do {
        printf("\n========== CADASTRO DE LOJA ==========\n");
        printf("1 - Listar produtos\n");
        printf("2 - Cadastrar produto\n");
        printf("3 - Alterar produto\n");
        printf("4 - Excluir produto\n");
        printf("5 - Buscar por nome ou categoria\n");
        printf("6 - Ordenar produtos (Bubble Sort)\n");
        printf("7 - Exportar CSV\n");
        printf("0 - Sair\n");
        opcao = lerInteiro("Opcao: ", 0, 7);
        switch (opcao) {
            case 1: listarProdutos(); break;
            case 2: cadastrarProduto(); break;
            case 3: alterarProduto(); break;
            case 4: excluirProduto(); break;
            case 5: buscarProdutos(); break;
            case 6: ordenarProdutos(); break;
            case 7: exportarCSV(); break;
            case 0: printf("Programa encerrado.\n"); break;
        }
    } while (opcao != 0);
    return 0;
}
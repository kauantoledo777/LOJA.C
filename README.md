# Cadastro de Loja em C

Programa em C para cadastro de produtos de uma loja, feito como atividade
da faculdade (ADS). Usa struct, ponteiros, arquivos de texto e Bubble Sort.

## Funcionalidades

- Criar tabela inicial de produtos
- Listar em formato de tabela
- Inserir (ID automatico e sem produtos duplicados)
- Alterar e excluir por ID
- Buscar por nome e por categoria (sem diferenciar maiuscula/minuscula)
- Ordenar por nome (A-Z / Z-A) e por preco (menor/maior)
- Exportar os dados para CSV

## Estrutura

```
LOJA.C/
├── include/      # arquivos .h (lista das funcoes)
├── src/          # arquivos .c (codigo das funcoes)
├── Makefile
├── README.md
└── .gitignore
```

## O que cada arquivo faz

| Arquivo | Responsabilidade |
|---|---|
| `main.c` | menu principal do programa |
| `produto.h` | estrutura `Produto` e constantes |
| `entrada.c / .h` | leitura de dados digitados (texto, inteiro, decimal) |
| `texto.c / .h` | tratamento de texto (converter para minusculo) |
| `arquivo.c / .h` | salvar, carregar e exportar CSV |
| `cadastro.c / .h` | inserir, alterar e excluir produtos |
| `busca.c / .h` | gerar ID e buscar por nome ou categoria |
| `ordenacao.c / .h` | ordenar com Bubble Sort |
| `tabela.c / .h` | mostrar os produtos em formato de tabela |

## Como compilar e executar

```bash
gcc -Iinclude src/*.c -o loja
./loja
```

Ou, se tiver o `make` instalado:

```bash
make
./loja
```

## Tecnologias

- Linguagem C (gcc)
- Git e GitHub

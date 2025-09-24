#include <stdio.h>   // Biblioteca para funções de entrada e saída (printf, scanf)
#include <string.h>  // Biblioteca para manipulação de strings (strcmp, etc.)
#include <stdlib.h>  // Biblioteca padrão (usada aqui para organização geral)

#define MAX_ITENS 10 // Define a capacidade máxima da mochila (10 itens)

// ----------------------------------------------------------
// Definição da struct Item
// Cada Item terá: nome, tipo (arma, munição, cura...) e quantidade.
// ----------------------------------------------------------
typedef struct {
    char nome[30];    // Nome do item (ex: "Rifle", "Kit Médico")
    char tipo[20];    // Tipo do item (ex: "Arma", "Munição", "Cura")
    int quantidade;   // Quantidade de unidades do item
} Item;

// ----------------------------------------------------------
// Variáveis globais
// ----------------------------------------------------------
Item mochila[MAX_ITENS]; // Vetor que armazena os itens cadastrados na mochila
int totalItens = 0;      // Quantidade atual de itens cadastrados na mochila

// ----------------------------------------------------------
// Função: inserirItem()
// Cadastra um novo item na mochila, desde que haja espaço.
// ----------------------------------------------------------
void inserirItem() {
    // Verifica se já atingiu o limite máximo de itens
    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    // Estrutura temporária para receber os dados do novo item
    Item novo;

    printf("\n===== Cadastro de Novo Item =====\n");

    // Lê o nome do item (usa %[^\n] para aceitar espaços)
    printf("Nome do item: ");
    scanf(" %[^\n]", novo.nome);

    // Lê o tipo do item
    printf("Tipo do item (arma, munição, cura...): ");
    scanf(" %[^\n]", novo.tipo);

    // Lê a quantidade
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    // Adiciona o novo item no vetor da mochila
    mochila[totalItens] = novo;
    totalItens++; // Incrementa o contador de itens cadastrados

    printf("\nItem adicionado com sucesso!\n");
}

// ----------------------------------------------------------
// Função: removerItem()
// Remove um item da mochila com base no nome informado.
// ----------------------------------------------------------
void removerItem() {
    char nomeRemover[30]; // String para receber o nome do item a ser removido

    printf("\n===== Remoção de Item =====\n");
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nomeRemover);

    int encontrado = -1; // Variável para armazenar a posição do item encontrado

    // Percorre o vetor de itens para procurar pelo nome
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) { // strcmp retorna 0 se as strings forem iguais
            encontrado = i; // Armazena o índice do item encontrado
            break;
        }
    }

    // Se o item foi encontrado
    if (encontrado != -1) {
        // "Remove" o item deslocando todos os seguintes uma posição para trás
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--; // Decrementa o número total de itens
        printf("\nItem removido com sucesso!\n");
    } else {
        printf("\nItem não encontrado.\n");
    }
}

// ----------------------------------------------------------
// Função: listarItens()
// Lista todos os itens atualmente cadastrados na mochila.
// ----------------------------------------------------------
void listarItens() {
    printf("\n===== Itens na Mochila =====\n");

    // Caso a mochila esteja vazia
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
    } else {
        // Percorre e imprime cada item
        for (int i = 0; i < totalItens; i++) {
            printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
                   i + 1,                 // Número do item (índice + 1)
                   mochila[i].nome,       // Nome do item
                   mochila[i].tipo,       // Tipo do item
                   mochila[i].quantidade);// Quantidade do item
        }
    }
}

// ----------------------------------------------------------
// Função: buscarItem()
// Faz uma busca sequencial na mochila pelo nome do item.
// ----------------------------------------------------------
void buscarItem() {
    char nomeBusca[30]; // Nome do item que será buscado

    printf("\n====== Buscar Item ======\n");
    printf("Digite o nome do item para buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0; // Flag para verificar se encontrou o item

    // Percorre todos os itens
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) { // Compara os nomes
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            encontrado = 1; // Marca como encontrado
            break; // Sai do loop pois já achou
        }
    }

    // Caso não tenha encontrado
    if (!encontrado) {
        printf("\nItem não encontrado.\n");
    }
}

// ----------------------------------------------------------
// Função principal: main()
// Exibe um menu interativo para o usuário.
// Permite cadastrar, remover, listar e buscar itens.
// ----------------------------------------------------------
int main() {
    int opcao; // Armazena a opção escolhida pelo usuário

    do {
        // Exibe o menu
        printf("\n=========================================\n");
        printf("MOCHILA DE SOBREVIVÊNCIA - CÓDIGO DA ILHA\n");
        printf("=========================================\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Executa a função correspondente à opção
        switch (opcao) {
            case 1:
                inserirItem();  // Cadastra novo item
                listarItens();  // Lista itens após cadastro
                break;
            case 2:
                removerItem();  // Remove item existente
                listarItens();  // Lista itens após remoção
                break;
            case 3:
                listarItens();  // Lista todos os itens
                break;
            case 4:
                buscarItem();   // Busca item específico
                break;
            case 0:
                printf("\nSaindo do sistema...\n"); // Encerra o programa
                break;
            default:
                printf("\nOpção inválida.\n"); // Caso digite número fora das opções
        }

    } while (opcao != 0); // Continua exibindo o menu até o usuário escolher sair

    return 0; // Fim do programa
}

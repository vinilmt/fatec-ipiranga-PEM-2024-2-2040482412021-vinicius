/*--------------------------------------------------------------------------*
 * Disciplina: Programaçao Estruturada e Modular                            *
 *          Prof. Carlos Veríssimo                              	        *
 *--------------------------------------------------------------------------*
 * Objetivo do Programa: Loja de Produtos Eletrônicos utilizando Ponteiros  *
 * Data - 08/11/2024                                         		        *
 * Autor: Vinicius Leon Melo Tavares                		                *
 *--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRODUCTS_CAPACITY 100   // Limite máximo de produtos
#define NAME_CAPACITY 30        // Tamanho máximo do nome

typedef struct {
    int id;                     // ID único para cada produto
    char name[NAME_CAPACITY];   // Nome do produto
    int amount;                 // Quantidade em estoque
    double price;               // Preço do produto
} Product;

typedef struct {
    Product slice[PRODUCTS_CAPACITY];   // Array de produtos
    int length;                         // Tamanho ocupado do array
} Stock;

void insertProduct(Stock *stock) {
    if (stock->length >= PRODUCTS_CAPACITY) {   // Verifica se o estoque está cheio
        printf("O estoque está cheio\n");
        return;
    }

    
    printf("Digite o ID do produto: ");
    while (scanf("%i", &stock->slice[stock->length].id) != 1)    // Validação do ID do produto
        while (getchar() != '\n');    // Limpa o buffer, pois as entradas permanecem lá

    
    for (int i = 0; i < stock->length; i++) {    // Verifica se o ID já existe no estoque
        if (stock->slice[i].id == stock->slice[stock->length].id) {
            printf("Esse ID já existe\n");
            return;
        }
    }

    // Validação do nome do produto (com espaços) e trunca o texto para o tamanho máximo
    printf("Digite o nome do produto (limite de %i caractéres): ", NAME_CAPACITY);
    while (fgets(stock->slice[stock->length].name, NAME_CAPACITY, stdin) == NULL || stock->slice[stock->length].name[0] == '\n'); 
    stock->slice[stock->length].name[strcspn(stock->slice[stock->length].name, "\n")] = '\0';    // Remove quebra de linha que normalmente é lida pelo fgets
    while (getchar() != '\n');    // Limpa o buffer, pois o remanescente do texto permanece lá

    printf("Digite a quantidade: ");
    while (scanf("%i", &stock->slice[stock->length].amount) != 1 || stock->slice[stock->length].amount < 0)    // Validação da quantidade
        while (getchar() != '\n');

    printf("Digite o preço do produto: ");
    while (scanf("%lf", &stock->slice[stock->length].price) != 1 || stock->slice[stock->length].price < 0.0)    // Validação do preço
        while (getchar() != '\n');

    stock->length++;   // Incrementa o tamanho ocupado pelo array

    printf("Produto inserido com sucesso\n");
}

void consultProduct(Stock *stock) {
    int id;
    printf("Digite o ID do produto: ");
    while (scanf("%i", &id) != 1)    // Validação do ID do produto
        while (getchar() != '\n');

    int target_index = -1;
    for (int i = 0; i < stock->length; i++) {   //  Armazenando o índice do produto
        if (id == stock->slice[i].id) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {   // Se o produto não foi encontrado, interrompe a função
        printf("Produto não encontrado.\n");
        return;
    }

    printf("\n| Nome: %s\n| Quantidade em estoque: %i\n| Preço: %.2lf\n",
        stock->slice[target_index].name,
        stock->slice[target_index].amount,
        stock->slice[target_index].price);
}

void updateProduct(Stock *stock) {
    int id;
    printf("Digite o ID do produto: ");
    while (scanf("%i", &id) != 1)   // Validação do ID do produto
        while (getchar() != '\n');

    int target_index = -1;
    for (int i = 0; i < stock->length; i++) {    // Armazenando o índice do produto
        if (id == stock->slice[i].id) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {    // Se o produto não foi encontrado, interrompe a função
        printf("Produto não encontrado\n");
        return;
    }

    int update_name_flag;
    printf("Digite 1 para mudar o nome (senão digite 0): ");    // Validação da opção
    while (scanf("%i", &update_name_flag) != 1 || update_name_flag != 0 && update_name_flag != 1)
        while (getchar() != '\n');

    if (update_name_flag) {    // Se o usuário deseja mudar o nome
        // Validação do nome do produto
        printf("Digite o novo nome do produto (limite de %i caractéres): ", NAME_CAPACITY);
        while (fgets(stock->slice[stock->length].name, NAME_CAPACITY, stdin) == NULL || stock->slice[stock->length].name[0] == '\n');
        stock->slice[stock->length].name[strcspn(stock->slice[stock->length].name, "\n")] = '\0';
        while (getchar() != '\n');

        printf("O nome do produto foi alterado com sucesso\n");
    }

    int update_amount_flag;
    printf("Digite 1 para mudar a quantidade em estoque (senão digite 0): ");
    while (scanf("%i", &update_amount_flag) != 1 || update_amount_flag != 0 && update_amount_flag != 1)
        while (getchar() != '\n');
    
    if (update_amount_flag) {
        printf("Digite a nova quantidade em estoque: ");
        while (scanf("%i", &stock->slice[stock->length].amount) != 1 || stock->slice[stock->length].amount < 0)    // Validação da quantidade
            while (getchar() != '\n');

        printf("A quantidade em estoque foi alterada com sucesso\n");
    }

    int update_price_flag;
    printf("Digite 1 para mudar o preço do produto (senão digite 0): ");
    while (scanf("%i", &update_price_flag) != 1 || update_price_flag != 0 && update_price_flag != 1)
        while (getchar() != '\n');

    if (update_price_flag) {
        printf("Digite o novo preço do produto: ");
        while (scanf("%lf", &stock->slice[stock->length].price) != 1 || stock->slice[stock->length].amount < 0.0)    // Validação do preço
            while (getchar() != '\n');

        printf("O preço do produto foi alterado com sucesso\n");
    }

    if (!(update_name_flag || update_amount_flag || update_price_flag)) {    //  Se o usuário não alterou nada 
        printf("O produto não foi alterado\n");
    }
}

void removeProduct(Stock *stock) {
    int id;
    printf("Digite o ID do produto: ");
    while (scanf("%i", &id) != 1)    // Validação do ID do produto
        while (getchar() != '\n');

    int target_index = -1;
    for (int i = 0; i < stock->length; i++) {    // Armazenando o índice do produto
        if (id == stock->slice[i].id) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {    // Se o produto não foi encontrado, interrompe a função
        printf("Produto não encontrado\n");
        return;
    }

    printf("O produto \"%s\" foi removido com sucesso\n", stock->slice[target_index].name);

    for (int i = target_index; i < stock->length - 1; i++) {    // Deslocando os produtos para a esquerda
        stock->slice[i] = stock->slice[i + 1];
    }
    stock->length--;   // Decrementa o tamanho do array
                       // A duplicata do último produto permanece, pois não há necessidade de zerar já que não pode ser acessado
}

void sellProduct(Stock *stock) {
    int id;
    printf("Digite o ID do produto: ");
    while (scanf("%i", &id) != 1)    // Validação do ID do produto
        while (getchar() != '\n');

    int target_index = -1;
    for (int i = 0; i < stock->length; i++) {    // Armazenando o índice do produto
        if (id == stock->slice[i].id) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {    // Se o produto não foi encontrado, interrompe a função
        printf("Produto não encontrado\n");
        return;
    }

    int amount;
    printf("Digite a quantidade a ser vendida: ");    // Validação da quantidade
    while (scanf("%i", &amount) != 1 || amount < 0)
        while (getchar() != '\n');

    if (amount > stock->slice[target_index].amount) {    // Se a quantidade solicitada for maior que a disponível
        printf("A quantidade solicitada não está disponível\n");
        return;
    }

    printf("Venda de \"%s\" realizada com sucesso\n\n", stock->slice[target_index].name);
    printf("| Quantidade restante no estoque: %i -> %i\n", stock->slice[target_index].amount, stock->slice[target_index].amount - amount);
    printf("| Valor pago: R$ %.2lf\n", stock->slice[target_index].price * amount);

    stock->slice[target_index].amount -= amount;    // Atualizando a quantidade em estoque
}

int main() {
    Stock stock = {0};
    
    int option;
    do {    // Loop principal
        printf("\n----- Menu Loja de Eletrônicos -----\n");
        printf("1. Inserir Produto\n");
        printf("2. Consultar Produto\n");
        printf("3. Atualizar Produto\n");
        printf("4. Remover Produto\n");
        printf("5. Vender Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");

        while (scanf("%i", &option) != 1 || option < 0 || option > 5)    // Validação da opção
            while (getchar() != '\n');
        
        switch (option) {    // Chama as opções do menu
            case 1:
                insertProduct(&stock);
                break;
            case 2:
                consultProduct(&stock);
                break;
            case 3:
                updateProduct(&stock);
                break;
            case 4:
                removeProduct(&stock);
                break;
            case 5:
                sellProduct(&stock);
                break;
            case 0:
                break;
            default:
                printf("Mensagem que deveria ser inalcançável\n");
                break;
        }
    } while (option != 0);
    
    return 0;
}

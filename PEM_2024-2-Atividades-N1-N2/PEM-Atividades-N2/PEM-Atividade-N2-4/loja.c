#include <stdio.h>
#include <string.h>

#define PRODUCTS_CAPACITY 100
#define NAME_CAPACITY 50
#define DESCRIPTION_CAPACITY 100

typedef struct {
    int id;
    char name[NAME_CAPACITY];
    char description[DESCRIPTION_CAPACITY];
    float price;
    int amount;
} Product;

void insertProduct(Product* products, int* len) {
    if (*len >= PRODUCTS_CAPACITY) {
        printf("Limite de produtos atingido!\n");
        return;
    }
    Product newProduct;
    newProduct.id = *len + 1;

    printf("Nome do Produto: ");
    getchar();
    fgets(newProduct.name, NAME_CAPACITY, stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = '\0';

    printf("Descrição do Produto: ");
    fgets(newProduct.description, DESCRIPTION_CAPACITY, stdin);
    newProduct.description[strcspn(newProduct.description, "\n")] = '\0';

    printf("Preço Unitário: ");
    while (scanf("%f", &newProduct.price) == 0) {
        printf("Preço inválido. Digite novamente: ");
        while (getchar() != '\n');
    }

    printf("Quantidade em Estoque: ");
    while (scanf("%i", &newProduct.amount) == 0) {
        printf("Quantidade inválida. Digite novamente: ");
        while (getchar() != '\n');
    }

    products[*len] = newProduct;
    (*len)++;
    printf("Produto inserido com sucesso!\n");
}

void sortProducts(Product *products, int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (strcmp(products[j].name, products[j + 1].name) > 0) {
                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

void showProducts(Product *products, int len) {
    sortProducts(products, len);
    printf("\nLista de Produtos:\n");
    for (int i = 0; i < len; i++) {
        printf("ID: %d | Nome: %s | Descrição: %s | Preço: %.2f | Estoque: %d\n",
               products[i].id, products[i].name, products[i].description, products[i].price, products[i].amount);
    }
}

void buyProduct(Product *products, int len) {
    int id;
    printf("Digite o ID do produto que deseja comprar: ");
    while (scanf("%d", &id) == 0) {
        printf("ID inválido. Digite novamente: ");
        while (getchar() != '\n');
    }

    int index = -1;
    for (int i = 0; i < len; i++) {
        if (products[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Produto inexistente!\n");
        return;
    }

    int amount;
    printf("Quantidade desejada: ");
    while (scanf("%d", &amount) == 0) {
        printf("Quantidade inválida. Digite novamente: ");
        while (getchar() != '\n');
    }

    if (amount > products[index].amount) {
        printf("Estoque insuficiente! Disponível: %d unidades\n", products[index].amount);
    } else {
        products[index].amount -= amount;
        printf("Compra realizada com sucesso! Total: R$%.2f\n", amount * products[index].price);
    }
}

int main() {
    Product products[PRODUCTS_CAPACITY];
    int len = 0;

    int option;
    do {
        printf("\n----- Menu Loja de Eletrônicos -----\n");
        printf("1. Inserir Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Comprar Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        
        while (scanf("%d", &option) == 0) {
            printf("Opção inválida!");
            while (getchar() != '\n');
            continue;
        }

        switch (option) {
            case 1:
                insertProduct(products, &len);
                break;
            case 2:
                showProducts(products, len);
                break;
            case 3:
                buyProduct(products, len);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (option != 0);

    return 0;
}
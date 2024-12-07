#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define CARACTERES 100
#define MAX_PRODUTOS 500
#define INICIO 0

typedef struct {
    int codigo;
	char nome[CARACTERES];
	int quantidade;
	double preco;
	int ativo;
} Produto;
	
void incluirProduto(Produto* produtos, int* numeroDeProdutos);
void alterarProduto(Produto* produtos, int numeroDeProdutos);
void excluirProduto(Produto* produtos, int numeroDeProdutos);
void comprarProduto(Produto* produtos, int numeroDeProdutos);
void consultarProduto(Produto* produtos, int numeroDeProdutos);
void listarProdutos(Produto* produtos, int numeroDeProdutos);
int obterPosicaoDoProdutoPorCodigo(Produto* produtos, int numeroDeProdutos, int codigo);
int confirmarResposta();

int main() {
    int numeroDeProdutos;
    Produto produtos[MAX_PRODUTOS];
    
    while (1) {
		printf("\n");
		printf("O que deseja fazer?\n");
		printf("0 - Finalizar compra\n");
		printf("1 - Incluir um produto\n");
		printf("2 - Alterar um produto\n");
		printf("3 - Excluir um produto\n");
		printf("4 - Comprar um produto\n");
		printf("5 - Consultar um produto\n");
		printf("6 - Ver lista de produtos\n");
        
		int opcaoSelecionada;
		while (scanf("%i", &opcaoSelecionada) != 1 || opcaoSelecionada < 0 || opcaoSelecionada > 6) {
			printf("Resposta inválida!\n");
			printf("Digite o numero ao lado da opção que deseja tomar\n");
			while (getchar() != '\n');
		}
		
		switch (opcaoSelecionada) {
            case 1:
				incluirProduto(produtos, &numeroDeProdutos);
				break;
            case 2:
				alterarProduto(produtos, numeroDeProdutos);
				break;
            case 3:
				excluirProduto(produtos, numeroDeProdutos);
				break;
            case 4:
				comprarProduto(produtos, numeroDeProdutos);
				break;
            case 5:
				consultarProduto(produtos, numeroDeProdutos);
				break;
            case 6:
				listarProdutos(produtos, numeroDeProdutos);
				break;
			default:
				printf("Obrigado por utilizar nosso programa!\n");
				return 0;
        }
    }
	
	return 0;
}

void incluirProduto(Produto* produtos, int* numeroDeProdutos) {
	if (*numeroDeProdutos == MAX_PRODUTOS) {
		printf("Não é possível cadastrar mais produtos no momento!\n");
		printf("Exclua um produto e tente novamente!\n");
		return;
	}
	
	int codigo;
	printf("Qual o código do produto?\n");
	while (1) {
		if (scanf("%i", &codigo) != 1) {
			while (getchar() != '\n');
			continue;
		}
		
		for (int i = 0; i < *numeroDeProdutos; i++) {
			if (produtos[i].codigo == codigo && produtos[i].ativo == 1) {
				printf("Esse código já existe!\n");
				continue;
			}
		}
		
		break;
	}
	
    produtos[*numeroDeProdutos].codigo = codigo;
	produtos[*numeroDeProdutos].ativo = 1;
	
    printf("Qual o nome do produto?\n");
	while (fgets(produtos[*numeroDeProdutos].nome, CARACTERES, stdin) == NULL || produtos[*numeroDeProdutos].nome[0] == '\n'); 
    produtos[*numeroDeProdutos].nome[strcspn(produtos[*numeroDeProdutos].nome, "\n")] = '\0';
    while (getchar() != '\n');

    printf("Qual o preço desse produto?\n");
	while (scanf("%lf", &produtos[*numeroDeProdutos].preco) != 1)
		while (getchar() != '\n');
	
    printf("Quantos desse produto tem em estoque?\n");
	while (scanf("%i", &produtos[*numeroDeProdutos].quantidade) != 1)
		while (getchar() != '\n');
    
    (*numeroDeProdutos)++;
	
	printf("Produto incluido!\n");
}

void alterarProduto(Produto* produtos, int numeroDeProdutos) {
	int codigo;
    printf("Digite o codigo do produto que deseja alterar: ");
    while (scanf("%i", &codigo) != 1)
		while (getchar() != '\n');
    
	int posicaoProduto = obterPosicaoDoProdutoPorCodigo(produtos, numeroDeProdutos, codigo);
	if (posicaoProduto == -1) {
		printf("Esse produto não existe!\n");
		return;
	}
	
    while (1) {
        printf("O que deseja alterar no produto %s?\n", produtos[posicaoProduto].nome);
        printf("0 - Encerrar alterações\n");
        printf("1 - Alterar nome\n");
        printf("2 - Alterar preço\n");
        printf("3 - Alterar quantidade em estoque\n");
        
		int escolha;
		while (scanf("%i", &escolha) != 1 || escolha < 0 || escolha > 3)
			while (getchar() != '\n');
    
        switch (escolha) {
            case 1:
                printf("Qual nome deseja colocar?\n");
                printf("(Nome atual: '%s')\n", produtos[posicaoProduto].nome);
                while (fgets(produtos[posicaoProduto].nome, CARACTERES, stdin) == NULL || produtos[posicaoProduto].nome[0] == '\n'); 
				produtos[posicaoProduto].nome[strcspn(produtos[posicaoProduto].nome, "\n")] = '\0';
				while (getchar() != '\n');
                break;
            case 2:
                printf("Qual preço deseja colocar?\n");
                printf("(Preço atual: '%.2lf')\n",produtos[posicaoProduto].preco);
                while (scanf("%lf", &produtos[posicaoProduto].preco) != 1)
					while (getchar() != '\n');
                break;
            case 3:
                int novaQuantidade;
                printf("Qual quantidade deseja colocar?\n");
                printf("(Quantidade atual: '%i')", produtos[posicaoProduto].quantidade);
                while (scanf("%i", &produtos[posicaoProduto].quantidade) != 1)
					while (getchar() != '\n');
                break;
			default: return;
        }
    
        printf("Deseja alterar mais algo nesse produto?\n");
        if (confirmarResposta() == 0)
            return;
    }
}

void excluirProduto(Produto* produtos, int numeroDeProdutos) {
    int codigo;
    printf("Digite o codigo do produto que deseja excluir: ");
    while (scanf("%i", &codigo) != 1)
		while (getchar() != '\n');
    
	int posicaoProduto = obterPosicaoDoProdutoPorCodigo(produtos, numeroDeProdutos, codigo);
	if (posicaoProduto == -1) {
		printf("Esse produto não existe!\n");
		return;
	}
    
    printf("Tem certeza que deseja excluir o produto %s?\n", produtos[posicaoProduto].nome);
    if (confirmarResposta() == 0)
        return;
	
	produtos[posicaoProduto].ativo = 0;
    
    printf("Produto excluído com sucesso!\n");
}

void comprarProduto(Produto* produtos, int numeroDeProdutos) {
    int codigo;
    printf("Digite o codigo do produto que deseja comprar: ");
    while (scanf("%i", &codigo) != 1)
		while (getchar() != '\n');
    
	int posicaoProduto = obterPosicaoDoProdutoPorCodigo(produtos, numeroDeProdutos, codigo);
	if (posicaoProduto == -1) {
		printf("Esse produto não existe!\n");
		return;
	}
    
    printf("Tem certeza que deseja comprar o produto %s?\n", produtos[posicaoProduto].nome);
    if (confirmarResposta() == 0)
        return;
    
	int quantidade;
    printf("Quantos(as) '%s' deseja comprar?\n", produtos[posicaoProduto].nome);
    printf("(Quantidade em estoque: %i)\n", produtos[posicaoProduto].quantidade);
    while (scanf("%i", &quantidade) != 1 || quantidade < 1)
		while (getchar() != '\n');
	
	if (quantidade > produtos[posicaoProduto].quantidade) {
		printf("Quantidade insuficiente em estoque\n");
		return;
	}
    
    double custo = produtos[posicaoProduto].preco * quantidade;
	
    printf("Deseja mesmo comprar %i unidade(s) do produto '%s'?\n",quantidade, produtos[posicaoProduto].nome);
    printf("A compra irá custar R$%.2lf\n", custo);
    if (confirmarResposta() == 0)
        return;
		
    produtos[posicaoProduto].quantidade -= quantidade;
    printf("Compra realizada com sucesso!\n");
}

void consultarProduto(Produto* produtos, int numeroDeProdutos) {
    int codigo;
    printf("Digite o codigo do produto que deseja consultar: ");
    while (scanf("%i", &codigo) != 1)
		while (getchar() != '\n');
    
	int posicaoProduto = obterPosicaoDoProdutoPorCodigo(produtos, numeroDeProdutos, codigo);
	if (posicaoProduto == -1) {
		printf("Esse produto não existe!\n");
		return;
	}
	
    printf("----------------------------------------------------\n");
	printf("|  ID  |        NOME        |   PREÇO   |QUANTIDADE|\n");
	printf("----------------------------------------------------\n");   
    printf("|%-6i|%-20s|%11.2f|%10i|\n", produtos[posicaoProduto].codigo, produtos[posicaoProduto].nome, produtos[posicaoProduto].preco, produtos[posicaoProduto].quantidade);
	printf("----------------------------------------------------\n"); 
}

void listarProdutos(Produto* produtos, int numeroDeProdutos) {
    printf("\n----------------------------------------------------\n");
    printf("|                TABELA DE PRODUTOS                |\n");
    printf("----------------------------------------------------\n");
    printf("|  ID  |        NOME        |   PREÇO   |QUANTIDADE|\n");
	
    for(int i = 0; i < numeroDeProdutos; i++) {
        printf("----------------------------------------------------\n");   
		printf("|%-6i|%-20s|%11.2f|%10i|\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
	
    printf("----------------------------------------------------\n"); 
}

int obterPosicaoDoProdutoPorCodigo(Produto* produtos, int numeroDeProdutos, int codigo) {
    for (int i = 0; i < numeroDeProdutos; i++)
        if (produtos[i].codigo == codigo && produtos[i].ativo == 1)
            return i;
	
    return -1;
}

int confirmarResposta() {
	printf("0 - Não / 1 - Sim\n");
    
	int resposta;
    while (scanf("%i", &resposta) != 1 || resposta != 0 && resposta != 1) {
        printf("Resposta inválida!\n");
        printf("Digite o numero ao lado da opção que deseja\n");
    }
	
    return resposta;
}
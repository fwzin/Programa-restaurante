#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define CYAN    "\x1B[36m"

// Estrutura para armazenar informações do produto
struct Produto {
    char nome[50];
    double preco;
};

// Função para calcular o valor total da compra
double calcularValorTotal(struct Produto produtos[], int quantidadeProdutos, bool cobrarGarcom) {
    double valorTotal = 0.0;

    for (int i = 0; i < quantidadeProdutos; i++) {
        valorTotal += produtos[i].preco;
    }

    if (cobrarGarcom) {
        valorTotal *= 1.15;  // Cobrar 15% a mais se o garçom for incluído
    }

    return valorTotal;
}

// Função para obter a confirmação do cliente
bool obterConfirmacao() {
    char confirmacao;
    printf("Confirmar o pedido (S para sim, N para não): ");
    scanf(" %c", &confirmacao);

    return (confirmacao == 'S' || confirmacao == 's');
}

// Função para mostrar um menu de opções e retornar a escolha do cliente
char mostrarMenu() {
    char escolha;
    printf("\n");
    printf("Menu:\n");
    printf("a. Prato Principal\n");
    printf("b. Bebida\n");
    printf("c. Sobremesa\n");
    printf("x. Finalizar Pedido\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &escolha);
    return escolha;
}

// Função para adicionar um produto ao pedido
void adicionarProduto(struct Produto produtos[], int *quantidadeProdutos) {
    printf("\n");
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]s", produtos[*quantidadeProdutos].nome);
    printf("Digite o preço do produto: ");
    scanf("%lf", &produtos[*quantidadeProdutos].preco);
    (*quantidadeProdutos)++;
}

int main() {
    printf(GREEN "Bem-vindo ao Restaurante Cantinho de Santana!\n" RESET);

    char funcionario[50];
    printf("Digite o nome do funcionario: ");
    scanf("%s", funcionario);

    struct Produto produtos[50];
    int quantidadeProdutos = 0;
    bool cobrarGarcom = false;

    char escolha;
    do {
        escolha = mostrarMenu();

        switch (escolha) {
            case 'a':
                adicionarProduto(produtos, &quantidadeProdutos);
                break;
            case 'b':
                adicionarProduto(produtos, &quantidadeProdutos);
                break;
            case 'c':
                adicionarProduto(produtos, &quantidadeProdutos);
                break;
            case 'x':
                break;
            default:
                printf(RED "Opção inválida. Tente novamente.\n" RESET);
        }
    } while (escolha != 'x' && quantidadeProdutos < 50);

    char cobrarGarcomResposta;
    printf("Deseja cobrar os 15%% do garçom (S para sim, N para não): ");
    scanf(" %c", &cobrarGarcomResposta);
    cobrarGarcom = (cobrarGarcomResposta == 'S' || cobrarGarcomResposta == 's');

    double valorTotal = calcularValorTotal(produtos, quantidadeProdutos, cobrarGarcom);

    time_t t;
    struct tm* tm_info;
    char dataHora[100];
    time(&t);
    tm_info = localtime(&t);
    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M:%S", tm_info);

    printf("\nResumo do Pedido:\n");
    for (int i = 0; i < quantidadeProdutos; i++) {
        printf("Produto: %s - R$ %.2f\n", produtos[i].nome, produtos[i].preco);
    }
    printf("Cobrar Garçom: %s\n", (cobrarGarcom ? "Sim" : "Não"));
    printf("Valor Total do Pedido: R$ %.2f\n", valorTotal);

    if (obterConfirmacao()) {
        FILE *reciboArquivo = fopen("recibo.txt", "a");

        if (reciboArquivo == NULL) {
            printf(RED "Erro ao abrir o arquivo de recibo.\n" RESET);
        } else {
            fprintf(reciboArquivo, "Recibo do Pedido:\n");
            fprintf(reciboArquivo, "Data e Hora do Pedido: %s\n", dataHora);
            fprintf(reciboArquivo, "funcionario: %s\n", funcionario);

            for (int i = 0; i < quantidadeProdutos; i++) {
                fprintf(reciboArquivo, "Produto: %s - R$ %.2f\n", produtos[i].nome, produtos[i].preco);
            }

            fprintf(reciboArquivo, "Cobrar Garçom: %s\n", (cobrarGarcom ? "Sim" : "Não"));
            fprintf(reciboArquivo, "Valor Total do Pedido: R$ %.2f\n", valorTotal);
            fprintf(reciboArquivo, "Pedido registrado com sucesso. Obrigado!\n\n");

            fclose(reciboArquivo);

            printf("Recibo do pedido salvo em 'recibo.txt'.\n");
        }
    } else {
        printf("Pedido cancelado.\n");
    }

    printf("Deseja fazer outro pedido (S para sim, N para não): ");
    char novaCompra;
    scanf(" %c", &novaCompra);

    if (novaCompra != 'S' && novaCompra != 's') {
        printf("Finalizando programa.\n");
    }

    return 0;
}

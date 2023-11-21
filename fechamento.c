#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *reciboArquivo;
    double totalDoDia = 0.0;
    char linha[256];

    reciboArquivo = fopen("recibo.txt", "r");

    if (reciboArquivo == NULL) {
        printf("Nenhum recibo encontrado. O restaurante não fez vendas hoje.\n");
        return 1;
    }

    while (fgets(linha, sizeof(linha), reciboArquivo) != NULL) {
        double valorDoRecibo = 0.0;
        if (sscanf(linha, "Valor Total do Pedido: R$ %lf", &valorDoRecibo) == 1) {
            totalDoDia += valorDoRecibo;
        }
    }

    fclose(reciboArquivo);

    printf("Total do dia: R$ %.2f\n", totalDoDia);

    return 0;
}

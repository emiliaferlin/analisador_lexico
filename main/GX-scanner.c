#include <stdio.h>

int main() {
    FILE *arquivo;
    char linha[100]; // Tamanho máximo de cada linha

    // Abre o arquivo em modo de leitura ("r")
    arquivo = fopen("GX-cadeias_entrada.txt", "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Lê e exibe cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    return 0;
}

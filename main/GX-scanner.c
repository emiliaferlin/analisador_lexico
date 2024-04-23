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
        // Remove o caractere de nova linha, se existir

        int cont_linha = 0; // Comprimento da linha
         for (int i = 0; linha[i] != '\0'; i++) {
            cont_linha++;
        }

        int state = 0;
        int i = 0;

        while (i < cont_linha) {
            printf("\n", linha[i]);
            switch (state) {
                case 0:
                    if (linha[i] == '{') {
                        printf("%c\n", linha[i]);
                        printf("Acerto no estado 0\n");
                        state = 1;
                    } else {
                        printf("%c\n", linha[i]);
                        // error
                        printf("Erro no esatdo 0\n");
                        state = 0;
                    }
                    break;

                case 1:
                    if (linha[i] == '}') {
                        printf("%c\n", linha[i]);
                        printf("Acerto no estado 1\n");
                        state = 2;
                    } else {
                        printf("%c\n", linha[i]);
                        // error
                        printf("Erro no estado 1\n");
                        state = 1;
                    }
                    break;
            }
            i++;
        }

        if (state == 2) {
            printf("Acepet: Cadeia aceita\n");
        } else {
            printf("Error: Cadeia não reconhecida\n");
        }
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    return 0;
}

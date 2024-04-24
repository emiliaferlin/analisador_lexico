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
        if (linha[strlen(linha) - 1] == '\n')
            linha[strlen(linha) - 1] = '\0';

         int cont_linha = 0; // Comprimento da linha
         for (int i = 0; linha[i] != '\0'; i++) {
            cont_linha++;
        }

        int state = 0;
        int i = 0;
        printf("quantidade linha ==> %d", cont_linha);
        printf("\n");

        while (i < cont_linha) {
            switch (state) {
                case 0:
                    if (linha[i] == '{') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 0\n");
                        state = 1;
                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no esatdo 0\n");
                        state = 3;
                    }
                    break;

                case 1:
                    if (linha[i] == '}') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 1\n");
                        state = 2;
                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 1\n");
                        state = 1;
                    }
                    break;

            }
            i++;
        }

         if (state == 2) {
            printf("Acepet: Cadeia aceita a.1 \n");
            printf("\n");
        } else {
            printf("Error: Cadeia nao reconhecida a.1 \n");
            printf("\n");
        }

        int stateb1 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (stateb1) {
                case 0:
                    if ((linha[i] >= 'A' && linha[i] <= 'Z') || (linha[i] >= 'a' && linha[i] <= 'z')) {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 0\n");
                        if((linha[i + 1] >= 'A' && linha[i + 1] <= 'Z') || (linha[i + 1] >= 'a' && linha[i + 1] <= 'z')){
                            stateb1 = 0;
                        }else{
                            stateb1 = 1;
                        }

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 0\n");
                        stateb1 = 1;
                    }

                    break;

                case 1:
                    if ((linha[i] >= '0' && linha[i] <= '9') || linha[i] == '_') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 1\n");
                        if(cont_linha == (i+1)){
                            stateb1 = 2;
                        }else{
                            if((linha[i + 1] >= 'A' && linha[i + 1] <= 'Z') || (linha[i + 1] >= 'a' && linha[i + 1] <= 'z')){
                                stateb1 = 0;
                            }else{
                                stateb1 = 1;
                            }
                        }

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 1\n");
                        stateb1 = 0;
                    }

                    break;

            }
            i++;
        }


         if (stateb1 == 2) {
            printf("Acepet: Cadeia aceita b.1 \n");
            printf("\n");
        } else {
            printf("Error: Cadeia nao reconhecida b.1 \n");
            printf("\n");
        }

        int stateb2 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (stateb2) {
                case 0:
                    if (linha[i] == 'i') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 0\n");
                        stateb2 = 1;

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 0\n");
                        stateb2 = 3;
                    }

                    break;

                case 1:
                    if (linha[i] == 'f') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 1\n");
                        stateb2 = 2;

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 1\n");
                        stateb2 = 3;
                    }

                    break;


            }
            i++;
        }


         if (stateb2 == 2) {
            printf("Acepet: Cadeia aceita b.2 \n");
            printf("\n");
        } else {
            printf("Error: Cadeia nao reconhecida b.2 \n");
            printf("\n");
        }

        int statec2 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statec2) {
                case 0:
                    if (linha[i] == '<' || linha[i] == '>' || linha[i] == '!' || linha[i] == '=') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 0\n");
                        if(linha[i] == '=' && cont_linha == 1){
                            statec2 = 2;
                        }else{
                            statec2 = 1;
                        }

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 0\n");
                        statec2 = 3;
                    }

                    break;

                case 1:
                    if (linha[i] == '=') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 1\n");
                        statec2 = 2;

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 1\n");
                        statec2 = 3;
                    }

                    break;

            }
            i++;
        }


         if (statec2 == 2) {
            printf("Acepet: Cadeia aceita c.2 \n");
            printf("\n");
        } else {
            printf("Error: Cadeia nao reconhecida c.2 \n");
            printf("\n");
        }

        int statec4 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statec4) {
                case 0:
                    if (linha[i] == '=') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 0\n");
                        statec4 = 1;

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 0\n");
                        statec4 = 3;
                    }

                    break;

                case 1:
                    if (linha[i] == ':') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 1\n");
                        statec4 = 2;

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 1\n");
                        statec4 = 3;
                    }

                    break;

            }
            i++;
        }


         if (statec4 == 2) {
            printf("Acepet: Cadeia aceita c.4 \n");
            printf("\n");
        } else {
            printf("Error: Cadeia nao reconhecida c.4 \n");
            printf("\n");
        }

        int statee1 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statee1) {
                case 0:
                    if (linha[i] == ';') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 0\n");
                        statee1 = 1;

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 0\n");
                        statee1 = 2;
                    }

                    break;

            }
            i++;
        }


         if (statee1 == 1) {
            printf("Acepet: Cadeia aceita e.1 \n");
            printf("\n");
        } else {
            printf("Error: Cadeia nao reconhecida e.1 \n");
            printf("\n");
        }

        int statee2 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statee2) {
                case 0:
                    if (linha[i] == '(') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 0\n");
                        statee2 = 1;

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 0\n");
                        statee2 = 3;
                    }

                    break;

                case 1:
                    if (linha[i] == ')') {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Acerto no estado 1\n");
                        statee2 = 2;

                    } else {
                        printf("Caractere ==> %c ", linha[i]);
                        printf("Erro no estado 1\n");
                        statee2 = 1;
                    }

                    break;

            }
            i++;
        }


         if (statee2 == 2) {
            printf("Acepet: Cadeia aceita e.2 \n");
            printf("\n");
        } else {
            printf("Error: Cadeia nao reconhecida e.2 \n");
            printf("\n");
        }


    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    return 0;
}

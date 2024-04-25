#include <stdio.h>

/*HEADER***********************************************************************
* INSTITUITION  : IFSul - Passo Fundo
* COURSE/SUBJECT: BCC – Compilers – AT01: Lex Analysis Work
* DATE          : 28/04/2024
* FILENAME      : GX-scanner.c
* DESCRIPTION   : Analisador léxico
*       XXX YYY.
* AUTHOR(S)     : Emilia Ferlin e Natália Bernardo Nunes
* NOTES         : G4
*       XXX YYY.
**************************************************************************END*/

int main() {
    FILE *arquivo;
    char linha[300]; // Tamanho máximo de cada linha

    // Abre o arquivo em modo de leitura ("r")
    arquivo = fopen("GX-cadeias_entrada.txt", "r");

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numLinha = 0;

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        //variavel para mostrar o #linha
        numLinha++;


         int cont_linha = 0; // Comprimento da linha
         for (int i = 0; linha[i] != '\0'; i++) {
            cont_linha++;
        }

        //remove o pula linha, assim dando o valor real de caracteres
        cont_linha = cont_linha - 1;

        //a.1
        int state = 0;
        int i = 0;
        printf("\n");
        while (i < cont_linha) {
            switch (state) {
                case 0:
                    if (linha[i] == '{') {
                        state = 1;
                    } else {
                        state = 3;
                    }
                    break;

                case 1:
                    if (linha[i] == '}') {
                        state = 2;
                    } else {
                        state = 1;
                    }
                    break;

            }
            i++;
        }

         if (state == 2) {
            printf("#%d", numLinha);
            printf(" --> TKN_COMMENT --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_COMMENT --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }

        //b.1
        int stateb1 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (stateb1) {
                case 0:
                    if ((linha[i] >= 'A' && linha[i] <= 'Z') || (linha[i] >= 'a' && linha[i] <= 'z')) {
                        if((linha[i + 1] >= 'A' && linha[i + 1] <= 'Z') || (linha[i + 1] >= 'a' && linha[i + 1] <= 'z')){
                            stateb1 = 0;
                        }else{
                            stateb1 = 1;
                        }

                    } else {
                        stateb1 = 1;
                    }

                    break;

                case 1:
                    if ((linha[i] >= '0' && linha[i] <= '9') || linha[i] == '_') {
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
                        stateb1 = 0;
                    }

                    break;

            }
            i++;
        }

        if (stateb1 == 2) {
            printf("#%d", numLinha);
            printf(" --> TKN_VAR --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_VAR --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }

        //b.2
        int stateb2 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (stateb2) {
                case 0:
                    if (linha[i] == 'i') {
                        stateb2 = 1;

                    } else {
                        stateb2 = 3;
                    }

                    break;

                case 1:
                    if (linha[i] == 'f') {
                        stateb2 = 2;

                    } else {
                        stateb2 = 3;
                    }

                    break;


            }
            i++;
        }


         if (stateb2 == 2) {
            printf("#%d", numLinha);
            printf(" --> TKN_RESWORD --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_RESWORD --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }

        //c.2
        int statec2 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statec2) {
                case 0:
                    if (linha[i] == '<' || linha[i] == '>' || linha[i] == '!' || linha[i] == '=') {
                        if(linha[i] == '='){
                            if(cont_linha == 1){
                                statec2 = 2;
                            }else{
                                statec2 = 3;
                            }
                        }else{
                            statec2 = 1;
                        }

                    } else {
                        statec2 = 3;
                    }

                    break;

                case 1:
                    if (linha[i] == '=') {
                        if(cont_linha == (i+1)){
                            statec2 = 2;
                        }else{
                            statec2 = 3;
                        }

                    } else {
                        statec2 = 3;
                    }

                    break;

            }
            i++;
        }

        //KN_LTEQ (<=), TKN_GTEQ (>=), TKN_EQ (=), TKN_DIFF (!=) REVER
         if (statec2 == 2) {
            printf("#%d", numLinha);
            printf(" --> TKN_LTEQ --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_LTEQ --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }


        //c.4
        int statec4 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statec4) {
                case 0:
                    if (linha[i] == '=') {
                        statec4 = 1;

                    } else {
                        statec4 = 3;
                    }

                    break;

                case 1:
                    if (linha[i] == ':') {
                        statec4 = 2;

                    } else {
                        statec4 = 3;
                    }

                    break;

            }
            i++;
        }


         if (statec4 == 2) {
            printf("#%d", numLinha);
            printf(" --> TKN_ASSIGN --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_ASSIGN --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }

        //d.3
        int stated3 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (stated3) {
                case 0:
                    if (linha[i] == '-') {
                        stated3 = 1;

                    } else {
                        stated3 = 1;
                    }

                    break;

                case 1:
                    if ((linha[i] >= '0' && linha[i] <= '9')) {
                        stated3 = 1;

                    } else {
                        stated3 = 2;
                    }

                    break;

                case 2:
                    if (linha[i] == '.') {
                        stated3 = 3;

                    } else {
                        stated3 = 5;
                    }

                    break;

                case 3:
                    if ((linha[i] >= '0' && linha[i] <= '9')) {
                        stated3 = 4;

                    } else {
                        stated3 = 5;
                    }

                    break;

            }
            i++;
        }

         if (stated3 == 4) {
            printf("#%d", numLinha);
            printf(" --> TKN_NUMREAL --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_NUMREAL --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }


        //d.6
        int stated6 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (stated6) {
                case 0:
                    if (linha[i] == '"') {
                        stated6 = 1;

                    } else {
                        stated6 = 4;
                    }

                    break;

                case 1:
                    if (linha[i] == ' '|| linha[i] == '!' || linha[i] == '#' || linha[i] == '$' || linha[i] == '%' || linha[i] == '&' ||
                        linha[i] == "'" || linha[i] == '(' || linha[i] == ')' || linha[i] == '*' || linha[i] == '+' || linha[i] == ',' ||
                        linha[i] == '-' || linha[i] == '.' || linha[i] == '/' || linha[i] == ':' || linha[i] == ';' || linha[i] == '<' ||
                        linha[i] == '=' || linha[i] == '>' || linha[i] == '?' || linha[i] == '@' || linha[i] == '[' || linha[i] == ']' ||
                        linha[i] == '^' || linha[i] == '_' || linha[i] == '`' || linha[i] == '{' || linha[i] == '|' || linha[i] == '}' ||
                        linha[i] == '~' || (linha[i] >= 'A' && linha[i] <= 'Z') || (linha[i] >= 'a' && linha[i] <= 'z') ||
                        (linha[i] >= '0' && linha[i] <= '9')) {
                        stated6 = 1;

                    } else {
                        stated6 = 2;
                    }

                    break;

                case 2:
                    if (linha[i] == '"') {
                        stated6 = 3;

                    } else {
                        stated6 = 4;
                    }

                    break;

            }
            i++;
        }

         if (stated6 == 3) {
            printf("#%d", numLinha);
            printf(" --> TKN_STR --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_STR --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }

        //e.1
        int statee1 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statee1) {
                case 0:
                    if (linha[i] == ';') {
                        statee1 = 2;

                    } else {
                        statee1 = 1;
                    }

                    break;

            }
            i++;
        }

        if (statee1 == 2) {
            printf("#%d", numLinha);
            printf(" --> TKN_STMSEP --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_STMSEP --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }

        //e.2
        int statee2 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statee2) {
                case 0:
                    if (linha[i] == '(') {
                        statee2 = 1;

                    } else {
                        statee2 = 3;
                    }

                    break;

                case 1:
                    if (linha[i] == ')') {
                        statee2 = 2;

                    } else {
                        statee2 = 1;
                    }

                    break;

            }
            i++;
        }

         if (statee2 == 2) {
            printf("#%d", numLinha);
            printf(" --> TKN_LEFTPAR, TKN_RIGHTPAR --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_LEFTPAR, TKN_RIGHTPAR --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }

        //e.7
        int statee7 = 0;
        i = 0;
         while (i < cont_linha) {
            switch (statee7) {
                case 0:
                    if (linha[i] == ' ' || linha[i] == '\t' || linha[i] == '\n' || linha[i] == '\r') {
                        statee7 = 1;

                    } else {
                        statee7 = 3;
                    }

                    break;

            }
            i++;
        }

         if (statee7 == 1) {
            printf("#%d", numLinha);
            printf(" --> TKN_REJECT --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        } else {
            printf("#%d", numLinha);
            printf(" --> TKN_REJECT --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
        }



    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    return 0;
}



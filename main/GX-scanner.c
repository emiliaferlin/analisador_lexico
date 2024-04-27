#include <stdio.h>

/*HEADER***********************************************************************
* INSTITUITION  : IFSul - Passo Fundo
* COURSE/SUBJECT: BCC – Compilers – AT01: Lex Analysis Work
* DATE          : 28/04/2024
* FILENAME      : GX-scanner.c
* DESCRIPTION   : Analisador léxico
*       XXX YYY.
* AUTHOR(S)     : Emilia Ferlin e Natália Bernardo Nunes
* NOTES         :
*       XXX YYY.
**************************************************************************END*/

int main() {
    FILE *arquivo;
    char linha[500];

    /* CODE COMMENTS***************************************************************
    * Abre o arquivo em modo de leitura ("r")      XXX YYY.
    **************************************************************************END*/
    arquivo = fopen("GX-cadeias_entrada.txt", "r");

    /* CODE COMMENTS***************************************************************
    * Verifica se o arquivo foi aberto corretamente      XXX YYY.
    **************************************************************************END*/
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numLinha = 0;

    /* CODE COMMENTS***************************************************************
    * Le cada linha do arquivo      XXX YYY.
    **************************************************************************END*/
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
         numLinha++;
         int contLinha = 0; // Comprimento da linha
         for (int i = 0; linha[i] != '\0'; i++) {
            contLinha++;
        }

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoComentarioA1(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoVariavelB1(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        palavrasReservadasB2(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoComparacaoC2(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoAtribuicaoC4(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoReaisD3(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoStringD6(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoSeparadorSentencasE1(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoParentesesE2(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *       XXX YYY.
        **************************************************************************END*/
        automatoSimbolosBrancoE7(contLinha, numLinha, linha);

    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    return 0;
}

void automatoComentarioA1(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    printf("\n");
    int state = 0;
    while (i < contLinha) {
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

}


void automatoVariavelB1(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    int stateb1 = 0;
    i = 0;
     while (i < contLinha) {
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
                    if(contLinha == (i+1)){
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


}


void palavrasReservadasB2(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    int stateb2 = 0;
    i = 0;
     while (i < contLinha) {
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


}

void automatoComparacaoC2(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    int statec2 = 0;
    i = 0;
     while (i < contLinha) {
        switch (statec2) {
            case 0:
                if (linha[i] == '<' || linha[i] == '>' || linha[i] == '!' || linha[i] == '=') {
                    if(linha[i] == '='){
                        if(contLinha == 1){
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
                    if(contLinha == (i+1)){
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
}

void automatoAtribuicaoC4(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    int statec4 = 0;
    i = 0;
     while (i < contLinha) {
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
}

void automatoReaisD3(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    int stated3 = 0;
    i = 0;
     while (i < contLinha) {
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
}

void automatoStringD6(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    int stated6 = 0;
    i = 0;
     while (i < contLinha) {
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

}

void automatoSeparadorSentencasE1(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    int statee1 = 0;
    i = 0;
     while (i < contLinha) {
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
}

void automatoParentesesE2(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    int statee2 = 0;
    i = 0;
     while (i < contLinha) {
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
}

void automatoSimbolosBrancoE7(int contLinha, int numLinha, char linha[300]){
    int i = 0;
    int statee7 = 0;
    i = 0;
     while (i < contLinha) {
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



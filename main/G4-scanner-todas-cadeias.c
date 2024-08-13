#include <stdio.h>
#include <ctype.h> // Para a função isspace

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

void removeEspacos(char *linha) {
    int i, j;
    i = 0;
    j = 0;
    while (linha[i]) {
        if (!isspace(linha[i]) || linha[i] != ' ' || linha[i] != '\t' || linha[i] != '\n' || linha[i] != '\r' || linha[i] != '\0') {
            linha[j++] = linha[i];
        }
        i++;
    }
}

int isReservada = 0;
int main() {
    FILE *arquivo;
    char linha[500];

    /* CODE COMMENTS***************************************************************
    * Abre o arquivo em modo de leitura ("r")
     XXX YYY.
    **************************************************************************END*/
    arquivo = fopen("a.txt", "r");

    /* CODE COMMENTS***************************************************************
    * Verifica se o arquivo foi aberto corretamente
     XXX YYY.
    **************************************************************************END*/
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numLinha = 0; // indica a posição #linha

    /* CODE COMMENTS***************************************************************
    * Le cada linha do arquivo
    XXX YYY.
    **************************************************************************END*/
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
         numLinha++;

         removeEspacos(linha); // Remove os espaços da linha

         int contLinha = 0; // Comprimento da linha

         /* CODE COMMENTS***************************************************************
        * conta o numero de caracter de cada linha
        XXX YYY.
        **************************************************************************END*/
         for (int i = 0; linha[i] != '\0'; i++) {
            contLinha++;
        }

        /* CODE COMMENTS***************************************************************
        * remove o pula linha, assim dando o valor real de caracteres e printa esse valor
        XXX YYY.
        **************************************************************************END*/
        contLinha = contLinha - 1;

            switch (linha[0]) {
                case '{':
                    automatoComentarioA1(contLinha, numLinha, linha);
                    break;
                case '=':
                    automatoAtribuicaoC4(contLinha, numLinha, linha);
                    break;
                case ';':
                    automatoSeparadorSentencasE1(contLinha, numLinha, linha);
                    break;
                case '(':
                case ')':
                    automatoParentesesE2(contLinha, numLinha, linha);
                    break;
                case '<':
                case '>':
                case '!':
                    automatoComparacaoC2(contLinha, numLinha, linha);
                    break;
                case '"':
                    automatoStringD6(contLinha, numLinha, linha);
                    break;
                default:
                    if ((linha[0] >= 'A' && linha[0] <= 'Z') || (linha[0] >= 'a' && linha[0] <= 'z')) {
                        palavrasReservadasB2(contLinha, numLinha, linha);
                        if (!isReservada) {
                            automatoVariavelB1(contLinha, numLinha, linha);
                        }
                    } else if ((linha[0] >= '0' && linha[0] <= '9')) {
                        automatoReaisD3(contLinha, numLinha, linha);
                    }
                    break;
            }

    }

    /* CODE COMMENTS***************************************************************
    *  Fecha o arquivo após a leitura
    XXX YYY.
    **************************************************************************END*/
    fclose(arquivo);


    /* CODE COMMENTS***************************************************************
    *  Finaliza programa
    XXX YYY.
    **************************************************************************END*/
    return 0;
}

void automatoComentarioA1(int contLinha, int numLinha, char linha[500]){
    printf("\n");
    int i = 0;
    int state = 0;

    //statea1 == 2 é aceito, caso contrario rejeitado
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
    }
    else {
        printf("#%d", numLinha);
        printf(" --> TKN_COMMENT --> ");
        printf("Reject --> ");
        printf("%s ", linha);
        printf("\n");
    }

}


void automatoVariavelB1(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int stateb1 = 0;


    /* CODE COMMENTS***************************************************************
    * Verificar se a linha excede o tamanho máximo permitido
    // Termina a string após o 30º caractere
    // Atualiza o comprimento da linha para 30
    XXX YYY.
    **************************************************************************END*/
    if (contLinha > 30) {
        linha[30] = '\0';
        contLinha = 30;
    }

    //stateb1 == 2 é aceito, caso contrario rejeitado
    if(isReservada == 0){
         while (i < contLinha) {
        switch (stateb1) {
            case 0:
                if ((linha[i] >= 'A' && linha[i] <= 'Z') || (linha[i] >= 'a' && linha[i] <= 'z')) {
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
                    stateb1 = 4;
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
                    stateb1 = 4;
                }

                break;

        }
        i++;
    }
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


void palavrasReservadasB2(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int stateb2 = 0;

    //stateb2 == 2 || stateb2 == 7 || stateb2 == 15 || stateb2 == 21 || stateb2 == 26 || stateb2 == 30 || stateb2 == 35
    //é aceito, caso contrario rejeitado
    while (i < contLinha) {
        if (stateb2 == 0) {
            if (linha[i] == 'i') {
                stateb2 = 1;
            } else if (linha[i] == 't') {
                stateb2 = 4;
            } else if (linha[i] == 'e') {
                stateb2 = 8;
            } else if (linha[i] == 'r') {
                stateb2 = 16;
            } else if (linha[i] == 'u') {
                stateb2 = 22;
            }else if (linha[i] == 'w') {
                stateb2 = 31;
            } else {
                stateb2 = 40;
            }
        } else if (stateb2 == 1) {
            if (linha[i] == 'f') {
                stateb2 = 2;
            } else {
                stateb2 = 40;
            }
        } else if (stateb2 == 4) {
            if (linha[i] == 'h') {
                stateb2 = 5;
            } else {
                stateb2 = 40;
            }
        } else if (stateb2 == 5) {
            if (linha[i] == 'e') {
                stateb2 = 6;
            } else {
                stateb2 = 40;
            }
        }else if (stateb2 == 6) {
            if (linha[i] == 'n') {
                stateb2 = 7;
            } else {
                stateb2 = 40;
            }
        } else if (stateb2 == 8) {
            if (linha[i] == 'l') {
                stateb2 = 9;
            } else {
                if(linha[i] == 'n'){
                    stateb2 = 14;
                }else{
                    stateb2 = 40;
                }
            }
        } else if (stateb2 == 9) {
            if (linha[i] == 's') {
                stateb2 = 10;
            } else {
                stateb2 = 40;
            }
        } else if (stateb2 == 10) {
            if (linha[i] == 'e') {
                stateb2 = 15;
            } else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 13) {
            if (linha[i] == 'n') {
                stateb2 = 14;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 14) {
            if (linha[i] == 'd') {
                stateb2 = 15;
            }
            else {
                stateb2 = 40;
            }
        } else if (stateb2 == 16) {
            if (linha[i] == 'e') {
                stateb2 = 17;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 17) {
            if (linha[i] == 'p') {
                stateb2 = 18;

            }else if(linha[i] == 'a'){
                stateb2 = 29;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 18) {
            if (linha[i] == 'e') {
                stateb2 = 19;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 19) {
            if (linha[i] == 'a') {
                stateb2 = 20;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 20) {
            if (linha[i] == 't') {
                stateb2 = 21;
            }
            else {
                stateb2 = 40;
            }
        }
         else if (stateb2 == 22) {
            if (linha[i] == 'n') {
                stateb2 = 23;
            }
            else {
                stateb2 = 40;
            }
        }
         else if (stateb2 == 23) {
            if (linha[i] == 't') {
                stateb2 = 24;
            }
            else {
                stateb2 = 40;
            }
        }
         else if (stateb2 == 24) {
            if (linha[i] == 'i') {
                stateb2 = 25;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 25) {
            if (linha[i] == 'l') {
                stateb2 = 26;
            }
            else {
                stateb2 = 40;
            }
        }

         else if (stateb2 == 29) {
            if (linha[i] == 'd') {
                stateb2 = 30;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 31) {
            if (linha[i] == 'r') {
                stateb2 = 32;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 32) {
            if (linha[i] == 'i') {
                stateb2 = 33;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 33) {
            if (linha[i] == 't') {
                stateb2 = 34;
            }
            else {
                stateb2 = 40;
            }
        }
        else if (stateb2 == 34) {
            if (linha[i] == 'e') {
                stateb2 = 35;
            }
            else {
                stateb2 = 40;
            }
        }

        i++;
    }


        if (stateb2 == 2 || stateb2 == 7 || stateb2 == 15 || stateb2 == 21 || stateb2 == 26 || stateb2 == 30 || stateb2 == 35) {
            isReservada = 1;
            printf("#%d", numLinha);
            printf(" --> TKN_RESWORD --> ");
            printf("Accept --> ");
            printf("%s ", linha);
            printf("\n");
        }
        else {
            isReservada = 0;
            printf("#%d", numLinha);
            printf(" --> TKN_RESWORD --> ");
            printf("Reject --> ");
            printf("%s ", linha);
            printf("\n");
    }


}

void automatoComparacaoC2(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int statec2 = 0;
    int maior = 0;
    int menor = 0;
    int diferente = 0;
    int igual = 0;

    //statec2 == 2 é aceito, caso contrario rejeitado
     while (i < contLinha) {
        switch (statec2) {
            case 0:
                if (linha[i] == '<' || linha[i] == '>' || linha[i] == '!' || linha[i] == '=') {
                    if(linha[i] == '='){
                        if(contLinha == 1){
                            igual = 1;
                            statec2 = 2;
                        }else{
                            statec2 = 3;
                        }
                    }else{
                        if(linha[i] == '<'){
                            menor = 1;
                        }
                        if(linha[i] == '>'){
                            maior = 1;
                        }
                        if(linha[i] == '!'){
                            diferente = 1;
                        }
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

     if (statec2 == 2 && maior == 1) {
        printf("#%d", numLinha);
        printf(" --> TKN_GTEQ --> ");
        printf("Accept --> ");
        printf("%s ", linha);
        printf("\n");
    }
    else if (statec2 == 2 && menor == 1) {
        printf("#%d", numLinha);
        printf(" --> KN_LTEQ --> ");
        printf("Accept --> ");
        printf("%s ", linha);
        printf("\n");
    }
    else if (statec2 == 2 && diferente == 1) {
        printf("#%d", numLinha);
        printf(" --> TKN_DIFF --> ");
        printf("Accept --> ");
        printf("%s ", linha);
        printf("\n");
    }
    else if (statec2 == 2 && igual == 1) {
        printf("#%d", numLinha);
        printf(" --> TKN_EQ --> ");
        printf("Accept --> ");
        printf("%s ", linha);
        printf("\n");
    }
    else {
        printf("#%d", numLinha);
        printf(" --> KN_LTEQ, TKN_GTEQ, TKN_EQ, TKN_DIFF --> ");
        printf("Reject --> ");
        printf("%s ", linha);
        printf("\n");
    }
}

void automatoAtribuicaoC4(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int statec4 = 0;

    //statec4 == 2 é aceito, caso contrario rejeitado
     while (i < contLinha) {
        switch (statec4) {
            case 0:
                if (linha[i] == ':') {
                    statec4 = 1;

                } else {
                    statec4 = 3;
                }

                break;

            case 1:
                if (linha[i] == '=') {
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
    }
    else {
        printf("#%d", numLinha);
        printf(" --> TKN_ASSIGN --> ");
        printf("Reject --> ");
        printf("%s ", linha);
        printf("\n");
    }
}

void automatoReaisD3(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int stated3 = 0;

    //stated3 == 3 é aceito, caso contrario rejeitado
     while (i < contLinha) {
        switch (stated3) {
            case 0:
                /* CODE COMMENTS***************************************************************
                * Verifica se a linha excede o tamanho máximo permitido, se exceder cai no estado de rejeitado
                tem que ter no minimo 4 caracteres com sinal e no maximo 14 com sinal,
                XXX YYY.
                **************************************************************************END*/
                if (linha[i] == '-' && (contLinha >= 4 || contLinha <= 14)) {
                    stated3 = 0;

                } else {
                    /* CODE COMMENTS***************************************************************
                    * Verifica se a linha excede o tamanho máximo permitido, se exceder cai no estado de rejeitado
                    tem que ter no minimo 3 caracteres sem sinal e no maximo 13 sem sinal,
                    XXX YYY.
                    **************************************************************************END*/
                    if ((linha[i] >= '0' && linha[i] <= '9') && (contLinha >= 3 || contLinha <= 13)) {
                    stated3 = 0;
                        if ((linha[i + 1] >= '0' && linha[i + 1] <= '9')) {
                            stated3 = 0;

                        } else {
                            stated3 = 2;
                        }

                    } else {
                        stated3 = 5;
                    }
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
                    stated3 = 3;

                } else {
                    stated3 = 5;
                }

                break;

        }
        i++;
    }

     if (stated3 == 3) {
        printf("#%d", numLinha);
        printf(" --> TKN_NUMREAL --> ");
        printf("Accept --> ");
        printf("%s ", linha);
        printf("\n");
    }
    else {
        printf("#%d", numLinha);
        printf(" --> TKN_NUMREAL --> ");
        printf("Reject --> ");
        printf("%s ", linha);
        printf("\n");
    }
}

void automatoStringD6(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int stated6 = 0;


    //stated6 == 3 é aceito, caso contrario rejeitado
     while (i < contLinha) {
        switch (stated6) {
            case 0:
                 /* CODE COMMENTS***************************************************************
                * Verifica se a linha excede o tamanho máximo permitido, se exceder cai no estado de rejeitado
                 seria 126 caracteres especiais e mais as aspas, então teria o tamanho máximo de 128, por conta das aspas
                XXX YYY.
                **************************************************************************END*/

                if (linha[i] == '"' && contLinha <= 128) {
                    stated6 = 1;

                } else {
                    stated6 = 4;
                }

                break;

            case 1:
                if (linha[i] == ' '|| linha[i] == '!' || linha[i] == '#' || linha[i] == '$' || linha[i] == '%' || linha[i] == '&' ||
                    linha[i] == '\'' || linha[i] == '(' || linha[i] == ')' || linha[i] == '*' || linha[i] == '+' || linha[i] == ',' ||
                    linha[i] == '-' || linha[i] == '.' || linha[i] == '/' || linha[i] == ':' || linha[i] == ';' || linha[i] == '<' ||
                    linha[i] == '=' || linha[i] == '>' || linha[i] == '?' || linha[i] == '@' || linha[i] == '[' || linha[i] == ']' ||
                    linha[i] == '^' || linha[i] == '_' || linha[i] == '`' || linha[i] == '{' || linha[i] == '|' || linha[i] == '}' ||
                    linha[i] == '~' || (linha[i] >= 'A' && linha[i] <= 'Z') || (linha[i] >= 'a' && linha[i] <= 'z') || linha[i] == '\\' ||
                    (linha[i] >= '0' && linha[i] <= '9')) {
                     if (linha[i + 1] == ' '|| linha[i + 1] == '!' || linha[i + 1] == '#' || linha[i + 1] == '$' || linha[i + 1] == '%' || linha[i + 1] == '&' ||
                        linha[i + 1] == '\'' || linha[i + 1] == '(' || linha[i + 1] == ')' || linha[i + 1] == '*' || linha[i + 1] == '+' || linha[i + 1] == ',' ||
                        linha[i + 1] == '-' || linha[i + 1] == '.' || linha[i + 1] == '/' || linha[i + 1] == ':' || linha[i + 1] == ';' || linha[i + 1] == '<' ||
                        linha[i + 1] == '=' || linha[i + 1] == '>' || linha[i + 1] == '?' || linha[i + 1] == '@' || linha[i + 1] == '[' || linha[i + 1] == ']' ||
                        linha[i + 1] == '^' || linha[i + 1] == '_' || linha[i + 1] == '`' || linha[i + 1] == '{' || linha[i + 1] == '|' || linha[i + 1] == '}' ||
                        linha[i + 1] == '~' || (linha[i + 1] >= 'A' && linha[i + 1] <= 'Z') || (linha[i + 1] >= 'a' && linha[i + 1] <= 'z') || linha[i + 1] == '\\' ||
                        (linha[i + 1] >= '0' && linha[i + 1] <= '9')){
                            stated6 = 1;
                        }else{
                            stated6 = 2;
                        }

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
    }
    else {
        printf("#%d", numLinha);
        printf(" --> TKN_STR --> ");
        printf("Reject --> ");
        printf("%s ", linha);
        printf("\n");
    }

}

void automatoSeparadorSentencasE1(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int statee1 = 0;


    //statee1 == 2 é aceito, caso contrario rejeitado
     while (i < contLinha) {
        switch (statee1) {
            case 0:
                if (linha[i] == ';' && contLinha == 1) {
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
    }
    else {
        printf("#%d", numLinha);
        printf(" --> TKN_STMSEP --> ");
        printf("Reject --> ");
        printf("%s ", linha);
        printf("\n");
    }
}

void automatoParentesesE2(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int statee2 = 0;

    //statee2 == 2 é aceito, se não é rejeitado
     while (i < contLinha) {
        switch (statee2) {
            case 0:
                if (linha[i] == '(' || linha[i] == ')') {
                    if(linha[i] == '('){
                        statee2 = 1;
                    }
                    if(linha[i] == ')'){
                        statee2 = 2;
                    }


                } else {
                    statee2 = 3;
                }

                break;

        }
        i++;
    }

     if (statee2 == 1) {
        printf("#%d", numLinha);
        printf(" --> TKN_LEFTPAR --> ");
        printf("Accept --> ");
        printf("%s ", linha);
        printf("\n");
    }
    else if (statee2 == 2) {
        printf("#%d", numLinha);
        printf(" --> TKN_RIGHTPAR --> ");
        printf("Accept --> ");
        printf("%s ", linha);
        printf("\n");
    }
    else {
        printf("#%d", numLinha);
        printf(" --> TKN_LEFTPAR, TKN_RIGHTPAR --> ");
        printf("Reject --> ");
        printf("%s ", linha);
        printf("\n");
    }
}

void automatoSimbolosBrancoE7(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int statee7 = 0;
    int contLinhaAux = 0;

    //remove o pula linha, assim dando o valor real de caracteres
    contLinhaAux = contLinha + 1;

    //statee7 == 1 é aceito, caso contrário é erro
     while (i < contLinhaAux) {
        switch (statee7) {
            case 0:
                if (linha[i] == ' ' || linha[i] == '\t' || linha[i] == '\n' || linha[i] == '\r') {
                    statee7 = 1;

                } else {
                    statee7 = 2;
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



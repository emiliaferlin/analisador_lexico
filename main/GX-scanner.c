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
    * Abre o arquivo em modo de leitura ("r")
     XXX YYY.
    **************************************************************************END*/
    arquivo = fopen("GX-cadeias_entrada.txt", "r");

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

         int contLinha = 0; // Comprimento da linha

         /* CODE COMMENTS***************************************************************
        * conta o numero de caracter de cada linha, porém ignora o final da linha, que seria a quebra
        XXX YYY.
        **************************************************************************END*/
         for (int i = 0; linha[i] != '\0'; i++) {
            contLinha++;
        }

        /* CODE COMMENTS***************************************************************
        * Essa funcão faz com que identifique uma cadeia que tenha um comentário sendo, {...}
        Ela deve iniciar com { e terminar com }, ignorando o que há depois de { ou antes de }
        XXX YYY.
        **************************************************************************END*/
        automatoComentarioA1(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        * Essa funcão vai ser responsável por verificar a cadeia que seja uma variavel, começando com uma letra
        e terminando com numero ou _. Não estaria especificado que deveria terminar em letra ou só numero, apenas começar com uma ou mais letras.
        Ter no mínimo um caractere ou no máximo 30, sendo que se chegasse nos 30 deveria descartar os excedentes,
        que seria o que está fazendo essa função.
        XXX YYY.
        **************************************************************************END*/
        automatoVariavelB1(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        * Essa função é responsavel por aceitar as cadeia palavras reservadas sendo
        if ou then ou else end ou repeat ou until | read ou write
        XXX YYY.
        **************************************************************************END*/
        palavrasReservadasB2(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        * Essa função fica responsavel por aceitar cadeias de comparacao, sendo assim, vai aceitar cadeias que começem com
        > < ! e termine com = ou também aceitar apenas o caracter de =. E ainda validando qual comparacao foi aceita para identificar
        na hora de mostrar o resultado como por exemplo, se >= foi aceita, então mostra como id TKN_GTEQ.
        XXX YYY.
        **************************************************************************END*/
        automatoComparacaoC2(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        *
        XXX YYY.
        **************************************************************************END*/
        automatoAtribuicaoC4(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        * Esse codigo e respoonsavel por aceitar cadeias de numeros reais, sendo no minimo 3 e no maximo 13 sem sinal
        ou no minimo 4 ou máximo 14 com sinal, considerando que pode ou não ter sinal, que comece com numeros, tenho um ponto entre eles
        e que termine com numeros.
        XXX YYY.
        **************************************************************************END*/
        automatoReaisD3(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        * Essa funcao vai tratar a cadeia de String contendo caracteres especiais entre as aspas.
        Ou seja, deve iniciar com uma aspa, conter caracteres especiais, sendo até no máximo 126, e terminando com uma aspa.
        XXX YYY.
        **************************************************************************END*/
        automatoStringD6(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        * Funcao resposavel por tratar a cadeia que contenha apenas ; então a cadeia
        deve iniciar e finalizar com esse simbolo
        XXX YYY.
        **************************************************************************END*/
        automatoSeparadorSentencasE1(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        * Funcao que fica resposavel por identificar parenteses, ou seja começando com ( e terminando com )
        independete do que tenha dentro deles.
        XXX YYY.
        **************************************************************************END*/
        automatoParentesesE2(contLinha, numLinha, linha);

        /* CODE COMMENTS***************************************************************
        * Funcao resposanevl por identificar na cadeia caracteres que iniciem por espaço ou ctabulação
        ou salto de linha ou retorno de carro, e lógico terminem com os mesmos. A única diferença é que
        nessa função em cada cadeia não é removido o salto de linha no final de cada linha, para não alterar o resultado,
        já que pode ser que uma linha tenha apenas um salto, e isso é considerado válido, por conta que incia e termina com salto de linha
        XXX YYY.
        **************************************************************************END*/
        automatoSimbolosBrancoE7(contLinha, numLinha, linha);

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
    int i = 0;
    int state = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
    printf("\n");

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
    } else {
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
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;


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
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;

    //stateb2 == 2 || stateb2 == 6 || stateb2 == 9 || stateb2 == 11 || stateb2 == 15 é aceito, caso contrario rejeitado
    while (i < contLinha) {
        if (stateb2 == 0) {
            if (linha[i] == 'i') {
                stateb2 = 1;
            } else if (linha[i] == 't') {
                stateb2 = 4;
            } else if (linha[i] == 'e') {
                stateb2 = 7;
            } else if (linha[i] == 'r') {
                stateb2 = 10;
            } else if (linha[i] == 'w') {
                stateb2 = 13;
            } else {
                stateb2 = 16;
            }
        } else if (stateb2 == 1) {
            if (linha[i] == 'f') {
                stateb2 = 2;
            } else {
                stateb2 = 16;
            }
        } else if (stateb2 == 4) {
            if (linha[i] == 'h') {
                stateb2 = 5;
            } else {
                stateb2 = 16;
            }
        } else if (stateb2 == 5) {
            if (linha[i] == 'e') {
                stateb2 = 6;
            } else {
                stateb2 = 16;
            }
        } else if (stateb2 == 7) {
            if (linha[i] == 'l') {
                stateb2 = 8;
            } else {
                stateb2 = 16;
            }
        } else if (stateb2 == 8) {
            if (linha[i] == 's') {
                stateb2 = 9;
            } else {
                stateb2 = 16;
            }
        } else if (stateb2 == 10) {
            if (linha[i] == 'e') {
                stateb2 = 11;
            } else if (linha[i] == 'e') {
                stateb2 = 14;
            } else {
                stateb2 = 16;
            }
        } else if (stateb2 == 14) {
            if (linha[i] == 'a') {
                stateb2 = 15;
            } else {
                stateb2 = 16;
            }
        }
        i++;
    }

     if (stateb2 == 2 || stateb2 == 6 || stateb2 == 9 || stateb2 == 11 || stateb2 == 15) {
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

void automatoComparacaoC2(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int statec2 = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;
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
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;

    //statec4 == 2 é aceito, caso contrario rejeitado
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

void automatoReaisD3(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int stated3 = 0;
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;


    //stated3 == 3 é aceito, caso contrario rejeitado
     while (i < contLinha) {
        switch (stated3) {
            case 0:
                /* CODE COMMENTS***************************************************************
                * Verifica se a linha excede o tamanho máximo permitido, se exceder cai no estado de rejeitado
                tem que ter no minimo 4 caracteres com sinal e no maximo 14 com sinal,
                XXX YYY.
                **************************************************************************END*/
                if (linha[i] == '-' && (contLinha < 4 || contLinha > 14)) {
                    stated3 = 1;

                } else {
                    /* CODE COMMENTS***************************************************************
                    * Verifica se a linha excede o tamanho máximo permitido, se exceder cai no estado de rejeitado
                    tem que ter no minimo 3 caracteres sem sinal e no maximo 13 sem sinal,
                    XXX YYY.
                    **************************************************************************END*/
                    if((linha[i] >= '0' && linha[i] <= '9') && (contLinha < 3 || contLinha > 13)){
                        stated3 = 1;
                    }else{
                        stated3 = 5;
                    }
                }

                break;

            case 1:
                if ((linha[i] >= '0' && linha[i] <= '9')) {
                    stated3 = 1;
                    if ((linha[i + 1] >= '0' && linha[i + 1] <= '9')) {
                        stated3 = 1;

                    } else {
                        stated3 = 2;
                    }

                } else {
                    stated3 = 5;
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
    } else {
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
    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;


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
    } else {
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

    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;

    //statee1 == 2 é aceito, caso contrario rejeitado
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

void automatoParentesesE2(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int statee2 = 0;

    //remove o pula linha, assim dando o valor real de caracteres
    contLinha = contLinha - 1;

    //statee2 == 2 é aceito, se não é rejeitado
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

void automatoSimbolosBrancoE7(int contLinha, int numLinha, char linha[500]){
    int i = 0;
    int statee7 = 0;

    //statee7 == 1 é aceito, caso contrário é erro
     while (i < contLinha) {
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



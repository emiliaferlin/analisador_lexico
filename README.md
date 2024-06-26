ANÁLISADOR LÉXICO QUE CONSIGA INTERPRETAR TAIS CADEIAS;
a) Comentários:

a.1) Cadeias de comentários: cadeias contidas entre chaves (inclusive), mono/multi-linhas ( {...} )
b) Identificadores*:
b.1) Variáveis, representadas por cadeias de tamanho variável:
            - Cadeias contendo: 1º símbolo letra, demais símbolos letras, dígitos ou sublinhado
            - Símbolos: letras A-Z,a-z, dígitos 0-9 e sublinhado
            - Tamanho: mínimo 1 símbolo, máximo 30 símbolos, excedentes devem ser descartados, indicando o descarte e o ponto onde iniciou

b.2) Palavras reservadas, representadas pelas seguintes cadeias fixas:
            if, then, else end, repeat, until | read, write
*Use o princípio da precedência de classe.
c.2) Comparações: menor-igual (<=), maior-igual (>=), igual (=), diferente (!=)

c.4) Atribuição: transferências de resultados de expressões para variável (:=), podendo ser variável uma expressão
d.3) Reais**: cadeias contendo decimais positivos, negativos e sinal apenas quando negativo, formato iii.nnn, onde: ‘iii’ indica a parte inteira, ‘.’ o indicador decimal e ‘nnn’ a parte não inteira
            - Tamanho: mínimo 3 símbolos -> ‘i.n’, máximo 13 símbolos -> ‘iiiiiii.nnnnn’, mais o sinal ( - )
d.6) String: cadeias delimitados por aspas duplas ( “”, inclusive), contendo qualquer símbolo entre os códigos 32 e 126 da tabela ASCII, exceto os delimitadores ( “” ), mono/multi-linhas

           - Tamanho: cadeias entre 0 e 126 símbolos, desconsiderando os delimitadores; cadeias maiores que 126 símbolos devem ser consideradas rejeitadas !
e) Símbolos especiais:

e.1) Separador de sentenças: ponto e vírgula (;)

e.2) Parênteses: contêiner para associações, usado em expressões ( (...) )
e.7) Símbolos branco: espaço ( ‘sp’  ASCII 32/20), tabulação ( ® ASCII 32/09), salto de linha ( LF ASCII 10/0A ), retorno de carro ( CR ASCII 13/0D)


1.2 - Identificadores para cada classe de cadeia (lexemas) de linguagens de programação definidas no item 1.1:

a.1) Comentários: TKN_COMMENT

b.1) Variáveis: TKN_VAR

b.2) Palavras reservadas: TKN_RESWORD

c.1) Aritméticas: TKN_SUM (+), TKN_ SUB (-), TKN_ MUL (*), TKN_DIV (/), TKN_MOD (%)

c.2) Comparações: TKN_LTEQ (<=), TKN_GTEQ (>=), TKN_EQ (=), TKN_DIFF (!=)

c.3) Lógicas: TKN_AND (&), TKN_OR (|), TKN_NOT (~), TKN_XOR (^)

c.4) Atribuição: TKN_ASSIGN (:=)

d.1) Naturais: TKN_NUMNAT números

d.2) Inteiros: TKN_NUMINT números

d.3) Reais: TKN_NUMREAL números

d.4) Octais: TKN_NUMOCT números

d.5) Hexadecimais: TKN_NUMHEX números

d.6) String: TKN_STR cadeias de símbolos diversos

e.1) Separador de sentenças: TKN_STMSEP (;)

e.2) Parênteses: TKN_LEFTPAR, TKN_RIGHTPAR ( (...) )

e.7) Cadeias não reconhecidas: TKN_REJECT

 

1.3 - Mecanismo para verificação das cadeias (teste):

a) Entrada: mecanismo para verificação das cadeias de entrada
            - Arquivo texto: cadeias de entrada lidas de um arquivo texto
            - Verificação: testar todas as cadeias/combinações aceitas pelas estruturas definidas no item 1.1 e atribuídas ao seu grupo; teste também cadeias rejeitadas de forma a evidenciar a eficácia do scanner
            - Sugestão de entrada: escreva cadeias que representem cada estrutura definida no item 1.1 e atribuída ao seu grupo; creia duas seções no arquivo, uma para cadeias aceitas outra para rejeitadas, indicando com os rótulos {Accepts} e {Rejects}

b) Saída: mecanismo para apresentar o resultado da análise léxica
            - Saída padrão (StdOut): envie para StdOut o resultado de cada cadeia de entrada do item a.1 (acima), conforme padrão de saída especificado a seguir
            - Formato da saída:  a saída para cada cadeia de entrada deve seguir o seguinte formato:
#Linha -> Id_Class -> Accept|Reject -> cadeia_processada

A saída é composta de 4 campos, onde:
#Linha             : indica ‘#’ seguido do número da linha(s) em que a cadeia está inserida (ex: #01-03)
Id_Class          : identificador da classe da cadeia, conforme especificado no item 1.2
Accept|Reject   : termo que indica se cadeia foi aceita ou rejeitada, respectivamente
cadeia_processada: apresenta a cadeia de entrada analisada

 

1.4 - Metodologia de desenvolvimento do analisador léxico

a) Construa os autômatos individuais para cada cadeia do item 1.1, atribuídas ao grupo.

b) Construa o autômato geral, que une todos os autômatos do item ‘a’ logo acima.
-->Para representar os autômatos sugere-se preferencialemente usar a ferramenta JFlap , disponível em: https://www2.cs.duke.edu/csed/jflap/

c) Implemente o Scanner em linguagem C*, preferencialmente em ambiente GNU/Linux, onde será avaliado.

* Embora não recomendado faculta-se o uso da linguagem C++.

* Não use bibliotecas dependentes de ambiente (especialmente Windows), recomenda-se usar o padrão C-ANSI.

* IMPORTANTE: em nenhuma hipótese, poderão ser usadas bibliotecas que substituam a dinâmica da análise léxica de forma a automatizar ou alterar o processo de análise. Caso sejam utilizados tais mecanismos, a atividade não será avaliada, portanto zerada.

d) Implemente o código do analisador léxico com base em um dos algoritmos estudados (Cp-C2 - Análise Léxica (Scanner) slide 39 a 42).

e) Teste seu Scanner de forma a validar todas as cadeias de entrada a serem reconhecidas bem como cadeias que não devam ser reconhecidas, isto permite validar a cobertura da implementação, tanto para cadeias de entrada aceitas como rejeitadas.

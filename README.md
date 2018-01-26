<!--
Projeto de Introdução à Computação 2ª época 2017/2018 (c) by Nuno Fachada

Projeto de Introdução à Computação 2ª época 2017/2018 is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
-->

# Projeto de Introdução à Computação 2ª época 2017/2018

## Descrição do problema

Pretende-se que os alunos desenvolvam um jogo/simulador no qual zombies
perseguem e infetam humanos. O jogo desenrola-se numa grelha 2D limitada nos
lados (não toroidal<sup>[1](#fn1)</sup>) com dimensões _X_ e _Y_ e vizinhança
de Von Neumman<sup>[2](#fn2)</sup>. Em cada célula da grelha pode estar no
máximo um agente, que pode ser um **zombie** ou um **humano**. No início da
simulação existem _n<sub>z</sub>_ zombies e _n<sub>h</sub>_ humanos, num total
de _n = n<sub>z</sub>_ + _n<sub>h</sub>_ agentes. Os agentes devem ser
espalhados aleatoriamente pela grelha no início de cada jogo.

O jogo é _turn-based_, e em cada _turn_ (iteração) cada agente pode realizar
uma ação. Os humanos podem apenas realizar um tipo de ação: movimento. Os
zombies podem realizar dois diferentes tipos de ação: 1) movimento; e, 2)
infeção de humanos. O movimento dos agentes pode ser realizado para uma célula
vazia numa vizinhança de Von Neumman de raio 1. A infeção de humanos pode ser
realizada por zombies quando o humano está numa célula adjacente na vizinhança
de Von Neumman. A ordem em que os agentes executam as suas ações em cada _turn_
é aleatória<sup>[3](#fn3)</sup>, de modo a que nenhum agente em específico
obtenha a vantagem de agir cedo durante todo o jogo.

Os agentes podem ser controlados pelo computador através de uma Inteligência
Artificial (IA) básica, ou podem ser controlados por jogadores. Neste último
caso, um jogador que controle determinado agente pode decidir o destino do
mesmo. Se o agente for um zombie, a ação de infeção equivale à indicação de
movimento para o local onde está um humano. Nesse caso o zombie não se move
(pois o local já está ocupado pelo humano), mas o humano é convertido em
zombie. Se o humano era controlado por um jogador, deixa de o ser, e passa a
ser controlado pela IA. O jogo termina quando não existirem mais agentes do
tipo humano na grelha.

Caso um agente seja controlado pela IA, as suas decisões dependem do tipo de
agente:

* Humano - Tenta mover-se na direção oposta ao zombie mais próximo. Se a célula
  para onde o humano deseja mover-se estiver ocupada, o humano fica no mesmo
  local.
* Zombie - Caso exista um humano numa célula adjacente, infeta-o. Caso
  contrário, tenta mover-se na direção do humano mais próximo. Se a célula para
  onde o zombie deseja mover-se estiver ocupada, o zombie fica no mesmo local.

O jogo termina quando o número máximo de _turns_ for atingido, ou quando não
existirem mais humanos na simulação.

## Modo de funcionamento

### Invocação do programa

O programa deve aceitar sete opções na linha de comando<sup>[4](#fn4)</sup>:

* `-x` - Dimensão horizontal da grelha de jogo.
* `-y` - Dimensão vertical da grelha de jogo.
* `-z` - Número total de zombies.
* `-h` - Número total de humanos.
* `-Z` - Número de zombies controlados por jogadores.
* `-H` - Número de humanos controlados por jogadores.
* `-t` - Número máximo de _turns_.

Um exemplo de execução:

```
./jogo -x 20 -y 20 -z 10 -h 30 -Z 1 -H 2 -t 1000
```

As opções indicadas são obrigatórias e podem ser dadas em qualquer ordem, desde
que o valor numérico suceda à opção propriamente dita. Se alguma das opções for
omitida o programa deve terminar com uma mensagem de erro para `stderr`,
indicando o modo de uso.

### Modos de jogo

#### Modo automático

O programa entra em modo automático quando não existem agentes controlados
por jogadores. Neste modo o jogo desenrola-se sem intervenção direta do
utilizador. A visualização deve ser atualizada no fim de cada _turn_ (pelo
menos). No entanto, de modo a ser possível observar a evolução da simulação,
poderá ser boa ideia solicitar ao utilizador para pressionar uma tecla ou
clicar num botão antes de se dar início à próxima _turn_.

#### Modo interativo

Este modo é semelhante ao automático, apenas com duas pequenas diferenças: 1)
cada vez que um agente controlado pelo jogador é chamado a agir, o programa
fica a aguardar o _input_ do jogador sobre que ação tomar; e, 2) a visualização
do jogo deve ser atualizada imediatamente antes de ser solicitado _input_ a um
jogador (pelo menos). Se a dada altura deixarem de existir agentes controlados
pelo jogador, o programa entra em modo automático.

<a name="visualize"></a>

## Visualização do jogo

A visualização do jogo deve ser feita com recurso a uma biblioteca gráfica ou
de jogos, e deve obedecer à interface fornecida no ficheiro
[showworld.h](code/showworld.h). Relativamente à biblioteca, algumas sugestões:

* [g2] - Simples mas limitada.
* [Ncurses] - ASCII art (texto), ver referência [\[2\]](#ref2).
* [Allegro5] - Bom meio termo, com bons exemplos em C.
* [SDL2] - Muito versátil e abrangente, mas poucos exemplos em C.
* [Raylib] - Muito interessante, mas instalação no Ubuntu não é trivial (ver
  instruções no Wiki da [página no GitHub][Raylib-gh]).

Relativamente à interface fornecida no ficheiro
[showworld.h](code/showworld.h), a mesma declara uma série de tipos e funções
que devem ser respeitados na parte de visualização do jogo. Os alunos devem ler
com atenção os comentários no código deste ficheiro para perceberem como devem
implementar o corpo das funções de visualização. O ficheiro
[showworld_simple.c](code/showworld_simple.c) oferece uma implementação
simples desta interface, com visualização em modo de texto, e que pode ser
usada numa primeira fase de desenvolvimento do projeto. A secção
[Código exemplo](#examplecode) contém mais informações sobre a visualização do
jogo.

## Objetivos, critério de avaliação e entrega

<a name="objetivos"></a>

### Objetivos

* Jogo deve funcionar como especificado.
* Código deve compilar sem erros no compilador [GCC] e/ou [Clang] com as opções
  `-std=c99 -Wall -Wextra -Wpedantic`.
* Código deve estar devidamente comentado e indentado.
* Tamanho da grelha e número de agentes não deve ser fixado no código, mas sim
  especificado no ficheiro de configuração.
* Documentação do projeto deve ser feita com [Doxygen].
* Programa deve estar organizado em vários ficheiros `.c` e `.h` com uso de
  _Makefile_.
* Visualização do jogo deve ser feita com recurso a uma biblioteca gráfica ou
  de jogos (ver secções [Visualização do jogo](#visualize) e
  [Código exemplo](#examplecode)).

### Critério de avaliação

O projeto, que tem um peso de 10 valores na nota final da disciplina, será
avaliado segundo os critérios indicados na [Tabela 1](#tabela1).

<a name="tabela1"></a>

**Tabela 1** - Critérios de avaliação.

| Critério                                               | Peso      |
|--------------------------------------------------------|-----------|
| Funcionamento segundo especificações                   | 2,0 val.  |
| Qualidade do código e das soluções<sup>[6](#fn6)</sup> | 1,5 val.  |
| Comentários e documentação com [Doxygen]               | 1,0 val.  |
| Relatório                                              | 1,0 val.  |
| Desenvolvimento do projeto com Git<sup>[7](#fn7)</sup> | 1,0 val.  |
| Tamanho da grelha/número de agentes variável           | 1,0 val.  |
| Visualização com recurso a biblioteca externa          | 1,0 val.  |
| Organização do projecto e _Makefile_                   | 1,5 val.  |

### Entrega

O projeto deve ser entregue via Moodle até às 23h de 18 de fevereiro de 2018.
Deve ser submetido um ficheiro `zip` com os seguintes conteúdos:

* Ficheiros `.c` e `.h`, ficheiro `Makefile`, ficheiro `Doxyfile` e ficheiro
  `.gitignore`.
* Pasta escondida `.git` contendo o repositório Git local do projeto.
* Ficheiro `README.md` contendo o relatório do projeto em formato [Markdown]
  organizado da seguinte forma:
  * Título do projeto.
  * Nome dos autores (primeiro e último) e respetivos números de aluno.
  * Descrição da solução:
    * Arquitetura da solução, com breve explicação de como o programa foi
      estruturado.
      * Um fluxograma simples ou gráficos semelhantes à Figura [1](#figura1)
        são bem vindos.
    * Estruturas de dados: grelha de simulação, agentes, outras estruturas
      auxiliares relevantes.
    * Algoritmos: procura de agente mais próximo, cálculo de direção na grelha,
      _shuffling_ (embaralhamento) dos agentes antes de cada _turn_, outros
      algoritmos relevantes.
  * Manual de utilizador:
    * Como compilar: qual o comando ou comandos gerar uma _build_ do jogo.
    * Como jogar: que teclas pressionar e/ou onde clicar para mover agentes
      (modo interativo); tecla e/ou botão para passar para a próxima _turn_
      (modo automático); outras funcionalidades importantes que o utilizador
      possa controlar.
  * Conclusões e matéria aprendida.
  * Referências:
    * Incluindo trocas de ideias com colegas, código aberto reutilizado e
      bibliotecas de terceiros utilizadas. Devem ser o mais detalhados possível.
  * **Nota:** o relatório deve ser simples e breve, com informação mínima e
    suficiente para que seja possível ter uma boa ideia do que foi feito.

**Atenção**: Todos os ficheiros C e Markdown devem ser gravados em codificação
UTF-8<sup>[5](#fn5)</sup>.

<a name="extensoesop"></a>

## Notas adicionais e material didático para desenvolvimento do projeto

Esta secção apresenta algumas notas adicionais, bem como algum material
didático para auxiliar no desenvolvimento do projeto.

### Sugestões para o desenvolvimento do projeto

1. Devem começar o projeto a partir do código disponibilizado na pasta
   [code](code). Se usarem [Git], o primeiro _commit_ do projeto pode conter
   exatamente os ficheiros que compõem este exemplo<sup>[11](#fn11)</sup>.
2. Ler e reler o enunciado até deixarem de existir dúvidas sobre o mesmo. Se as
   mesmas persistirem, entrem em contato com o docente para esclarecimentos
   adicionais.
3. Fazer um plano de desenvolvimento do projeto. As seguintes limitações são
   aceitáveis numa primeira fase: 1) fixar no código (usando constantes) o
   tamanho do mundo de jogo, o número de agentes, e restantes parâmetros de
   configuração do jogo; e, 2) usar as funções no ficheiro
   [showworld_simple.c](code/showworld_simple.c) (ver secção
   [Visualização do jogo](#visualize)) para visualização do mundo de jogo. Numa
   segunda fase, quando os básicos estiverem todos a funcionar, podem então: 1)
   implementar o tratamento das opções de linha de comandos; 2) usar
   alocação/libertação de memória para terem tamanhos variáveis do mundo e
   número de agentes; e, 3) implementar visualização com uma biblioteca gráfica
   externa.
4. Dividir bem o trabalho entre os diferentes elementos do grupo.
5. Organizar as estruturas e funções em ficheiros separados em volta de um
   conceito comum: coordenada, agente, grelha, etc. Por exemplo, no caso das
   coordenadas podem desenvolver um módulo (e.g. `coordenadas.c` e
   `coordenadas.h`), onde definem o tipo `COORD` para coordenadas 2D em grelha
   toroidal com vizinhança de Von Neumman, e todas as funções que operam sobre
   variáveis desse tipo (e.g. deslocamento, comparação de coordenadas,
   distância, direção entre uma coordenada e outra, etc).
6. As funções devem ser pequenas e com responsabilidades bem definidas. Se uma
   função começar a ficar muito grande, devem considerar dividir a função em
   várias funções.
7. Existem uma série de ferramentas úteis que podem facilitar bastante o
   desenvolvimento do projeto, como por exemplo:
    * [Git] para colaboração e controlo de versões do código fonte.
      * Tendo em conta a complexidade do projeto, que requer a experimentação
        de diferentes abordagens e uma colaboração de facto entre todos os
        membros do grupo, o uso de [Git] pode facilitar bastante o
        desenvolvimento do projeto<sup>[7](#fn7),[11](#fn11)</sup>.
    * [cppcheck] para verificação estática do código fonte.
      * O [cppcheck] (e outras ferramentas similares) fazem uma verificação
        mais aprofundada do código, detetando possíveis problemas como
        operações entre tipos diferentes, ficheiros não devidamente fechados ou
        acesso potencial a zonas inválidas da memória. Para o código deste
        projeto, o [cppcheck] pode ser invocado na pasta do projeto da seguinte
        forma: `cppcheck --enable=all --language=c --platform=unix64
        --std=c99 *.c`.
    * [Valgrind] para verificação dinâmica do programa.
      * Ao contrário do [cppcheck], o [Valgrind] tenta detetar _bugs_ no
        programa enquanto o mesmo está a ser executado. É especialmente útil
        para descobrir erros de acesso à memória e verificar se toda a memória
        alocada foi devidamente libertada. Caso o executável do projeto se
        chame `zombies`, o [Valgrind] pode ser usado para verificar o programa
        da seguinte forma: `valgrind --leak-check=full ./zombies`.
    * [GDB] para execução passo a passo e _debugging_ do programa.
      * Tal como discutido na aula 4, o [GDB] permite executar programas passo
        a passo (desde que tenham sido compilados com a opção `-g`). Muitas
        vezes é a única forma de se perceber o que o código está realmente a
        fazer e corrigir _bugs_ complicados. Caso o executável do projeto se
        chame `zombies`, o [GDB] pode ser usado para executar o programa da
        seguinte forma: `gdb ./zombies`.

<a name="examplecode"></a>

### Código exemplo

A pasta [code](code) contém codigo auxiliar para desenhar o mundo do jogo. A
[Figura 1](#figura1) mostra como o código está organizado.

<a name="figura1"></a>

![arquitectura](https://user-images.githubusercontent.com/3018963/34787896-c2f7e734-f630-11e7-8947-2ac796bad33d.png)

**Figura 1** - Organização do código auxiliar para desenhar o mundo do jogo no
ecrã.

O ficheiro [showworld.h](code/showworld.h) declara seis tipos e/ou funções que
devem ser usados para o desenvolvimento da parte de visualização do projeto,
nomeadamente:

* [`AGENT_TYPE`](code/showworld.h#L34) - Enumeração que define os diferentes
  tipos de agente, tal como indicado na [Tabela 3](#tabela3).
* [`SHOWWORLD`](code/showworld.h#L45) - Tipo abstrato que representa o
  _display_ ou visualização do mundo de simulação.
* [`get_agent_info_at`](code/showworld.h#L52) - Tipo de função que retorna
  informação sobre um agente em dado local do mundo de jogo.
* [`showworld_new`](code/showworld.h#L71) - Função para criar um _display_ ou
  visualização do mundo de jogo (objeto do tipo `SHOWWORLD`).
* [`showworld_destroy`](code/showworld.h#L84) - Função para libertar memória
  associada a um _display_ ou visualização do mundo de jogo (objeto do tipo
  `SHOWWORLD`).
* [`showworld_update`](code/showworld.h#L91) - Função que atualiza o _display_
  / visualização do mundo de jogo.

O ficheiro [showworld_simple.c](code/showworld_simple.c) define uma
implementação concreta dos tipos e/ou funções declaradas de forma abstrata na
interface [showworld.h](code/showworld.h), podendo ser utilizado numa primeira
fase de desenvolvimento do projeto. Quando o projeto estiver a funcionar
adequadamente, os alunos devem criar uma implementação concreta da visualização
do jogo que faça uso de uma biblioteca gráfica, tal como indicado
[anteriormente](#visualize). Para o efeito devem substituir o ficheiro
[showworld_simple.c](code/showworld_simple.c) por outra implementação, mas que
continue a obedecer à interface definida em [showworld.h](code/showworld.h).

Por sua vez, o ficheiro [example.c](code/example.c) contém um exemplo de como
usar a interface definida em [showworld.h](code/showworld.h).

As próximas subsecções descrevem em detalhe a implementação
[showworld_simple.c](code/showworld_simple.c), e como os alunos podem criar a
sua própria implementação da visualização.

#### Exemplo de implementação: showworld_simple.c

A implementação de visualização definida no ficheiro
[showworld_simple.c](code/showworld_simple.c) mostra o mundo do jogo no
terminal, indicando se o agente é zombie (`z`) ou humano (`h`), o ID do agente
em hexadecimal (por exemplo, `z0A`), e diferenciando com `Z` ou `H` maiúsculo
caso o agente em questão seja controlado por um jogador (por exemplo, `H19`).
Caso não exista um agente na célula em questão, é impresso um ponto (`.`). Para
um mundo 5x5 com 4 zombies e 1 humano, com um dos zombies controlado por um
jogador, a implementação mostra algo parecido com a [Figura 2](#figura2).

<a name="figura2"></a>

```
.   .  Z02  .   .

.  z00  .   .   .

.   .   .   .   .

.   .  z03  .   .

.  z01  .  h04  .
```

**Figura 2** - Exemplo do mundo de jogo com dimensões 5x5, tal como mostrado
na implementação de visualização definida em
[showworld_simple.c](code/showworld_simple.c).

##### Implementação do objeto SHOWWORLD para visualização do mundo de simulação

O tipo concreto `SHOWWORLD` está definido como uma [estrutura com três
campos](code/showworld_simple.c#L36): `xdim`, `ydim` e `aginfo_func`. Os dois
primeiros campos representam o tamanho horizontal e vertical do mundo de jogo,
respetivamente. O terceito campo é do tipo
[`get_agent_info_at`](code/showworld.h#L52), ou seja, representa um apontador
para uma função que retorna informação sobre um agente em dado local do mundo
de jogo.

Não é preciso nada de mais, uma vez que este tipo de visualização é muito
simples.

##### Implementação da função showworld_new()

A [implementação](code/showworld_simple.c#L50) desta função aloca memória para
um objeto do tipo [`SHOWWORLD`](code/showworld_simple.c#L36), guardando nos
campos dessa estrutura o tamanho do mundo e o apontador para a função que
retorna informação sobre um agente em dado local do mundo de jogo, do tipo
[`get_agent_info_at`](code/showworld.h#L52).

##### Implementação da função showworld_destroy()

Uma vez que apenas foi efetuada uma
[alocação de memória](code/showworld_simple.c#L60) para criação do objeto
`SHOWWORLD`, a função [showworld_destroy()](code/showworld_simple.c#L68)
simplesmente liberta essa memória usando a função `free()`.

##### Implementação da função showworld_update()

Esta função vai mostrar o mundo do jogo tal como aparece na
[Figura 2](#figura2). A função não devolve nada (`void`), mas aceita dois
argumentos. O primeiro, de nome `sw`, é um objeto do tipo `SHOWWORLD` que
contém informação sobre o _display_ / visualização do jogo. O segundo, de nome
`w`, é do tipo `void *` (apontador genérico), e aponta para a estrutura de
dados que contém o mundo do jogo.

Como é possível observar no [código](code/showworld_simple.c#L76), esta
implementação da função `showworld_update()` percorre todas as células da
grelha de simulação, por linha e por coluna, obtém informação sobre o agente em
cada posição (usando o apontador para função guardado num dos campos da
variável `sw`), e imprime no ecrã, de forma formatada, a informação obtida.
Esta função não precisa de saber nada sobre o mundo de simulação, apontado pela
variável `w`, pois este é passado como argumento e interpretado pela função
apontada por `sw->aginfo_func`.

#### Apontador para função do tipo get_agent_info_at

Existe ainda uma questão crucial e não esclarecida. Onde está definida a
estrutura de dados que contém o mundo de simulação, bem como a função que a
sabe interpretar? A reposta é a seguinte: tanto a estrutura de dados, bem como
a função que a interpreta, devem ser desenvolvidas no código do projeto. Uma
vez que o mundo de simulação vai ser definido de forma específica por cada
grupo, faz então sentido que a função que obtém informação sobre um agente em
determinada localização no mundo seja também definida pelo grupo. Esta função
deve obedecer ao tipo `get_agent_info_at`, definido na interface
[showworld.h](code/showworld.h#L52). No caso do código exemplo, a função está
definida no ficheiro [example.c](code/example.c#L207).

##### Como funcionam as funções do tipo get_agent_info_at?

As funções do tipo `get_agent_info_at` devem devolver um `unsigned int`
contendo informação sobre um agente, recebendo como argumentos a variável `w`
(apontador genérico para o mundo do jogo), bem como as coordenadas `(x,y)` da
posição sobre a qual se pretende obter informação. O `unsigned int` com
informação sobre um agente está organizado internamente como indicado na
[Tabela 2](#tabela2).

<a name="tabela2"></a>

**Tabela 2** - Informação sobre um agente tal como devolvida por funções do
tipo `get_agent_info_at`.

| Bits            | _31–19_ | _18–3_       | _2_             | _1–0_          |
|-----------------|---------|--------------|-----------------|----------------|
| **Significado** | Livre   | ID do agente | Agente jogável? | Tipo de agente |


Os dois bits menos significativos, nas posições 0 e 1, representam o tipo de
agente. O bit na posição 2 indica se o agente é controlado por um jogador (`1`)
ou pela IA (`0`). Os bits entre as posições 3 e 18 contêm o ID do agente.
Finalmente, os bits mais significativos (posições 19 a 31) estão livres para
uso do aluno, caso assim o entenda.

Os possíveis tipos de agente (posições 0 e 1) estão definidos numa enumeração
de nome `AGENT_TYPE` no ficheiro [showworld.h](code/showworld.h#L34), tal como
indicado na [Tabela 3](#tabela3). O tipo `Unknown` nunca deve ocorrer. Se tal
acontecer, significa que o jogo tem um _bug_.

<a name="tabela3"></a>

**Tabela 3** - Tipos de agentes definidos na enumeração
[`AGENT_TYPE`](code/showworld.h#L34).

| Tipo      | Significado            | Código (dec.)  | Código (bin.)  |
|-----------|------------------------|----------------|----------------|
| `None`    | Nenhum agente presente | 0              | 00             |
| `Human`   | Agente humano          | 1              | 01             |
| `Zombie`  | Agente zombie          | 2              | 10             |
| `Unknown` | Agente desconhecido    | 3              | 11             |


#### Exemplo de uso

Um exemplo desta abordagem está disponível no ficheiro
[example.c](code/example.c). Este programa cria uma grelha de simulação de
dimensões 20x20, na qual os agentes são colocados aleatoriamente, invocando
depois a função `showworld_update()` para mostrar o mundo aleatoriamente
gerado. A grelha de simulação (mundo do jogo) é definida como um _array_
bidimensional de apontadores para agente, onde cada posição `[i][j]` do
_array_, correspondente a uma coordenada `(x,y)` no mundo do jogo, contém
um apontador para agente. Por sua vez, os agentes são definidos como uma
[estrutura de nome `AGENT` com três campos](code/example.c#L54): tipo de agente
(`AGENT_TYPE`), agente jogável (`unsigned char`, 0 ou 1), e ID do agente
(`unsigned short`). A função [`example_get_ag_info()`](code/example.c#L207),
que obedece ao tipo `get_agent_info_at`, sabe interpretar a variável `w` como
_array_ de apontadores para agente, sabendo também como obter informação sobre
um agente em determinada posição do _array_. Esta função é dada a conhecer ao
código de visualização durante a criação do objeto `SHOWWORLD`, sendo passada
como [último argumento da função `showworld_new()`](code/example.c#L94).

Convém referir que as estruturas de dados usadas neste exemplo poderão não ser
adequadas ou suficientes para o desenvolvimento do projeto.

## Honestidade académica

Nesta disciplina, espera-se que cada aluno siga os mais altos padrões de
honestidade académica. Isto significa que cada ideia que não seja do
aluno deve ser claramente indicada, com devida referência ao respectivo
autor. O não cumprimento desta regra constitui plágio.

O plágio inclui a utilização de ideias, código ou conjuntos de soluções
de outros alunos ou indivíduos, ou quaisquer outras fontes para além
dos textos de apoio à disciplina, sem dar o respectivo crédito a essas
fontes. Os alunos são encorajados a discutir os problemas com outros
alunos e devem mencionar essa discussão quando submetem os projetos.
Essa menção **não** influenciará a nota. Os alunos não deverão, no
entanto, copiar códigos, documentação e relatórios de outros alunos, ou dar os
seus próprios códigos, documentação e relatórios a outros em qualquer
circunstância. De facto, não devem sequer deixar códigos, documentação e
relatórios em computadores de uso partilhado.

Nesta disciplina, a desonestidade académica é considerada fraude, com
todas as consequências legais que daí advêm. Qualquer fraude terá como
consequência imediata a anulação dos projetos de todos os alunos envolvidos
(incluindo os que possibilitaram a ocorrência). Qualquer suspeita de
desonestidade académica será relatada aos órgãos superiores da escola
para possível instauração de um processo disciplinar. Este poderá
resultar em reprovação à disciplina, reprovação de ano ou mesmo
suspensão temporária ou definitiva da ULHT<sup>[12](#fn12)</sup>.

## Notas

<sup><a name="fn1">1</a></sup> Num mapa toroidal 2D, a grelha "dá a volta" na
vertical e na horizontal. Neste caso o mapa não é toroidal, sendo limitado
pelos lados, pelo que os agentes não podem "dar a volta" nesse sentido.

<sup><a name="fn2">2</a></sup> Numa grelha 2D, a
[vizinhança de Von Neumman](https://en.wikipedia.org/wiki/Von_Neumann_neighborhood)
é composta pela célula central, pelas células do lado direito e esquerdo e
pelas células em cima e em baixo.

<sup><a name="fn3">3</a></sup> Por outras palavras, a lista de agentes deve ser
embaralhada (_shuffled_) no início de cada _turn_. O algoritmo de
[Fisher–Yates](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
é um método de embaralhamento (_shuffling_) tipicamente utilizado para este
fim.

<sup><a name="fn4">4</a></sup> É relativamente simples tratar os argumentos da
linha de comandos, sobretudo no caso deste projeto. No entanto existem algumas
bibliotecas para o efeito, como por exemplo o
[Commandline option parser](https://developer.gnome.org/glib/2.54/glib-Commandline-option-parser.html)
da [GLib](https://developer.gnome.org/glib/2.54/), ou o
[Option parser](http://www.ucw.cz/libucw/doc/ucw/opt.html) da
[LibUCW](http://www.ucw.cz/libucw/).

<sup><a name="fn5">5</a></sup> Este pormenor é especialmente importante em
Windows pois regra geral a codificação UTF-8 não é usada por omissão. Em todo o
caso, e dependendo do editor usado, a codificação UTF-8 pode ser selecionada na
janela de "Save as"/"Guardar como", ou então nas preferências do editor.

<sup><a name="fn6">6</a></sup> A qualidade do código e das soluções inclui
vários aspetos, como por exemplo: 1) código bem indentado; 2) evitar código
"morto", que não faz nada, tal como variáveis ou funções nunca usadas; 3) as
soluções desenvolvidas são [simples][KISS] e/ou eficientes; 4) código compila
sem erros e _warnings_; 5) código devidamente organizado e dividido em funções
e ficheiros de forma lógica e bem estruturada; 6) código não acede a zonas não
alocadas da memória, como por exemplo índices fora dos limites de um _array_;
ou, 7) toda a memória alocada com as funções `malloc` e `calloc` é devidamente
libertada com a função `free`.

<sup><a name="fn7">7</a></sup> Neste projeto não é necessário fazer _fork_
deste repositório. Caso usem Git, os alunos podem inicializar um repositório
local vazio ou com os conteúdos da pasta [code](code) e desenvolver o projeto a
partir desse ponto. Dito isto, para um projeto desta dimensão e com grupos de
até 3 alunos, o uso de Git não é apenas recomendado para uma colaboração
eficiente: é absolutamente essencial. Caso usem um ou mais repositórios remotos
para colaboração devem indicar esse facto no relatório.

<sup><a name="fn8">8</a></sup>
[Application Programming Interface](https://en.wikipedia.org/wiki/Application_programming_interface).

<sup><a name="fn9">9</a></sup> Mais especificamente a ferramenta
[GNU Make][`make`], uma vez que existem várias variantes desta [abordagem de
automatização][Make] de _builds_, nomeadamente o programa [NMake] incluido com
o Microsoft Visual Studio. Apesar de ser orientada ao C e C++, a ferramenta
[Make] pode ser usada em projetos desenvolvidos em qualquer linguagem de
programação.

<sup><a name="fn10">10</a></sup> O Doxygen está disponível para _download_
[aqui](https://www.stack.nl/~dimitri/doxygen/download.html) (Linux/Windows/Mac).
Pode também ser instalado em Ubuntu com o comando `sudo apt install doxygen`,
ou através dos gestores de pacotes [Homebrew](https://brew.sh/) (macOS) e
[Chocolatey](https://chocolatey.org/) (Windows).

<sup><a name="fn11">11</a></sup> É também boa ideia criarem um ficheiro
[`.gitignore`](https://stackoverflow.com/questions/27850222/what-is-gitignore-exactly/27850270)
para evitar a inclusão de ficheiros binários no repositório (como por exemplo
ficheiros objeto ou o executável do projeto). O ficheiro `.gitignore` [incluido
neste repositório](https://github.com/VideojogosLusofona/ic2017p2/blob/master/.gitignore)
é um bom ponto de partida.

<sup><a name="fn12">12</a></sup> Texto adaptado da disciplina de [Algoritmos e
Estruturas de Dados][aed] do [Instituto Superior Técnico][ist].

## Referências

* <a name="ref1">\[1\]</a> Pereira, A. (2017). C e Algoritmos, 2ª edição. Sílabo.
* <a name="ref2">\[2\]</a> Reagan, P. (2014). [Game Programming in C with the
Ncurses Library](https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library),
Viget Labs.
* <a name="ref3">\[3\]</a> Marshall, D. (1999).
[Writing Larger Programs](http://users.cs.cf.ac.uk/Dave.Marshall/C/node35.html),
Cardiff School of Computer Science and Informatics.
* <a name="ref4">\[4\]</a> Sizer, B. (2013). [Organizing Code Files in C and C++](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/organizing-code-files-in-c-and-c-r3173), GameDev.net.
* <a name="ref5">\[5\]</a> Kieras, D. (2012). [C Header File Guidelines](http://umich.edu/~eecs381/handouts/CHeaderFileGuidelines.pdf),
EECS Department, University of Michigan.
* <a name="ref6">\[6\]</a> Ekstrand, J. (2013). [Header file best practices](http://www.jlekstrand.net/math/teaching/programming-course/unit-2/header-file-best-practice/),
Math Department, Iowa State University.
* <a name="ref7">\[7\]</a> Magnes, M. et al. (2012). [What should and what shouldn't be in a header file?](https://softwareengineering.stackexchange.com/questions/167723/what-should-and-what-shouldnt-be-in-a-header-file),
Software Engineering, StackExchange.com.
* <a name="ref8">\[8\]</a> Backus, J. et al. (2009). [Code organization style for C?](https://stackoverflow.com/questions/1479574/code-organization-style-for-c),
StackOverflow.com.
* <a name="ref9">\[9\]</a> Cronin, K. et al. [Organization of C files](https://stackoverflow.com/questions/47919/organization-of-c-files),
StackOverflow.com.
* <a name="ref10">\[10\]</a> "horseyguy" et al. [Good way to organize C source files?](https://stackoverflow.com/questions/1263480/good-way-to-organize-c-source-files),
StackOverflow.com.
* <a name="ref11">\[11\]</a> Allain, A. (2017). [Compiling and Linking](https://www.cprogramming.com/compilingandlinking.html),
CProgramming.com.

## Licenças

Todo o código neste repositório é disponibilizado através da licença [GPLv3].
O enunciado e restante documentação são disponibilizados através da licença
[CC BY-NC-SA 4.0].

## Metadados

* Autor: [Nuno Fachada]
* Curso:  [Licenciatura em Aplicações Multimédia e Videojogos][lamv]
* Instituição: [Universidade Lusófona de Humanidades e Tecnologias][ULHT]

[GPLv3]:https://www.gnu.org/licenses/gpl-3.0.en.html
[CC BY-NC-SA 4.0]:https://creativecommons.org/licenses/by-nc-sa/4.0/
[lamv]:https://www.ulusofona.pt/licenciatura/aplicacoes-multimedia-e-videojogos
[Nuno Fachada]:https://github.com/fakenmc
[ULHT]:https://www.ulusofona.pt/
[aed]:https://fenix.tecnico.ulisboa.pt/disciplinas/AED-2/2009-2010/2-semestre/honestidade-academica
[ist]:https://tecnico.ulisboa.pt/pt/
[Markdown]:https://guides.github.com/features/mastering-markdown/
[GCC]:https://gcc.gnu.org/
[Clang]:https://clang.llvm.org/
[Gedit]:https://wiki.gnome.org/Apps/Gedit
[Geany]:https://www.geany.org/
[Code::Blocks]:http://www.codeblocks.org/
[Atom]:https://atom.io/
[XCode]:https://developer.apple.com/xcode/
[Notepad++]:https://notepad-plus-plus.org/
[Remarkable]:https://remarkableapp.github.io/
[Git]:https://git-scm.com/
[repositório]:https://github.com/VideojogosLusofona/ic2017p1
[GitHub]:https://github.com/
[git-tutorial]:https://try.github.io/levels/1/challenges/1
[Moodle]:https://secure.grupolusofona.pt/ulht/moodle/
[GitLab]:https://gitlab.com/
[BitBucket]:https://bitbucket.org/
[NotABug]:https://notabug.org/
[StackEdit]:https://stackedit.io/editor
[(GitHub-Flavored) Markdown Editor]:https://jbt.github.io/markdown-editor/
[Doxygen]:http://www.stack.nl/~dimitri/doxygen/
[Ncurses]:https://www.gnu.org/software/ncurses/ncurses.html
[g2]:http://www.ncbr.muni.cz/~martinp/g2/index.html
[Allegro5]:http://liballeg.org/
[SDL2]:https://www.libsdl.org/
[raylib]:http://www.raylib.com/
[raylib-gh]:https://github.com/raysan5/raylib
[GDB]:https://www.gnu.org/software/gdb/
[cppcheck]:http://cppcheck.sourceforge.net/
[Valgrind]:http://valgrind.org/
[`make`]:https://www.gnu.org/software/make/manual/make.html
[Make]:https://en.wikipedia.org/wiki/Make_(software)
[NMake]:https://docs.microsoft.com/pt-pt/cpp/build/nmake-reference
[KISS]:https://en.wikipedia.org/wiki/KISS_principle

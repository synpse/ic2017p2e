<!--
2º Projeto de Introdução à Computação 2017/2018 (c) by Nuno Fachada

2º Projeto de Introdução à Computação 2017/2018 is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
-->

# 2º Projeto de Introdução à Computação 2017/2018

O projeto deve ser realizado em grupos de 2 a 3 alunos. A constituição dos
grupos deve ser comunicada ao docente até 4 de janeiro, data a partir da qual
se assume que os alunos não pretendem realizar o projeto na 1ª época.

## Descrição do problema

Pretende-se que os alunos desenvolvam um jogo/simulador no qual zombies
perseguem e infetam humanos. O jogo desenrola-se numa grelha 2D
toroidal<sup>[1](#fn1)</sup> com dimensões _X_ e _Y_ e vizinhança de
Moore<sup>[2](#fn2)</sup>. Em cada célula da grelha pode estar no máximo um
agente, que pode ser um **zombie** ou um **humano**. No início da simulação
existem _n<sub>z</sub>_ zombies e _n<sub>h</sub>_ humanos, num total de _n =
n<sub>z</sub>_ + _n<sub>h</sub>_ agentes. Os agentes devem ser espalhados
aleatoriamente pela grelha no início de cada jogo.

O jogo é _turn-based_, e em cada _turn_ (iteração) cada agente pode realizar
uma ação. Os humanos podem apenas realizar um tipo de ação: movimento. Os
zombies podem realizar dois diferentes tipos de ação: 1) movimento; e, 2)
infeção de humanos. O movimento dos agentes pode ser realizado para uma célula
vazia numa vizinhança de Moore de raio 1. A infeção de humanos pode ser
realizada por zombies quando o humano está numa célula adjacente na vizinhança
de Moore. A ordem em que os agentes executam as suas ações em cada _turn_ é
aleatória<sup>[3](#fn3)</sup>, de modo a que nenhum agente em específico
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

O programa deve aceitar como único parâmetro um ficheiro de configuração em
formato [INI]<sup>[4](#fn4)</sup>, de acordo com o seguinte exemplo:

```INI
; Dimensao da grelha de jogo
xdim=20
ydim=20
; Numero inicial de zombies e humanos
nzombies=20
nhumans=20
; Numero de zombies e humanos controlados por jogadores
nzplayers=0
nhplayers=1
; Numero de turns maximo
maxturns=1000
```

Os campos indicados no exemplo anterior são obrigatórios e o programa deve
saber interpretá-los corretamente. O programa deve ainda ignorar campos que
não conheça. Os alunos podem acrescentar campos que considerem úteis para o
desenvolvimento do projeto, mas estes devem ser opcionais. Por outras palavras,
o programa deve assumir valores por omissão para campos opcionais extra. Um
ficheiro INI usado para um projeto deve funcionar sem erros noutro projeto.

Senão for indicado o ficheiro de configuração, o programa deve terminar com uma
mensagem de erro para `stderr`, indicando o modo de uso.

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

## Objetivos, critério de avaliação e entrega

<a name="objetivos"></a>

### Objectivos

* Jogo deve funcionar como especificado.
* Código deve compilar sem erros no compilador [GCC] e/ou [Clang] com as opções
  `-std=c99 -Wall -Wextra -Wpedantic`.
* Código deve estar devidamente comentado e indentado.
* Tamanho da grelha e número de agentes não deve ser fixado no código, mas sim
  especificado no ficheiro de configuração.
* Documentação do projeto deve ser feita com [Doxygen] (ver secção
  [Documentação automática do código com Doxygen](#doxygen)).
* Programa deve estar organizado em vários ficheiros `.c` e `.h` com uso de
  _Makefile_ (ver secção [Divisão do código em vários ficheiros](#orgproj)).
* Visualização do jogo deve ser feita com recurso a uma biblioteca gráfica ou
  de jogos. Algumas sugestões:
  * [g2] - Simples mas limitada.
  * [Ncurses] - ASCII art (texto), ver referência [\[2\]](#ref2).
  * [Allegro5] - Bom meio termo, com bons exemplos em C.
  * [SDL2] - Muito versátil e abrangente, mas poucos exemplos em C.
  * [Raylib] - Muito interessante, mas instalação no Ubuntu não é trivial (ver
    instruções no Wiki da [página no GitHub][Raylib-gh]).

### Critério de avaliação

O projeto, que tem um peso de 8 valores na nota final da disciplina, será
avaliado segundo os critérios indicados na [Tabela 1](#tabela1).

<a name="tabela1"></a>

**Tabela 1** - Critérios de avaliação.

| Critério                                               | Peso      |
|--------------------------------------------------------|-----------|
| Funcionamento segundo especificações                   | 1,5 val.  |
| Qualidade do código e das soluções<sup>[6](#fn6)</sup> | 1,0 val.  |
| Comentários e documentação com [Doxygen]               | 1,0 val.  |
| Relatório                                              | 1,0 val.  |
| Desenvolvimento do projeto com Git<sup>[7](#fn7)</sup> | 0,5 val.  |
| Tamanho da grelha/número de agentes variável           | 1,0 val.  |
| Visualização com recurso a biblioteca externa          | 1,0 val.  |
| Organização do projecto e _Makefile_                   | 1,0 val.  |
| [Extensões opcionais e Global Game Jam](#gamejam)      | Bónus!    |

### Entrega

O projeto deve ser entregue via Moodle até às 23h de 21 de janeiro de 2018.
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
      * Um fluxograma simples ou gráficos semelhantes às Figuras [1](#figura1)
        e [3](#figura3) são bem vindos.
    * Estruturas de dados: grelha de simulação, agentes, outras estruturas
      auxiliares relevantes.
    * Algoritmos: procura de agente mais próximo, cálculo de direção na grelha,
      _shuffling_ (embaralhamento) dos agentes antes de cada _turn_, outros
      algoritmos relevantes.
  * Manual de utilizador:
    * Como compilar: qual o comando ou comandos gerar uma _build_ do jogo (ver
      secção [Divisão do código em vários ficheiros](#orgproj)).
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

<a name="gamejam"></a>

### Extensões opcionais, trabalho futuro e Global Game Jam

Caso os alunos atinjam todos os objetivos pretendidos, é possível estender e
melhorar o jogo de várias formas. A melhor forma de o fazer é durante a
[Global Game Jam]. Não existem restrições sobre melhorias a fazer, desde que o
jogo mantenha a suas premissas básicas:

* Zombies vs. Humanos numa grelha 2D toroidal.
* Implementado em C99 com bibliotecas C auxiliares.
* O ponto de partida deve ser o código entregue a 21 de janeiro.

Algumas sugestões:

* Melhor IA, sobretudo da parte dos humanos.
* Dar aos humanos alguma forma de se defenderem.
* Agentes com propriedades individuais como energia, capacidade de movimento,
  etc.
* _Power-ups_.
* Melhor integração com biblioteca preferida ([Ncurses], [Allegro5], [SDL2] ou
  [Raylib] – infelizmente a [g2] não é apropriada para jogos "a sério"):
  * Possibilitar controlo com o rato.
  * Adicionar som.
  * etc...

Caso optem por melhorar o jogo, podem fazer nova entrega até 29 de janeiro (ou
seja, logo após a [Global Game Jam]) para as melhorias e extensões serem tidas
em conta no bónus da nota final do projeto.

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
3. Fazer um plano de desenvolvimento do projeto e dividir bem o trabalho entre
   os diferentes elementos do grupo.
4. Organizar as estruturas e funções em ficheiros separados em volta de um
   conceito comum: coordenada, agente, grelha, etc. Por exemplo, no caso das
   coordenadas podem desenvolver um módulo (e.g. `coordenadas.c` e
   `coordenadas.h`), onde definem o tipo `COORD` para coordenadas 2D em grelha
   toroidal com vizinhança de Moore, e todas as funções que operam sobre
   variáveis desse tipo (e.g. deslocamento, comparação de coordenadas,
   distância, direção entre uma coordenada e outra, etc).
5. As funções devem ser pequenas e com responsabilidades bem definidas. Se uma
   função começar a ficar muito grande, devem considerar dividir a função em
   várias funções.
6. Existem uma série de ferramentas úteis que podem facilitar bastante o
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
7. Sugestao de divisão em duas partes (a fazer)

<a name="orgproj"></a>

### Divisão do código em vários ficheiros

#### Vantagens

Existem várias vantagens em dividir um programa por vários ficheiros, como por
exemplo [\[3\]](#ref3),[\[4\]](#ref4):

* Facilita cooperação entre vários programadores, uma vez que cada programador
  pode trabalhar num ficheiro ou grupo de ficheiros diferente sem receio de
  conflitos.
* Permite uma abordagem orientada a objetos. Por outras palavras, cada módulo
  (par de ficheiros `.c` e `.h`) pode definir um tipo (ou vários tipos
  relacionados), bem como, bem como operações (funções) sobre esse tipo ou
  tipo(s), e até possíveis constantes associadas. Isto leva a que os programas
  fiquem muito bem estruturados.
* Na sequência do ponto anterior, o código fica organizado em forma de módulos
  ou bibliotecas, sendo facilmente reutilizável noutros projetos e programas,
  reduzindo o tempo de desenvolvimento.
* Quando um ficheiro é modificado, apenas esse ficheiro precisa de ser
  recompilado para o programa ser reconstruído. O programa [`make`] automatiza
  este processo.

#### Como dividir um programa em vários ficheiros

Regra geral, existe um ficheiro `.c` principal que contém a função `main` e
eventualmente outras funções, variáveis ou definições diretamente relevantes
para o programa a ser desenvolvido. Os restantes ficheiros devem ser agrupados
em pares `.c` e `.h` (módulos) e disponibilizam funcionalidades específicas, na
prática sendo usados como bibliotecas locais de funções.

Tipicamente, quando se define um tipo, por exemplo uma `struct`, todas as
funções que acedem e/ou manipulam variáveis desse tipo são colocadas no mesmo
par `.c` e `.h` (módulo). Numa linguagem de programação orientada a objetos,
como o Java ou C#, os tipos são chamados de _classes_, as variáveis de dado
tipo são chamadas de _objetos_, e as funções que operam sobre dado tipo são
chamadas de _métodos_.

De modo a que os tipos (_classes_) e funções que operam sobre esses tipos
(_métodos_) possam ser utilizados por outros programas e funções, é necessário
colocar as declarações de tipos e os protótipos (cabeçalhos) das funções
associadas no ficheiro `.h` (_header file_), e posteriormente incluir
(`#include`) esse ficheiro no código no qual se pretende ter acesso à
funcionalidade desenvolvida. Cada ficheiro `.h` tem um ficheiro `.c`
correspondente, onde são colocados os corpos (definições) das funções, bem como
tipos e variáveis que apenas tenham relevância no contexto desse ficheiro (ou
seja, que não valha a pena tornar públicos). O ficheiro `.h` pode ser
considerado a parte pública do módulo (que pode ser usada por outro código),
enquanto o ficheiro `.c` contém a parte privada. A parte pública é também
denominada de interface ou API<sup>[8](#fn8)</sup> do módulo/biblioteca.

O exemplo dado na secção [Visualização do jogo](#visualize) segue esta
abordagem. As seguintes referências oferecem informação mais detalhada sobre
este tópico: [\[4\]](#ref4), [\[5\]](#ref5), [\[6\]](#ref6), [\[7\]](#ref7),
[\[8\]](#ref8), [\[9\]](#ref9) e [\[10\]](#ref10).

#### Como compilar e ligar (construir) um programa dividido em vários ficheiros

Embora seja normal usar o termo _compilação_ para nos referirmos à criação de
um ficheiro executável a partir de código C, o termo mais correto seria
_construção_. Na realidade, a construção (do inglês _build_) de um ficheiro
executável passa por duas fases:  compilação e ligação (do inglês _compile_ e
_link_, respetivamente). A primeira fase, compilação, consiste em processar e
converter um ficheiro `.c` num ficheiro _objeto_ com extensão `.o` contendo
código máquina (zeros e uns). No entanto estes ficheiros não podem ser
executados. Para tal, é necessário ligar (_link_) um ou mais ficheiros objeto
num ficheiro executável [\[11\]](#ref11). O processo de compilação e ligação é
chamado de construção (_build_), e é realizado implicitamente pelo compilador
quando invocado da forma que temos feito até agora. Por exemplo:

```
$ gcc -Wall -Wextra -Wpedantic -std=c99 -o meuprograma meuprograma.c
```

É possível construir (compilar e ligar) um programa dividido em vários
ficheiros numa só invocação do compilador, bastando para isso indicar todos os
ficheiros `.c` a serem incluídos. Nesse caso, a função `main` terá de existir
num e apenas num dos ficheiros `.c`. No caso do exemplo disponibilizado na
pasta [code](code), que contém dois ficheiros `.c`, o comando de construção
(compilação e ligação) será o seguinte:

```
$ gcc -Wall -Wextra -Wpedantic -std=c99 -o example example.c simple_showworld.c
```

Neste caso são apenas dois ficheiros, mas regra geral os projetos podem conter
muitos ficheiros, caso no qual o comando anterior fica bastante comprido. Além
disso, esta abordagem obriga a recompilar todos os ficheiros `.c`, mesmo
aqueles que não tenham sido alterados, tornando o processo de compilação muito
lento. Desta forma, é comum realizar as fases de compilação e ligação de forma
separada. A opção `-c` indica ao compilador para apenas compilar o ficheiro
`.c` especificado. No caso do exemplo disponibilizado, os seguintes comandos
vão compilar separadamente os ficheiros `example.c` e `simple_showworld.c`,
dando origem aos ficheiros `example.o` e `simple_showworld.o`:

```
$ gcc -Wall -Wextra -Wpedantic -std=c99 -c example.c
$ gcc -Wall -Wextra -Wpedantic -std=c99 -c simple_showworld.c
```

Agora podemos ligar os dois ficheiros objeto, de modo a criar o ficheiro
executável:

```
$ gcc example.o simple_showworld.o -o example
```

É de realçar que as opções típicas de compilação, `-Wall -Wextra -Wpedantic
-std=c99`, só são relevantes para a fase de compilação, não sendo necessárias
na fase de ligação. No entanto, se o programa a construir usar bibliotecas de
terceiros, as opções para especificar tais bibliotecas (`-l` e `-L`) são
passadas na fase de ligação.

No entanto esta abordagem manual para construção de um executável, com
compilação individual de módulos e posterior ligação dos mesmos, está ainda
longe de ser perfeita. Em primeiro lugar, seria necessário tomar nota dos
módulos que precisam de ser recompilados (ou poderíamos recompilar todos e
voltar à estaca zero em termos de eficiência). Além disso, é sempre necessário
executar vários comandos (um ou mais para compilação e um para fazer a
ligação). A forma clássica de automatizar o _build_ (construção) de projetos
C/C++ é através da ferramenta [`make`]<sup>[9](#fn9)</sup>, discutida na
próxima secção.

#### _Builds_ automáticas com a ferramenta Make

A ferramenta [`make`] automatiza todo o processo de construção (_building_),
nomeadamente as fases de compilação (_compiling_) e ligação (_linking_), de
projetos C/C++. Basta executar o comando `make` e o projeto é automaticamente
construído de forma eficiente, sendo recompilados apenas os módulos que foram
modificados. Experimenta fazê-lo com o código disponibilizado na pasta
[code](code) (`cd code` seguido de `make`).

A configuração de um projeto a ser construído com a ferramenta `make` é
realizada com recurso a um ficheiro de nome `Makefile`, que indica ao `make`
como compilar e ligar um programa. Uma `Makefile` simples consiste num conjunto
de "regras", cada uma com a seguinte forma:

```
target ... : prerequisites ...
	recipe
	...
	...
```

O _target_ (alvo) é geralmente o nome de um ficheiro a ser gerado, como por
exemplo ficheiros executáveis ou ficheiros objeto. Um _target_ também pode ser
o nome de uma ação a realizar, como por exemplo `clean`. Neste último caso
diz-se que o _target_ é "Phony" (falso). Um _prerequisite_ (pré-requisito) é um
ficheiro usado como _input_ para geração do _target_. Geralmente um _target_
depende de vários ficheiros. Uma _recipe_ (receita) é uma ação a ser executada
pelo `make`, e pode ser composta por um ou mais comandos. É necessário colocar
um TAB no início de cada linha da receita, caso contrário o `make` não funciona
como pretendido. Tipicamente uma _recipe_ está numa regra com pré-requisitos e
serve para gerar o _target_ caso algum dos pré-requisitos tenha sido modificado
desde a última geração desse _target_. Nem todas as regras precisam de
pré-requisitos. Por exemplo, a regra para apagar todos os ficheiros gerados
(cujo _target_ é normalmente chamado `clean`) não tem pré-requisitos. Uma
possível `Makefile` para o exemplo disponibilizado na pasta [code](code) terá o
seguinte conteúdo:

```
example: example.o simple_showworld.o
	gcc example.o simple_showworld.o -o example

example.o: example.c simple_showworld.h showworld.h
	gcc -Wall -Wextra -Wpedantic -std=c99 -g -c -o example.o example.c

simple_showworld.o: simple_showworld.c simple_showworld.h
	gcc -Wall -Wextra -Wpedantic -std=c99 -g -c -o simple_showworld.o simple_showworld.c

clean:
	rm -f example *.o
```

A primeira regra é invocada por omissão quando o `make` é executado sem
argumentos. O _target_ desta regra é o ficheiro executável `example`, que
depende dos ficheiros `example.o` e `simple_showworld.o` para ser gerado (neste
caso através de ligação/_linking_). Uma vez que inicialmente nenhum dos
ficheiros objeto existe, a receita dessa regra não pode ser imediatamente
executada. O `make` vai então procurar outras regras cujo _target_ tem o nome
de cada um desses pré-requisitos. Uma vez que a segunda e terceira regras têm
_targets_ com esses nomes, o `make` vai tentar executar as respetivas receitas.
Dado que os pré-requisitos destas regras já existem (ficheiros `.c` e `.h`), as
respetivas receitas podem ser executadas, gerando dessa forma os dois ficheiros
objeto através de compilação dos respetivos ficheiros `.c`. Após esta fase, o
`make` já pode então invocar a receita da primeira regra, que vai criar o
ficheiro executável `example` ligando (_linking_) os ficheiros objeto
entretanto gerados.

Posteriormente, se modificarmos apenas o ficheiro `example.c` e voltarmos a
executar o `make`, apenas a segunda regra (compilação de `example.c`) e a
primeira regra (ligação dos ficheiros `.o`) serão executadas. O `make` sabe que
não é necessário voltar a gerar, através de compilação, o ficheiro
`simple_showworld.o`, uma vez que nenhum dos seus pré-requisitos foi
modificado.

O comando `make` pode aceitar como argumentos o nome dos _targets_. Ou seja, se
executarmos o comando `make clean`, a receita cujo _target_ tem esse nome vai
ser executada. Neste caso, esta receita corre o comando `rm -f example *.o`,
que elimina o ficheiro executável e os ficheiros objeto gerados.

Esta versão da `Makefile` funciona perfeitamente, mas pode ser melhorada. Em
primeiro lugar, estamos a repetir os argumentos de compilação em dois locais.
Além disso, o nome do executável aparece em vários locais. Felizmente as
`Makefiles` suportam variáveis nas quais podemos guardar opções que são
utilizadas várias vezes. A segunda versão da nossa `Makefile` poderia ter então
a seguinte forma:

```
CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -g
PROGRAM=example

$(PROGRAM): $(PROGRAM).o simple_showworld.o
	$(CC) $(PROGRAM).o simple_showworld.o -o $(PROGRAM)

$(PROGRAM).o: $(PROGRAM).c simple_showworld.h showworld.h
	$(CC) $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).c

simple_showworld.o: simple_showworld.c simple_showworld.h
	$(CC) $(CFLAGS) -c -o simple_showworld.o simple_showworld.c

clean:
	rm -f $(PROGRAM) *.o
```

É conveniente usar comentários para um melhor entendimento do conteúdo das
`Makefiles`. Os comentários começam com o caráter `#` (cardinal), tal como nos
_shell scripts_. Além disso, como o _target_ `clean` não corresponde a um
ficheiro, é boa prática indicar este facto na `Makefile`, de modo a que o
`make` não se confunda caso venha a existir um ficheiro com esse nome. Esta
indicação é feita com o _target_ especial `.PHONY`, colocado imediatamente
antes do _target_ em questão. Com esta informação chegamos a uma terceira
versão da nossa `Makefile`:


```
# Compilador C
CC=gcc
# Argumentos (flags) de compilacao
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -g

# Nome do programa
PROGRAM=example

# Regra para geral executavel
$(PROGRAM): $(PROGRAM).o simple_showworld.o
	$(CC) $(PROGRAM).o simple_showworld.o -o $(PROGRAM)

# Regra para gerar o ficheiro objeto com o mesmo nome do executavel
$(PROGRAM).o: $(PROGRAM).c simple_showworld.h showworld.h
	$(CC) $(CFLAGS) -c -o $(PROGRAM).o $(PROGRAM).c

# Regra para gerar o ficheiro objeto simple_showworld.o
simple_showworld.o: simple_showworld.c simple_showworld.h
	$(CC) $(CFLAGS) -c -o simple_showworld.o simple_showworld.c

# Regra para limpar todos os ficheiros gerados (executavel e objetos)
.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
```

A ferramenta `make` é bastante "inteligente", sobretudo quando se trata da
construção (_building_) de projetos C/C++. Nomeadamente, o `make` pode
determinar automaticamente as receitas para compilação e ligação (_compiling_
and _linking_) dos diferentes _targets_. Para o efeito é necessário definir
algumas
[variáveis especiais](https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html).
Na `Makefile` anterior já usamos duas destas variáveis: `CC` e `CFLAGS`. A
primeira especifica o programa a ser usado como compilador C, enquanto a
segunda define as opções (_flags_) a usar na fase de compilação. Existem outras
variáveis especiais importantes para compilação de projetos C, das quais duas
serão importantes neste projeto:

* `LDFLAGS` - Opções de ligação (_linking_) para localização de bibliotecas no
sistema de ficheiros, como por exemplo a _flag_ `-L`.
* `LDLIBS` - Opções de ligação (_linking_) para especificação de bibliotecas a
usar, como por exemplo a _flag_ `-l`.

No caso do exemplo apresentado não são usadas bibliotecas extra, pelo que estas
duas variáveis podem não ter conteúdos. No entanto é útil especificá-las
explicitamente na `Makefile`, pois podemos vir a querer adicionar bibliotecas
no futuro. Usando esta abordagem podemos omitir as receitas, pois o `make` vai
fazê-las corretamente. Desta forma, os conteúdos da próxima versão da
nossa `Makefile` são os seguintes:

```
# Compilador C
CC=gcc
# Argumentos (flags) de compilacao
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -g
# Opções de ligação para localização de bibliotecas (e.g. -L)
LDFLAGS=
# Opções de ligação, como por exemplo especificação de bibliotecas (e.g. -l)
LDLIBS=

# Nome do programa
PROGRAM=example

# Regra para geral executavel (deixar make fazer a receita)
$(PROGRAM): $(PROGRAM).o simple_showworld.o

# Regra para gerar o ficheiro objeto com o mesmo nome do executavel (deixar
# make fazer a receita)
$(PROGRAM).o: $(PROGRAM).c simple_showworld.h showworld.h

# Regra para gerar o ficheiro objeto simple_showworld.o (deixar make fazer a
# receita)
simple_showworld.o: simple_showworld.c simple_showworld.h

# Regra para limpar todos os ficheiros gerados (executavel e objetos)
.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
```

A linguagem das `Makefiles` oferece bastante possibilidades, como é possível
concluir olhando para o respetivo [manual][`make`]. Na prática, e nomeadamente
para o projeto em questão, as possibilidades aqui descritas são mais do que
suficientes para uma boa automatização da _build_ do jogo.

É de realçar que, ao contrário de linguagens imperativas como o C ou _scripts_
de linha de comandos (_Shell_/Bash), a linguagem das `Makefiles` é declarativa.
Ou seja, ao contrário dessas linguagens, a linguagem das `Makefile` descreve o
resultado desejado, mas não necessariamente os passos para o obter.

<a name="doygen"></a>

### Documentação automática do código com Doxygen

O código de um projeto deve estar devidamente documentado, sendo boa prática
escrever documentação específica sobre:

* Ficheiros e módulos: descrição e objetivos.
* Funções: descrição, entradas (argumentos) e saídas (valor retornado).
* Tipos: descrição geral e descrição específica para cada campo ou valor no
  caso de estruturas e enumerações, respetivamente.
* Variáveis globais: descrição.
* Constantes: descrição.

Esta documentação é especialmente importante para a parte pública (interface)
de um projeto, uma vez que a mesma pode vir a ser utilizada por outros
programadores ou incorporada noutros projetos. No entanto não é nada prático
escrever esta documentação em ficheiros ou documentos separados. A ferramenta
[Doxygen]<sup>[10](#fn10)</sup> permite converter comentários especialmente
formatados no código em documentação do projeto. A ferramenta permite exportar
documentação em formato HTML, PDF, RTF (compatível com DOC), _man pages_ e por
ai fora. Uma vez que comentários bem escritos são essenciais em qualquer
programa, é possível juntar dois em um (comentários e documentação) bastando
para isso seguir algumas regras de formatação de escrita de comentários.

O [código exemplo](code) foi comentado com as regras de documentação do
[Doxygen]. Para gerar a documentação basta entrar na pasta `code` e executar o
comando `doxygen`. A documentação é gerada em formato HTML e é colocada na
pasta `doc` dentro da pasta `code` (podem ver a documentação online em
https://videojogoslusofona.github.io/ic2017p2/). As definições do Doxygen para
cada projeto são especificadas num ficheiro chamado `Doxyfile`, como é o caso
do [ficheiro `Doxyfile` incluido no exemplo](code/Doxyfile).

O Doxygen suporta formatação Markdown dentro dos comentários, bem com a
inclusão de ficheiros Markdown na documentação (como é caso no exemplo
disponibilizado). Além das linguagens C e C++, o Doxygen suporta outras
linguagens comuns tais como Java, C#, Python ou PHP. Um
[grande número de projetos](https://www.stack.nl/~dimitri/doxygen/projects.html)
usa Doxygen para gerar a respetiva documentação, como por exemplo a biblioteca
[g2](http://www.ncbr.muni.cz/~martinp/g2/index.html) para gráficos, a
biblioteca de funções C [Apache Portable Runtime](http://apr.apache.org/docs/apr/1.6/index.html),
ou a biblioteca [cf4ocl](http://www.fakenmc.com/cf4ocl/docs/latest/index.html)
para execução de programas em GPU.

O manual do Doxygen está disponível
[aqui](http://www.stack.nl/~dimitri/doxygen/manual/index.html). De particular
interesse poderão ser a
[lista de comandos especiais](http://www.stack.nl/~dimitri/doxygen/manual/commands.html)
reconhecidos nos comentários no código, bem como o sumário de todas as
[etiquetas de configuração](http://www.stack.nl/~dimitri/doxygen/manual/config.html)
aceitáveis no ficheiro Doxyfile.

<a name="visualize"></a>

### Visualização do jogo

A pasta [code](code) contém codigo auxiliar para desenhar o mundo do jogo. A
[Figura 1](#figura1) mostra como o código está organizado.

<a name="figura1"></a>

![arquitectura](https://user-images.githubusercontent.com/3018963/34446014-d09091f8-eccf-11e7-8378-90221db5fc9a.png)

**Figura 1** - Organização do código auxiliar para desenhar o mundo do jogo no
ecrã.

O ficheiro [showworld.h](code/showworld.h) define três tipos que devem ser
usados para o desenvolvimento da parte de visualização do projeto, nomeadamente:

* [`AGENT_TYPE`](code/showworld.h#L34) - Enumeração que define os diferentes
  tipos de agente, tal como indicado na [Tabela 3](#tabela3).
* [`get_agent_info_at`](code/showworld.h#L44) - Tipo de função que retorna
  informação sobre um agente em dado local do mundo de jogo.
* [`show_world`](code/showworld.h#L62) - Tipo de função que mostra/atualiza a
  visualização do mundo de jogo.

A biblioteca definida nos ficheiros [simple_showworld.h](code/simple_showworld.h)
e [simple_showworld.c](code/simple_showworld.c) fornece uma função de nome
[`simple_show_world()`](code/simple_showworld.c#L35). Esta função obedece ao
tipo [`show_world`](code/showworld.h#L62), e mostra o mundo de jogo de forma
simples no terminal, podendo ser utilizada na 1ª parte do projeto. Na 2ª parte
do projeto os alunos devem implementar a sua própria biblioteca de visualização
do jogo, obedecendo aos tipos definidos em [showworld.h](code/showworld.h),
mas fazendo uso de uma biblioteca de terceiros tal como indicado
[anteriormente](#objetivos).

O ficheiro [example.c](code/example.c) contém um exemplo de como usar a função
`simple_show_world()`, obedecendo aos tipos definidos em
[showworld.h](code/showworld.h).

As próximas subsecções descrevem em detalhe como este código auxiliar pode ser
usado nas duas partes do projeto.

#### 1ª parte do projeto

Para a primeira parte do projeto, os alunos podem simplesmente usar a função
`simple_show_world()` cujo protótipo (cabeçalho) se encontra no ficheiro
[simple_showworld.h](code/simple_showworld.h), e cujo corpo está definido no
ficheiro [simple_showworld.c](code/simple_showworld.c). Esta função mostra o
mundo do jogo no terminal, indicando se o agente é zombie (`z`) ou humano (`h`),
o ID do agente em hexadecimal (por exemplo, `z0A`), e diferenciando com `Z` ou
`H` maiúsculo caso o agente em questão seja controlado por um jogador (por
exemplo, `H19`). Caso não exista um agente na célula em questão, a função
imprime um ponto (`.`). Para um mundo 5x5 com 4 zombies e 1 humano, com um dos
zombies controlado por um jogador, a função mostra algo parecido com a
[Figura 2](#figura2).

<a name="figura2"></a>

```
.   .  Z02  .   .

.  z00  .   .   .

.   .   .   .   .

.   .  z03  .   .

.  z01  .  h04  .
```

**Figura 2** - Exemplo do mundo de jogo com dimensões 5x5, tal como mostrado
pela função `simple_show_world()`.

A função `simple_show_world()` obedece ao tipo [`show_world`](code/showworld.h#L62)
e tem o seguinte protótipo:

```c
void simple_show_world(
    void *world,
    unsigned int xdim,
    unsigned int ydim,
    get_agent_info_at ag_info);
```

A função não devolve nada (`void`), mas aceita quatro argumentos. O primeiro
argumento, `world`, é do tipo `void *` (apontador genérico), e aponta para a
estrutura de dados que contém o mundo do jogo. O segundo e terceiro argumentos,
`xdim` e `ydim`, são as dimensões horizontal e vertical do mundo,
respetivamente. O quarto e último argumento, `ag_info`, é um apontador para uma
função que obtém informação sobre um agente localizado numa dada posição no
mundo do jogo, obedecendo ao tipo [`get_agent_info_at`](code/showworld.h#L44).
Como é possível observar no [código](code/simple_showworld.c#L35), a função
`simple_show_world()` percorre todas as células da grelha de simulação, por
linha e por coluna, obtém informação sobre o agente em cada posição (usando a
função apontada por `ag_info`), e imprime no ecrã, de forma formatada, a
informação obtida. A função `simple_show_world()` não precisa de saber nada
sobre o mundo de simulação, apontado pela variável `world`, pois este é passado
como argumento e interpretado pela função apontada por `ag_info`.

No entanto, após esta descrição existe ainda uma questão crucial e não
esclarecida. Onde está definida a estrutura de dados que contém o mundo de
simulação, bem como a função que a sabe interpretar? A reposta é a seguinte:
tanto a estrutura de dados, bem como a função que a interpreta, devem ser
desenvolvidas no código do projeto. Uma vez que o mundo de simulação vai ser
definido de forma específica por cada grupo, faz então sentido que a função que
obtém informação sobre um agente em determinada localização no mundo seja
também definida pelo grupo. Esta função deve obedecer ao tipo
`get_agent_info_at`, definido no ficheiro [showworld.h](code/showworld.h), da
seguinte forma:

```c
typedef unsigned int (*get_agent_info_at)(
    void *world,
    unsigned int x,
    unsigned int y);
```

Por outras palavras, funções do tipo `get_agent_info_at` devem devolver um
`unsigned int` contendo informação sobre um agente, recebendo como argumentos
a variável `world` (apontador genérico para o mundo do jogo), bem como as
coordenadas `(x,y)` da posição sobre a qual se pretende obter informação. O
`unsigned int` com informação sobre um agente está organizado internamente
como indicado na [Tabela 2](#tabela2).

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
[`AGENT_TYPE`](code/showworld.h).

| Tipo      | Significado            | Código (dec.)  | Código (bin.)  |
|-----------|------------------------|----------------|----------------|
| `None`    | Nenhum agente presente | 0              | 00             |
| `Human`   | Agente humano          | 1              | 01             |
| `Zombie`  | Agente zombie          | 2              | 10             |
| `Unknown` | Agente desconhecido    | 3              | 11             |

Um exemplo desta abordagem está disponível no ficheiro
[example.c](code/example.c). Este programa cria uma grelha de simulação de
dimensões 20x20, na qual os agentes são colocados em cada célula com uma
probabilidade de 10%, invocando depois a função `simple_show_world()` para
mostrar o mundo aleatoriamente gerado. A grelha de simulação (mundo do jogo) é
definida como um _array_ bidimensional de agentes, onde cada posição `[i][j]`
do _array_, correspondente a uma coordenada `(x,y)` no mundo do jogo, contém
um agente. Por sua vez, os agentes são definidos como uma [estrutura de nome
`AGENT` com três campos](code/example.c#L42): tipo de agente (`AGENT_TYPE`),
agente jogável (`unsigned char`, 0 ou 1), e ID do agente (`unsigned short`). A
função [`example_get_ag_info()`](code/example.c#L151), que obedece ao tipo
`get_agent_info_at`, sabe interpretar a variável `world` como _array_ de
agentes, sabendo também como obter informação sobre um agente em determinada
posição do _array_. Esta função é passada como último argumento da função
`simple_show_world()` quando a mesma é
[invocada no exemplo](code/example.c#L141).

Convém referir que as estruturas de dados usadas neste exemplo poderão não ser
adequadas ou suficientes para o desenvolvimento do projeto.

#### 2ª parte do projeto

Um dos [objetivos](#objetivos) para a 2ª parte do projeto consiste em
implementar a visualização do mundo do jogo usando uma biblioteca de terceiros.
Os alunos devem implementar a visualização na forma de uma biblioteca local que
substituirá a biblioteca simples fornecida nos ficheiros
[simple_showworld.c](code/simple_showworld.c) e
[simple_showworld.h](code/simple_showworld.h). Tal como esta última, a
biblioteca desenvolvida pelos alunos deve obedecer aos tipos definidos em
[showworld.h](code/showworld.h), de forma a que o código de visualização
desenvolvido por um grupo funcione no projeto de qualquer outro grupo. A
[Figura 3](#figura3) mostra uma possível organização de um projeto com
visualização baseada em [SDL2], omitindo possíveis ficheiros associados a
funcionalidades não discutidas nesta secção.

<a name="figura3"></a>

![orgproj](https://user-images.githubusercontent.com/3018963/34391685-44e7f88a-eb3f-11e7-9e26-636233178e16.png)

**Figura 3** - Possível organização de um projeto, omitindo possíveis
componentes associadas com outras funcionalidades específicas.

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
vertical e na horizontal. Por exemplo, num mapa 20x20, se um agente localizado
na coordenada (0,10), margem esquerda da grelha, decidir mover-se para a
esquerda, vai na realidade mover-se para a coordenada (19,10).

<sup><a name="fn2">2</a></sup> Numa grelha 2D, a
[vizinhança de Moore](https://en.wikipedia.org/wiki/Moore_neighborhood) é
composta pela célula central e pelas oito células que a rodeiam.

<sup><a name="fn3">3</a></sup> Por outras palavras, a lista de agentes deve ser
embaralhada (_shuffled_) no início de cada _turn_. O algoritmo de
[Fisher–Yates](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)
é um método de embaralhamento (_shuffling_) tipicamente utilizado para este
fim.

<sup><a name="fn4">4</a></sup> Embora seja relativamente simples criar uma
função ou biblioteca para leitura básica de ficheiros INI, existem algumas
prontas a utilizar, como por exemplo [iniparser](https://github.com/ndevilla/iniparser),
[inih](https://github.com/benhoyt/inih),
[minIni](https://github.com/compuphase/minIni) ou
[ini](https://github.com/rxi/ini). A biblioteca de jogos [Allegro5] também
oferece um módulo para processamento de ficheiros INI.

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
partir desse ponto. Dito isto, para um projeto desta dimensão e com grupos de 2
a 3 alunos, o uso de Git não é apenas recomendado para uma colaboração
eficiente: é absolutamente essencial. Caso usem um ou mais repositórios remotos
para colaboração devem indicar esse facto no relatório.

<sup><a name="fn8">8</a></sup> [Application Programming Interface](https://en.wikipedia.org/wiki/Application_programming_interface).

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
[INI]:https://en.wikipedia.org/wiki/INI_file
[GDB]:https://www.gnu.org/software/gdb/
[cppcheck]:http://cppcheck.sourceforge.net/
[Valgrind]:http://valgrind.org/
[`make`]:https://www.gnu.org/software/make/manual/make.html
[Make]:https://en.wikipedia.org/wiki/Make_(software)
[NMake]:https://docs.microsoft.com/pt-pt/cpp/build/nmake-reference
[KISS]:https://en.wikipedia.org/wiki/KISS_principle
[Global Game Jam]:https://globalgamejam.org/2018/jam-sites/misplay

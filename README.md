<!--
2º Projeto de Introdução à Computação 2017/2018 (c) by Nuno Fachada

2º Projeto de Introdução à Computação 2017/2018 is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
-->

# 2º Projeto de Introdução à Computação 2017/2018

> Este enunciado está em construção mas os alunos podem começar a planear o
> trabalho com base na informação já disponibilizada.

O projeto deve ser realizado em grupos de 2 a 3 alunos. A constituição dos
grupos deve ser comunicada ao docente via Moodle até 23 de dezembro, data a
partir da qual se assume que os alunos não pretendem realizar o projeto na 1ª
época.

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

Os agentes podem ser controlados pelo computador através de uma AI básica, ou
podem ser controlados por jogadores. Neste último caso, um jogador que controle
determinado agente pode decidir o destino do mesmo. Se o agente for um zombie,
a ação de infeção equivale à indicação de movimento para o local onde
está um humano. Nesse caso o zombie não se move (pois o local já está ocupado
pelo humano), mas o humano é convertido em zombie. Se o humano era controlado
por um jogador, deixa de o ser, e passa a ser controlado pela AI. O jogo
termina quando não existirem mais agentes do tipo humano na grelha.

Caso um agente seja controlado pela AI, as suas decisões dependem do tipo de
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
saber interpreta-los corretamente. O programa deve ainda ignorar campos que
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

Neste modo, cada vez que um agente controlado pelo jogador é chamado a agir,
o programa fica a aguardar o _input_ do jogador sobre que ação tomar. A
visualização do jogo deve ser atualizada imediatamente antes de ser solicitado
_input_ a um jogador (pelo menos).

## Desenvolvimento do projeto

### Primeira parte

#### Objetivos a atingir

* Jogo deve funcionar como especificado.
* Código deve compilar sem erros no compilador [GCC] e/ou [Clang] com as opções
  `-std=c99 -Wall -Wextra -Wpedantic`.
* Código deve estar devidamente comentado e indentado.

As seguintes limitações são aceitáveis e não serão penalizadas na primeira
entrega:

* Tamanho do ambiente e número de agentes fixo após compilação: _X_=20, _Y_=20,
_n<sub>z</sub>_=20, _n<sub>h</sub>_=20.
  * Sugestão: usar constantes e ignorar valores lidos do ficheiro de
    configuração.
* Código pode ser entregue num único ficheiro `.c`.
* Visualização do jogo pode ser feita com código exemplo disponibilizado na
  secção [Visualização do jogo](#visualize).

#### Entrega

A 1ª parte do projeto deve ser entregue via Moodle até às 23h de 14 de janeiro
de 2018. Deve ser submetido um ficheiro `zip` com a pasta do projeto que deve
ter os seguintes conteúdos:

* Ficheiro(s) `.c` (e possivelmente ficheiros `.h` se os alunos decidirem
  organizar o código em vários ficheiros logo para a primeira entrega).
* Pasta escondida `.git` contendo o repositório Git local do projeto.
* Ficheiro `README.md` contendo o relatório do projeto em formato [Markdown],
  contendo as seguintes secções:
  * Título do projeto.
  * Nomes dos autores (primeiro e último) e respetivos números de aluno.
  * Descrição da solução:
    * Arquitetura da solução, com breve explicação de como o programa foi
      estruturado. Um fluxograma simples, que mostre o funcionamento de alto
      nível do programa, pode ajudar bastante a explicar a arquitetura do
      mesmo.
    * Estruturas de dados: grelha de simulação, agentes, outras estruturas
      auxiliares relevantes.
    * Algoritmos: procura de agente mais próximo, cáculo de direção na grelha,
      _shuffling_ (embaralhamento) dos agentes antes de cada _turn_, outros
      algoritmos relevantes.
  * Manual de utilizador:
    * Como compilar (qual o comando completo para compilação).
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

**Atenção**: Todos os ficheiros C e Markdown devem ser gravado em codificação
UTF-8<sup>[5](#fn5)</sup>.

#### Critério de avaliação

A primeira parte do projeto, que tem um peso de 4 valores na nota final da
disciplina, será avaliada segundo os critérios indicados na Tabela 1.

**Tabela 1** - Critérios absolutos da 1ª parte do projeto.

| Critério                                               | Peso      |
|--------------------------------------------------------|-----------|
| Funcionamento segundo especificações                   | 1 val.    |
| Qualidade do código e das soluções<sup>[6](#fn6)</sup> | 0,6 val.  |
| Indentação  e comentários                              | 0,5 val.  |
| Compilação sem erros e _warnings_                      | 0,4 val.  |
| Relatório                                              | 1 val.    |
| Desenvolvimento do projeto com Git<sup>[7](#fn7)</sup> | 0,5 val.  |
| Antecipação de objetivos da 2ª parte do projeto        | Bónus!    |

A nota máxima da 1ª parte do projeto é de 4 valores, sendo que o bónus poderá
servir apenas para compensar avaliações piores nos critérios principais.

### Segunda parte

#### Objetivos a atingir

* Tamanho da grelha e número de agentes variável após compilação, tal como
  especificado no ficheiro de configuração.
* Documentação do projeto com [Doxygen].
* Organização do programa em vários ficheiros `.c` e `.h` com uso de _Makefile_.
* Visualização do jogo deve ser feita com recurso a uma biblioteca gráfica ou
  de jogos. Algumas sugestões:
  * [g2] - Simples mas limitada.
  * [Ncurses] - ASCII art (texto), ver referência [\[2\]](#ref2).
  * [Allegro5] - Bom meio termo, com bons exemplos em C.
  * [SDL2] - Muito versátil e abrangente, mas poucos exemplos em C.
  * [Raylib] - Muito interessante, mas instalação no Ubuntu não é trivial (ver
    instruções no Wiki da [página no GitHub][Raylib-gh]).

#### Entrega

A 2ª parte do projeto deve ser entregue via Moodle até às 23h de 21 de janeiro
de 2018. Deve ser submetido um ficheiro `zip` com a pasta do projeto que deve
ter os seguintes conteúdos:

* Ficheiros `.c` e `.h`, bem como a _Makefile_.
* Ficheiro `README.md` em formato [Markdown] gravado em codificação ASCII ou
  UTF-8<sup>[5](#fn5)</sup>.
* Pasta escondida `.git` contendo o repositório Git local do projeto.

#### Critério de avaliação

A segunda parte do projeto, que tem um peso de 4 valores na nota final da
disciplina, será avaliada usando duas tabelas distintas. A tabela 2 indica os
critérios absolutos, que totalizam 4 valores:

**Tabela 2** - Critérios absolutos da 2ª parte do projeto.

| Critério                                               | Peso      |
|--------------------------------------------------------|-----------|
| Tamanho da grelha/número de agentes variável           | 1 val.    |
| Visualização com recurso a biblioteca externa          | 1 val.    |
| Documentação com [Doxygen]                             | 1 val.    |
| Organização do projecto e _Makefile_                   | 1 val.    |
| [Extensões opcionais e Global Game Jam](#gamejam)      | Bónus!    |

A nota máxima da 2ª parte do projeto é de 4 valores, sendo que o bónus poderá
servir apenas para compensar avaliações piores nos critérios principais. No
entanto, como os critérios absolutos não fazem sentido sem que os objetivos da
1ª parte do projeto tenham sido atingidos, a nota final da 2ª parte também
depende de uma percentagem baseada nesses objetivos, tal como indicado na
Tabela 3.

**Tabela 3** - Critérios relativos da 2ª parte do projeto.

| Critério                                               | Peso      |
|--------------------------------------------------------|-----------|
| Funcionamento segundo especificações                   | 25,0%     |
| Qualidade do código e das soluções<sup>[6](#fn6)</sup> | 15,0%     |
| Indentação  e comentários                              | 12,5%     |
| Compilação sem erros e _warnings_                      | 10,0%     |
| Relatório                                              | 25,0%     |
| Desenvolvimento do projeto com Git<sup>[7](#fn7)</sup> | 12,5%     |

A nota final da 2ª parte do projeto é dada pelo total dos critérios absolutos
multiplicado pela percentagem obtida nos critérios relativos.

<a name="visualize">

### Visualização do jogo

Usar código fornecido para a 1ª parte, desenvolver código próprio para a 2ª
parte.

### Sugestões para o desenvolvimento do projeto

1. Começar com coisas simples
2. Usar Git para colaboração
3. Usar [cppcheck] para verificação estática
3. Usar [GDB] para _debugging_

<a name="gamejam"></a>

### Extensões opcionais, trabalho futuro e Global Game Jam

* Melhor AI.
* Melhor integração com biblioteca preferida: [Ncurses], [Allegro5], [SDL2] ou
  [Raylib]. Infelizmente [g2] não é apropriada para jogos "a sério".
* Desenvolvimento do jogo na Global Game Jam.

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
suspensão temporária ou definitiva da ULHT<sup>[8](#fn8)</sup>.

## Notas

<sup><a name="fn1">1</a></sup> Nota de rodapé sobre toros

<sup><a name="fn2">2</a></sup> Nota de rodapé sobre Moore

<sup><a name="fn3">3</a></sup> Nota de rodapé sobre _shuffling_

<sup><a name="fn4">4</a></sup> Nota de rodapé sobre bibliotecas para leitura de
ficheiros INI

<sup><a name="fn5">5</a></sup> Nota de rodapé sobre ASCII e UTF-8 em Windows

<sup><a name="fn6">6</a></sup> Nota de rodapé sobre qualidade do código

<sup><a name="fn7">7</a></sup> Nota de rodapé sobre Git local e remoto

<sup><a name="fn8">8</a></sup> Texto adaptado da disciplina de [Algoritmos e
Estruturas de Dados][aed] do [Instituto Superior Técnico][ist].

## Referências

* <a name="ref1">\[1\]</a> Pereira, A. (2017). C e Algoritmos, 2ª edição. Sílabo.
* <a name="ref2">\[2\]</a> Reagan, P. (2014). [Game Programming in C with the
Ncurses Library](https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library),
Viget Labs.


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

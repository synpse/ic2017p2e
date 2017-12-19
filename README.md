<!--
2º Projeto de Introdução à Computação 2017/2018 (c) by Nuno Fachada

2º Projeto de Introdução à Computação 2017/2018 is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
-->

# 2º Projeto de Introdução à Computação 2017/2018

> Este enunciado está em construção e não deve ser usado
> como base para o projecto enquanto esta mensagem aqui estiver.

## Descrição do problema

Pretende-se que os alunos desenvolvam um jogo/simulador no qual zombies
perseguem e infectam humanos. O jogo desenrola-se numa grelha 2D
toroidal<sup>[1](#fn1)</sup> com dimensões _X_ e _Y_ e vizinhança de
Moore<sup>[2](#fn2)</sup>. Em cada célula da grelha pode estar no máximo um
agente, que pode ser um **zombie** ou um **humano**. No início da simulação
existem _n<sub>z</sub>_ zombies e _n<sub>h</sub>_ humanos, num total de _n =
n<sub>z</sub>_ + _n<sub>h</sub>_ agentes.

O jogo é _turn-based_, e em cada _turn_ (iteração) cada agente pode realizar
uma acção. Os humanos têm disponível apenas uma acção: movimento. Os zombies
podem realizar dois diferentes tipos de acção: 1) movimento; e, 2) infeção de
humanos. O movimento dos agentes pode ser realizado para uma célula vazia numa
vizinhança de Moore de raio 1. A infeção de humanos pode ser realizada por
zombies quando o humano está numa célula adjacente na vizinhança de Moore. A
ordem em que os agentes executam as suas acções em cada _turn_ é
aleatória<sup>[3](#fn3)</sup>, de modo a que nenhum agente em específico
obtenha a vantagem de agir cedo durante todo o jogo.

Os agentes podem ser controlados pelo computador através de uma AI básica, ou
podem ser controlados por um ou mais jogadores. Neste último caso, o jogador
que controla o agente pode decidir o destino do mesmo. Se o agente for um
zombie, a acção de infecção equivale à indicação de movimento para o local onde
está um humano. O zombie não se move, mas o humano converte-se em zombie. Se
o humano era controlado por um jogador, deixa de o ser, e passa a ser
controlado pela AI.

Caso um agente seja controlado pela AI, as suas decisões dependem do tipo de
agente:

* Humano - O humano move-se na direção oposta ao zombie mais próximo.
* Zombie - Caso exista um humano numa célula adjacente, infecta-o. Caso
  contrário, move-se na direção do humano mais próximo.

## Exemplo de execução

Work in progress

## Notas

<sup><a name="fn1">1</a></sup> Nota de rodapé sobre toros

<sup><a name="fn2">2</a></sup> Nota de rodapé sobre Moore

<sup><a name="fn3">3</a></sup> Nota de rodapé sobre _shuffling_

## Referências

* <a name="ref1">(1)</a> Pereira, A. (2017). C e Algoritmos, 2ª edição. Sílabo.

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

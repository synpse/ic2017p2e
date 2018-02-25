# Introduction to Computation
### 2nd Project (2nd Period) 2017/2018

## Index

 **1.** Introduction
 **2.** Project´s Files
 **3.** Solution
 **4.** User´s Manual
 **5.** Conclusions
 **6.** Appendix

## Introduction

In this project I was asked to make a turn-based game in C that simulated a scenario where humans were stalked by zombies. This was to be achieved using the following mechanics:

- 2D Grid (Regular grid)
- von Neumann´s neighborhood
- Agents (Zombies + Humans)
- Movement
- Infection (For Zombies)

## Files

- coordinates.c
- coordinates.h
- Doxyfile
- jogo.c
- jogo.h
- Makefile
- README.md
- showworld.h
- showworld_simple.c
- shuffle.c
- shuffle.h
- movement.c
- movement.h
- sprite_human.png
- sprite_zombie.png
- sprite_tile.png

## Solution

For my game I used mainly a grid and agents. These were achieved with structs and arrays.
Also, I used von Neumann´s neighborhood.

## User´s Manual

 **1.** To generate a game build you have to write the following command on the **terminal**:

    $ make

 **2.** How to start:

	$ ./jogo <XDIM> <YDIM> <NZOMBIES> <NHUMANS> <NZOMBIESPLAYABLE> <NHUMANSPLAYABLE> <TURNS>

**3.** How to Play:

- Start the game (refer to step 2)
- Wait for your turn
- Move the playable agent
- Watch as the CPU plays

	- Zombies should stalk humans and infect them
	- Humans should run away from zombies

- Gamewin or Gameover

	 - Zombies win if there are no humans left
	 - Humans win if the target turn was reached

## Conclusions

The project was quite hard and labor-intensive but was ultimately worth it. I learned a **lot** with this project and now that I´ve finished it I think that all the time spent was worth it.

## Appendix

### External pages and files used:

- https://github.com/rui-martins/p2/
- http://www.learn-c.org/en/Arrays
- http://www.learn-c.org/en/Multidimensional_Arrays
- http://www.learn-c.org/en/Strings
- http://www.learn-c.org/en/Pointers
- https://stackoverflow.com/questions/42321370/fisher-yates-shuffling-algorithm-in-c
- http://www.sanfoundry.com/c-program-implement-fisher-yates-algorithm-array-shuffling/
- https://github.com/VideojogosLusofona/ic2017aulas
- https://github.com/VideojogosLusofona/ic_exercicios
- https://mathoverflow.net/questions/152107/proof-of-von-neumanns-debiasing-algorithm

### Books used:

- https://www.wook.pt/livro/c-e-algoritmos-alexandre-pereira/19072517

## Meta:

**Professor:** Nuno Fachada
**Student:** Tiago Alves (A21701031)

**Course:** Licenciatura em Aplicações Multimédia e Videojogos
**Institution:** Universidade Lusófona de Humanidades e Tecnologias


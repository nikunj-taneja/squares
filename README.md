# Squares

A MetaSquares clone built in C.
<br>
It is a two player strategy board game with simple rules and deep strategy, developed as a part of my freshman year programming course. The game is adapted from the online flash version available <a href="http://www.fastswf.com/2wsAnK8">here</a>. The game was originally designed by <a href="http://www.scottkim.com/">Scott Kim</a>.

Squares is a CLI application with 2 game modes:
* Human v/s Human
* Human v/s Computer

NOTE: A more enhanced computer player is WIP.

## Getting Started

These instructions will help you build and run the game on your local machine.

* Clone (or download) the repository
```
$ git clone https://github.com/nikunj-taneja/Squares.git
```

* Change the current directory to Squares/src and build the files using gcc
```
$ cd Squares/src
$ gcc -Wall main.c game.c helpers.c -o squares
```

* Run the game
```
$ ./squares
```

## Rules

The game takes place on an 8 x 8 game board with 64 cells where each cell can hold a disc. There are two kinds of discs represented as below: 
* Red – character 0
* Blue – character #

Players place their discs alternatively on the game board, one using the red disc and the other using blue with blue playing first. The goal of the game is to form as many squares (preferably large) as possible using the discs. Larger square corresponds to higher points. The points of a given square are calculated by the following formula:
```
#points = (#col)^2
```
where #col is the total number of columns (or rows) that the square covers. In each turn, a player must place (only) one disc. If the disc placed doesn't form any squares, the player gets zero points.

The game ends in the follwing situations:
* The game board is full, in which case the player with greater score wins and it's a draw if the scores of both the players are equal.
* one of the player gets over 150 points with at least 15 points higher than his/her opponent.

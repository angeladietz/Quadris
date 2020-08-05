# Quadris

Quadris is a game of Tetris but with a twist - unlike Tetris, Quadris is not real-time. It gives the user as much time as needed to drop a block.

This project uses many OOP principles and design patterns as taught by Prof. Scott in CS 247 (Spring 2020).

## Building the game
Build the game by typing `make` and run it with `./quadris` followed by command line options as seen below.

## Command line options:
- -text: run the game in text-mode only
- -seed [seed]: sets the random number generator's seed
- -scriptfile [file]: generates block based on file instead of default sequence.txt (only applies to level 0)
- -startlevel [n]: starts game on level n
- -h  or  --help           Display a help message with these CLI options and commands

Example: `./quadris -text`

## In-game commands:
- left: moves block one unit left
- right: moves block one unit right
- down: moves block one unit down
- clockwise: rotates block 90 degrees in the clockwise direction
- counterclockwise: rotates block 90 degrees in the anticlockwise direction
- drop: drops current block - this is required to move to the next block
- levelup: increases the difficulty by one level
- leveldown: decreases the diffculty by one level
- norandom [file]: this command makes these levels non-random, uses [file] as a sequence of blocks (only level 3 & 4)
- random: this comman makes levels 3 & 4 random (true by default)
- sequence [file]: executes the sequence of commands found in file
- I, J, L, S, Z, O, T: replace current block with specified block 
- restart: clears the board and restarts a new game from level 0
- hint: displays one possible location to drop the current block

## Bonus features:
- Commands can be shortened (eg. lef -> left)
- Commands can be executed multiple times (eg. 3ri -> moves to the right by three cells)

# num-game
## NAME
num-game - simple number game.
## SYNOPSIS
	num-game [OPTIONS]
## DESCRIPTION
num-game program will guess the number from 1 to 100 that you guessed.
## OPTIONS
- `-r` print roman numbers instead arabic.
- `-h, --help` print help message.
## CONSTANTS
```c
char *romans
```
array containing Roman numerals from 1 to 100
## FUNCTIONS
```c
char *to_roman(int num)
```
takes an integer from 1 to 100, returns a string with equal roman number or "Err" on error
```c
int to_arabic(char *roman)
```
takes a roman number from I to C, returns the equal value as an integer or -1 on error




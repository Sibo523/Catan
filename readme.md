# Catan

## Description

I created an interactive Catan game

## Table of Contents

- [Installation](#installation)
- [Manu-Game](#Manu-Game)
- [Usage](#usage)
- [Contact](#contact)


## Installation
for Arch:
```
    yay valgrind
```
```
    yay coredumpctl
```
for Ubuntu:
```
    sudo apt install valgrind //to check memory loss
```
```
    sudo apt install systemd-coredump //used for debug 
```

Step-by-step instructions on how to install the project.
## Manu-Game
There are 9 modes when playing the game 
1. Build a settlement in a givent cordinates
2. Buy development card
3. Build a road
4. Upgrade settlment
5. Trade with other players
6. next turn
7. print board
8. show resources
9. use development card

## Usage

to compile the code you can make "all" target
```
    make all##
```
to run the game use 
```
    ./catan
```
to run a shell script to run a couple of moves in the game
```
    make run
    or 
    ./!run_game.sh
```
to run the test that I wrote use 
```
    make test
    ./test
```
to check memory loss leak you can use 
```
    make valgrind
```
and to debug the code using coredumpctl and gdb (make sure you have installed the requirments)
```
    make debug
```


Examples of how to use the project:
change catan file to this
```
    //create players that will play the game
    Player *p1 = new Player("name","color");
    Player p2 = new Player("name2","color2");
```
```
    GameManager gamemanager({*p1,*p2}); // create the gameManager kind of facade for easy use
```
```
    while(!gameManager.checkWinCondition())
    {
        gameManager.play();// every player in his turn will do whatever he want

    }
```
and to finally run the code
```
    ./catan 
```


## Contact

Roi Sibony, Roisi20041@gmail.com

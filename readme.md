# Catan

## Description

I created 

## Table of Contents

- [Installation](#installation)
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

## Usage

to compile the code you can make "all" target
```
    make all
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
and to check memory loss leak you can use 
```
    make valgrind
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

/**
 * Programmer Name: Jordan Muehlbauer
 * Assignment: PA 4
 * Date: 3/4/2020
 * Description: Implementation of the class GameWorld which handles the game Hunt The Wumpus from source.h
 */

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "source.h"

using namespace std;

void GameWorld::generateWumpus() {
    generateCharacter('W',1);
}

void GameWorld::generateGold() {
    generateCharacter('G',1);
}

void GameWorld::generatePitts() {
    int pitts = 10 - (rand() % 6);
    generateCharacter('P',pitts);
}

bool GameWorld::isSpotTaken(int x, int y) {
    return board[y][x] != ' ';
}

void GameWorld::generateCharacter(char item, int amount) {
    int placed = 0;

    while (placed < amount){
        //Generate random coordinates
        int x = rand() % 5;
        int y = rand() % 5;

        //Check if that spot is taken
        if(isSpotTaken(x,y))continue;

        //Make sure that the char isn't on the spawn point
        if(x == 2 && y == 2)continue;

        //Place the item
        board[y][x] = item;
        placed++;
    }
}

void GameWorld::displayEntireWorld() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(i == playerY && j == playerX)cout << 'U';
            else cout << board[i][j];
        }
        cout << endl;
    }
}

void GameWorld::displayVisibleWorld() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            //Find the change
            int changeX = playerX - j;
            int changeY = playerY - i;

            //Make all the change's positive
            changeX = changeX < 0 ? changeX * -1 : changeX;
            changeY = changeY < 0 ? changeY * -1 : changeY;

            if(changeX <= 1 && changeY <= 1){
                if(i == playerY && j == playerX)cout << 'U';
                else cout << board[i][j];
                continue;
            }
            cout << " ";
        }
        cout << endl;
    }
}

void GameWorld::displayPlayer() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if(i == playerY && j == playerX)cout << 'U';
            else cout << " ";
        }
        cout << endl;
    }
}

void GameWorld::moveUp() {
    //Make sure we aren't going out of the map
    if(playerY == 0){
        cout << "Stop you cannot move outside of the map!" << endl;
        return;
    }

    //Increase their Y
    playerY--;
}

void GameWorld::moveDown() {
    //Make sure we aren't going out of the map
    if(playerY == 4){
        cout << "Stop you cannot move outside of the map!" << endl;
        return;
    }

    //Decrease their Y
    playerY++;
}

void GameWorld::moveRight() {
    //Make sure we aren't going out of the map
    if(playerX == 4){
        cout << "Stop you cannot move outside of the map!" << endl;
        return;
    }

    //Increase their X
    playerX++;
}

void GameWorld::moveLeft() {
    //Make sure we aren't going out of the map
    if(playerX == 0){
        cout << "Stop you cannot move outside of the map!" << endl;
        return;
    }

    //Decrease their Y
    playerX--;
}

bool GameWorld::haveIWon() {
    //Get what item the player is standing above
    char item = board[playerY][playerX];

    return item == 'G';
}

bool GameWorld::amIAlive() {
    //Get what item the player is standing above
    char item = board[playerY][playerX];

    return item != 'P' && item != 'W';
}

void GameWorld::modifyPoints(int change) {
    points += change;
}

ostream &operator<<(ostream& os,GameWorld &v) {
    os << v.name << ": " << v.points << endl;
    return os;
}

void GameWorld::newGame() {
    //Get the players name
    cout << "What is your name?" << endl;
    cin >> name;

    //Set all of the character to a space
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            board[i][j] = ' ';
        }
    }

    //Generate the 4 Pitt's for the player to fall into
    generatePitts();

    //Generate the gold
    generateGold();

    //Create the WUMPUS!
    generateWumpus();

    //Set the position of the user
    playerX = 2;
    playerY = 2;
    points = 0;

    start();
}

void GameWorld::restartGame() {
    //Reset points
    points = 0;

    //Reset player position
    playerY = 2;
    playerX = 2;
}

void GameWorld::quit() {
    saveGame();
    cout << "Thank you for playing!" << endl;
}


void GameWorld::start() {
    char input = '\0';
    bool displayRegularMap = true;
    while (input != 'Q' && input != 'q'){
        if(displayRegularMap)displayPlayer();
        printOptions();
        cout << "Enter your choice: " << endl;
        cin >> input;

        //Validate and handle input
        if(input == 'I' || input == 'i')moveUp();
        if(input == 'K' || input == 'k')moveDown();
        if(input == 'J' || input == 'j')moveLeft();
        if(input == 'L' || input == 'l')moveRight();
        if(input == 'V' || input == 'v')displayVisibleWorld();
        if(input == 'C' || input == 'c')displayEntireWorld();
        if(input == 'R' || input == 'r')restartGame();
        if(input == 'N' || input == 'n')newGame();
        if(input == 'Q' || input == 'q')quit();

        //Handle post input
        //Handle a moving turn
        if(     input == 'I' || input == 'i' ||
                input == 'K' || input == 'k' ||
                input == 'J' || input == 'j' ||
                input == 'L' || input == 'l'){

            //Return the map setting to normal
            displayRegularMap = true;

            //Add points for surviving
            if(amIAlive())modifyPoints(5);
            else {
                saveGame();
                cout << "Bummer! you have lost the game!" << endl;
                newGame();
                return;
            }
            //Save their points if they win and create a new game
            if(haveIWon()){
                saveGame();
                cout << "Congrats you won the game!" << endl;
                newGame();
                return;
            }

        }

        //Handle point deductions for using cheats!
        if(input == 'V' || input == 'v'){
            displayRegularMap = false;
            modifyPoints(-2);
        }
        if(input == 'C' || input == 'c'){
            displayRegularMap = false;
            modifyPoints(-5);
        }
    }
}


void GameWorld::printOptions() {
    cout << "Move Around with I,J,K,L. Q to Quit, N for new game, R for restart, V to display adjacent caves, C to display the entire map" << endl;
}

void GameWorld::saveGame() {
    ofstream file;
    file.open("GameScores.txt",fstream::app);
    file << *this;
    file.close();
}





/**
 * Programmer Name: Jordan Muehlbauer
 * Assignment: PA 4
 * Date: 3/4/2020
 * Description: Definition of the GameWorld class to be implemented in source.c
 */
#ifndef CPTS122PA4_SOURCE_H
#define CPTS122PA4_SOURCE_H

#include <cstdlib>
using namespace std;
class GameWorld {
private:
    char name[256];
    char board[5][5];
    int playerX;
    int playerY;
    int points = 0;
    void generateCharacter(char item,int amount);
public:
    GameWorld(){
        //Generate a new game!
        newGame();
    }

    friend std::ostream& operator<<(std::ostream & str, GameWorld& v);
    void generateWumpus();
    void generateGold();
    void generatePitts();
    bool isSpotTaken(int x,int y);
    void displayEntireWorld();
    void displayVisibleWorld();
    void displayPlayer();
    void newGame();
    void restartGame();
    void saveGame();
    void quit();
    void modifyPoints(int change);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void start();
    void printOptions();
    bool haveIWon();
    bool amIAlive();
};


#endif //CPTS122PA4_SOURCE_H

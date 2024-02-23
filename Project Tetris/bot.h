#pragma once
#include "shape.h"
#include "position.h"
#include "player.h"
#include <cmath>

//Computer Player
class Bot : public Player
{
    Position tmp1, tmp2, tmp3; 
    Position& bestPosition = tmp1; //The best position in a given moment
    Position& worstPosition = tmp2; //The worst position in a given moment
    Position& goToPosition = tmp3; //The position the computer is gonna move to

    const int playerNum = getPlayerNum();
    const GameConfig::Bot_Level level; //The level of the bot (good/best/novice)

public:
    Bot(Board& _board, GameConfig::Bot_Level _level, int _playerNum = 1);
    ~Bot();
    bool takeAction(char input) override; //Function that makes the action of the player
    bool botOrHuman() override; //Tells if the player is a bot or not
    void updatePositions(); //Updates all the positions
    void setNewShape(bool allowBomb = true) override; //Sets up a new shape for the player
private:
    int getOffsetForLeftRight(char input) override; //Tells the player where to go
    int getNextOrientation(char input) override; //Tells the orientation the player will rotate his shape for
};



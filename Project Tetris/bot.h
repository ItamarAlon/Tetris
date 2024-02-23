#pragma once
//#include "board.h"
#include "shape.h"
#include "position.h"
#include "player.h"
#include <cmath>

//Shape that plays itself
class Bot : public Player
{
    Position tmp1, tmp2, tmp3; //will probably delete
    Position& bestPosition = tmp1;
    Position& worstPosition = tmp2;
    Position& goToPosition = tmp3;

    const int playerNum = getPlayerNum(); //will probably delete
    const GameConfig::Bot_Level level;

public:
    Bot(Board& _board, GameConfig::Bot_Level _level, int _playerNum = 1);
    ~Bot();
    bool takeAction(char input) override;
    bool botOrHuman() override;
    void updatePositions();
    void setNewShape(bool allowBomb = true) override;
    void messUpPosition();
private:
    int getOffsetForLeftRight(char input) override;
    int getNextOrientation(char input) override;
};



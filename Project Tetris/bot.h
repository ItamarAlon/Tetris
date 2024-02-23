#pragma once
//#include "board.h"
#include "shape.h"
#include "position.h"
#include "player.h"
#include <cmath>

//Shape that plays itself
class Bot : public Player
{
    Position tmp; //will probably delete
    Position& bestPosition = tmp;
    const int playerNum = getPlayerNum(); //will probably delete

public:
    Bot(Board& _board, int _playerNum = 1);
    void takeAction(char input) override;
    bool botOrHuman() override;
    void updateBestPosition();
    void setNewShape(bool allowBomb = true) override;
private:
    int getOffsetForLeftRight(char input) override;
    int getNextOrientation(char input) override;

};



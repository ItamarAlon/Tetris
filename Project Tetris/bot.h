#pragma once
//#include "board.h"
#include "shape.h"
#include "position.h"
#include <cmath>

//Shape that plays itself
class Bot : public Shape
{
    Position tmp;
    Position& bestPosition = tmp;
    const int playerNum = board.getPlayerNum();

public:
    Bot(Board& _board, char ch = -2); 
    void takeAction(char input) override;
    void findBestPosition(); //To Shape, but needs board
    float getPositionScore(); //To Shape, but needs board
    bool botOrHuman() override;
    void setShape(); //Might delete

    void moveToPosition(const Position& bestPosition); //Will probably delete
private:
    int getOffsetForLeftRight(char input) override;

    int getHoleCount(); //To Board
    float getBumpinessLevel(int& maxHeight); //To Board
    int getFullLinesCount(); //To Board
    int fillHeightsArr(int heights[]); //To Board

    void updateBestPosition(float score); //To Shape
    int getNextOrientation(int key) override;

};



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
    enum class Action {LEFT, RIGHT, CLOCKWISE, COUNTER_CLOCKWISE};
    const int playerNum = board.getPlayerNum();

public:
    Bot(Board& _board, char ch = -2); 
    void takeAction(char input) override;
    void findBestPosition();
    float getPositionScore();
    bool botOrHuman() override;
    void setShape();

    void moveToPosition(const Position& bestPosition); //Will probably delete
private:
    int getOffsetForLeftRight(char input) override;
    int getHoleCount();
    float getBumpinessLevel(int& maxHeight);
    int getFullLinesCount();
    int fillHeightsArr(int heights[]);
    void updateBestPosition(float score);
    char getInputForAction(Action action);
    int getNextOrientation(int key);

};



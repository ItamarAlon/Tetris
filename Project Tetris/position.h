#pragma once
//Position, used to search for the best position so that the computer will know where to move
struct Position
{
    int anchorX, anchorY; 
    int orientation;
    float score = -999999999;

public:
    Position();
};


#pragma once
#include "Block.h"
#include "Board.h"
#include "game.h"

//class Block;
//class Board;

class Shape
{
	Block block;
	Board &board;
	Block blockArr[4] = {};
	int divider;
	int orientation;
	enum class Shapes {I,O,T,S,Z,J,L};
	Shapes shape;
public:
	bool IsShapeInAir = true;

	Shape(Board& _board, char ch = -2);
	//Shape& operator=(const Shape& newShape);
	void setShape(char ch = -2);
	void randomShape(int positions[8]);
	void print();
	void moveBy(int x, int y);
	bool moveShapeDown(int byWhat = 1);
	void moveShapeLeftRight(int key);
	void createCordsArr(int positions[8], int anchorX, int anchorY, int x1, int y1, int x2, int y2, int x3, int y3);
	//void speedUpShape(); //mightDeleteFunction
	void rotateShape(char key);
	void changeShapePosition(int positions[8]);
	int getNextOrientation(int key);

};


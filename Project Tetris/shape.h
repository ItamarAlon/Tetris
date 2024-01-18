#pragma once
#include "Libraries.h"
class Block;
class Board;
class Shape
{
	Block blockArr[4];
	Board board;
	int divider;
	int orientation;
	enum class Shapes {I,O,T,S,Z,J,L};
	Shapes shape;
public:
	Shape(const Board& _board, char ch = 254);
	void setShape(char ch = 254);
	void randomShape(int positions[8]);
	void print();
	void moveBy(int x, int y);
	bool moveShapeDown();
	void moveShapeLeftRight(int key, int playerNum);
	void createCordsArr(int positions[8], int anchorX, int anchorY, int x1, int y1, int x2, int y2, int x3, int y3);
	void handleInput(int playerNum);
	void moveShapeToBottom();
	void rotateShape(char key);
	//void

};


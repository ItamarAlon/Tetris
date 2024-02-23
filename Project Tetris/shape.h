#pragma once
#include "block.h"
#include "board.h"
#include "game.h"
#include "position.h"

//Class that handles the shapes (tetromino) of the game.
class Shape
{
	char ch;
	int orientation = 0; //The current orientation of the tetromino (because a shape can rotate during gameplay)
	int divider; //Number of orientations a shape has
	int numOfBlocks = 4;
	enum class Shapes { I, O, T, S, Z, J, L, BOMB }; //All the shapes that can appear in game
	Shapes shape; //The current shape of the tetromino

protected:
	Block blockArr[4] = {}; //Each shape is made of 4 blocks. This array represents the blocks that make the tetrominoe.
	Board& board; //The board where the shape is placed

public:
	Shape(Board& _board, char ch = -2);  
	Shape(const Shape& oldShape);
	Shape& operator=(const Shape& oldShape);
	virtual ~Shape() {}

	virtual void setShape(bool allowBomb = true); //Sets a new shape for game
	void print();
	void moveBy(int x, int y); //Moves the shape by a certain value (according to it's current value on-screen)
	bool moveShapeDown(); //Moves the shape 1 place down (if possible)
	bool moveShapeLeftRight(int offsetX); //Moves the shape left/right if possible (according to the input given from the keyboard), and returns whether or not the shape moved.
	void rotateShape(int newOrientation); //Rotates the shape (if possible)

	bool canShapeMoveOffset(int offsetX, int offsetY);
	bool canShapeMoveToPosition(int positions[8]) const;
	int getAnchorX() const;
	int getAnchorY() const;
	int getOrientation() const;
	int getDivider() const;
	void getAnchorXY(int& anchorX, int& anchorY) const;
	virtual bool isBomb() const;

	int getDistanceFromBorder(GameConfig::Direction direction);
	//void getMovingSpace(int& leftest, int& rightest);

	void findBestPosition(Position& bestPosition); //To Shape, but needs board
	virtual float getPositionScore(); //To Shape, but needs board

private:
	void randomShape(int positions[8]); //Receives an array of 4 coordinates on-screen (8 integers), generates a random shape, and updates the array accordingly
	void createCordsArr(int positions[8], int anchorX, int anchorY, int x1, int y1, int x2, int y2, int x3, int y3); //Sets new values to an empty positions array
	void updateBestPosition(float score, Position& bestPosition); //To Shape
	Block* getLeftestBlock();
	Block* getRightestBlock();
	void moveAllTheWay(GameConfig::Direction direction);
	int getOffsetX(GameConfig::Direction direction);

protected:
	enum class Type { HUMAN = true, BOT = false };
	void setBomb();
	void teleportToFloor();
	void teleportToCeiling();
	void getSpawnCords(int positions[8]);
	bool changeShapePosition(int positions[8]); //Receives a positions array and moves the blocks of the tetromino to the positions in the given array
	void glueShape();
	void unGlueShape();

};


#pragma once
#include "block.h"
#include "board.h"
#include "game.h"
#include "position.h"

//Class that handles the shapes (tetromino) of the game.
class Shape
{
	char ch; //The char the shape is made of
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

	int getDistanceFromBorder(GameConfig::Direction direction); //returns the distance of the shape from the Left/Right border of the board
	void findBestAndWorstPosition(Position& best, Position& worse); //Finds the best and worst position for the current shape (mainly used to computer player)
	virtual float getPositionScore(); //Calculates the score of the current position of the shape

private:
	void randomShape(int positions[8]); //Receives an array of 4 coordinates on-screen (8 integers), generates a random shape, and updates the array accordingly
	void createCordsArr(int positions[8], int anchorX, int anchorY, int x1, int y1, int x2, int y2, int x3, int y3); //Sets new values to an empty positions array
	void updateBestPosition(float score, Position& bestPosition); 
	void updateWorstPosition(float score, Position& worstPosition);
	void moveAllTheWay(GameConfig::Direction direction); //Moves all the way to the direction given
	int getOffsetX(GameConfig::Direction direction); //returns offSetX (1/-1) depending on the direction given

protected:
	void setBomb(); //Sets up the bomb
	void teleportToFloor();
	void teleportToCeiling();
	void getSpawnCords(int positions[8]); //Gets the cords of the spawn of the shape
	bool changeShapePosition(int positions[8]); //Receives a positions array and moves the blocks of the tetromino to the positions in the given array
	void glueShape(); //glues the shape to the board (updates freeSpaceArray of board)
	void unGlueShape();

};


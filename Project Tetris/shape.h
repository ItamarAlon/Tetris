#pragma once
#include "block.h"
#include "board.h"
#include "game.h"


//Class that handles the shapes (tetromino) of the game.
class Shape
{
	Block blockArr[4] = {}; //Each shape is made of 4 blocks. This array represents the blocks that make the tetrominoe.
	Board &board; //The board where the shape is placed
	int orientation; //The current orientation of the tetromino (because a shape can rotate during gameplay)
	int divider; //Number of orientations a shape has
	enum class Shapes {I,O,T,S,Z,J,L}; //All the shapes that can appear in game
	Shapes shape; //The current shape of the tetromino
public:
	Shape(Board& _board, char ch = -2); 
	void setShape(char ch = -2); //Sets a new shape for game
	void randomShape(int positions[8]); //Receives an array of 4 coordinates on-screen (8 integers), generates a random shape, and updates the array accordingly
	void print();
	void moveBy(int x, int y); //Moves the shape by a certain value (according to it's current value on-screen)
	bool moveShapeDown(); //Moves the shape 1 place down (if possible)
	void moveShapeLeftRight(int key); //Moves the shape left/right if possible (according to the input given from the keyboard)
	void createCordsArr(int positions[8], int anchorX, int anchorY, int x1, int y1, int x2, int y2, int x3, int y3); //Sets new values to an empty positions array
	void rotateShape(char key); //Rotates the shape (if possible)
	bool changeShapePosition(int positions[8]); //Receives a positions array and moves the blocks of the tetromino to the positions in the given array
	int getNextOrientation(int key); //Returns the next orientation of the block (relative to the input from the keyboard)

};


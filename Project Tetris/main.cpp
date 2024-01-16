#include "Libraries.h"
#include "block.h"
#include "Board.h"
#include "shape.h"


void main()
{
	bool shapeP1 = true;
	Board board;
	board.print();
	Shape s("XXXX",board, 254);


	while (true)
	{
		shapeP1=s.moveShapeDown();
		Sleep(500);
		if (shapeP1 == false)
			s.setShape("XXXX", 254);

	}


	gotoxy(0,board.Y_END + 2);
}
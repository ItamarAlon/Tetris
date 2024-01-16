#include "Libraries.h"
#include "block.h"
#include "Board.h"
#include "shape.h"


void main()
{
	bool shapeP1 = true;
	Board board;
	board.print();
	Shape s(board);


	while (true)
	{
		shapeP1=s.moveShapeDown();
		Sleep(200);
		if (shapeP1 == false)
			s.setShape(254);

	}


	gotoxy(0,board.Y_END + 2);
}
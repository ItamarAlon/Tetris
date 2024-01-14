#include "Libraries.h"
#include "block.h"
#include "Board.h"
#include "shape.h"


void main()
{
	Board board;
	board.print();
	Shape s("XXXX",board);
	//s.print();
	//while(_getch() != (char)GameConfig::Lkeys::ESC)

	while (true)
	{
		s.moveShapeDown();
		Sleep(500);
	}



	//s.moveShapeDown(500);
	//Block block(254);
	//board.moveBlockDownBoard(s, 500);
	//Shape shape("  X   X  X     X", b);
	//shape.moveBy(2, 2);
	//shape.print();

	gotoxy(0,board.Y_END + 2);
}
#include "stdafx.h"

using namespace std;

/* Piece legend
 *	1 = Black checker
 *	2 = Black king
 *  3 = White checker
 *	4 = White king
 */

void ResetBoard()
{
	// Clear Board
	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			_Board[x][y] = 0;
		}
	}

	// Place black's checkers: top of board
	for (int x = 0; x < 3; ++x)
	{
		if ((x % 2) == 0)
		{
			for (int y = 1; y <= 8; ++y)
			{
				if ((y % 2) != 0)
					_Board[x][y] = 1;
			}
		}
		else
		{
			for (int y = 0; y < 8; ++y)
			{
				if ((y % 2) == 0 || y == 0)
					_Board[x][y] = 1;
			}
		}
	}

	// Place white's checkers: bottom of board
	for (int x = 5; x < 8; ++x)
	{
		if ((x % 2) == 0)
		{
			for (int y = 1; y <= 8; ++y)
			{
				if ((y % 2) != 0)
					_Board[x][y] = 3;
			}
		}
		else
		{
			for (int y = 0; y < 8; ++y)
			{
				if ((y % 2) == 0 || y == 0)
					_Board[x][y] = 3;
			}
		}
	}
}

void PrintHeader()
{
	char c;
	fstream banner;
	banner.open("Banner.txt");
	while ((c = banner.get()) != EOF)
		cout << c;
}

// Refrain from using magic numbers in code. Use const or macros instead
// Place control flow statements on their own lines...
void PrintBoard()
{
	char c;
	int column = 0;
	int row = 0;
	int line_count = 0;
	int board_count = 0;
	int universalCount = 0;
	const int board_length = 36;	// length of the board
	const int line_length = 67;		// length of a line
	const int tiles_space = 4;		// space between board tiles

	fstream board;
	board.open("Board.txt");
	cout << "\n    1   2   3   4   5   6   7   8" << endl;
	while ((c = board.get()) != EOF)
	{
		// Yes, the following line looks ugly... but it is required
		if (((board_count / board_length) % 2) != 0 && board_count > board_length && ((line_count + 1) % tiles_space) == 0 && line_count >= 3 && line_count < board_length - 1)
		{
			switch (_Board[row][column])
			{
			case (1) :
				cout << 'b';
				break;
			case (2) :
				cout << 'B';
				break;
			case (3) :
				cout << 'w';
				break;
			case (4) :
				cout << 'W';
				break;
			default:
				cout << c;
				break;
			}
			++column;
		}
		// On the 11 and twelth lines and 56th position on that line
		else if (((universalCount / line_length) == 11 || (universalCount / line_length) == 12) && line_count == 56)
		{
			// Current line, even or odd? (line 11, line 12)
			if ((universalCount / line_length) % 2 != 0) cout << Captured[0];
			else cout << Captured[1];
		}
		else cout << c;

		// Reset column 
		if ((board_count % board_length) == 0)
		{
			column = 0;
		}

		if ((line_count % board_length) == 0 && ((universalCount / line_length) % 2) != 0 && line_count == board_length)
		{
			++row;
		}

		if ((universalCount % line_length) == 0 && (universalCount / line_length) != 0)
		{
			line_count = 0;
		}
		else
		{
			++line_count;
		}

		if ((universalCount % board_length) <= board_length && (universalCount % line_length) < board_length)
			++board_count;

		++universalCount;
	}
}

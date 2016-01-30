#include "stdafx.h"

using namespace std;

// Gametype Legend:
//	Player vs Player:	0
//		Black vs White
//	Player vs AI:		1
//		Player: Black
//	Player vs AI:		2
//		Player: White

// TODO:
//	Function to check valid moves
//	If a piece can be captured, that piece must be jumped.
//	If a piece reaches the opposite end of the board, king that piece (the first time).
//	** Swap the x and y cordinates! :( **
//	Add a "King me" function

/* Piece legend
*	1 = Black checker
*	2 = Black king
*	3 = White checker
*	4 = White king
*/

/*
	Checks if there is a winner
	return:
		white win:	1
		black win:	0
		no winner:	2
*/
int CheckWinner()
{
	// If captured[0] == 12, black wins.
	// If captured[1] == 12, white wins.
	if (Captured[0] == 12 && Captured[1] == 12)
		return 2; // Stalemate

	if (Captured[0] == 12)
		return black;
	else if (Captured[1] == 12)
		return white;
	else
		return 3; // No winner
}

// A piece has been captured, remove the piece from the board and increment the correct Captured[]
void CapturePiece(int PlayerPiece, int Square[])
{
	// Find the difference between source and destination
	// if source - destination == 2 ?
	// if destination - source == 2 ?
	_Board[Square[0]][Square[1]] = blank_square;
	++Captured[PlayerPiece];
}

// Remove the old piece and place the piece in the new square
void MovePiece(int Source[], int Destination[])
{
	int temp = _Board[Source[0]][Source[1]];
	_Board[Source[0]][Source[1]] = 0;
	_Board[Destination[0]][Destination[1]] = temp;
}

void KingMe(int PlayerPiece, int Square[])
{
	// Change the checker to a king if the piece is not already a king
	if (PlayerPiece == black)
	{
		if (Square[0] == 7)
		{
			if (_Board[Square[0]][Square[1]] == black_checker)
				_Board[Square[0]][Square[1]] = black_king;
		}
	}
	else
	{
		if (Square[0] == 0)
		{
			if (_Board[Square[0]][Square[1]] == white_checker)
				_Board[Square[0]][Square[1]] = white_king;
		}
	}
}

bool ForceCaptureScan(int player)
{
	// Scan all possible player moves to determine if a capture is possible
	for (int x = 0; x < 8; ++x)
	{
		for (int y = 0; y < 8; ++y)
		{
			if (player == black)
			{
				// Player is black
				if (_Board[x][y] == black_checker || _Board[x][y] == black_king)
				{
					// Black checker capture down and right
					if (_Board[x + 1][y + 1] == white_checker || _Board[x + 1][y + 1] == white_king)
					{
						if (x + 2 <= bottom_border && y + 2 <= right_border)
						{
							if (_Board[x + 2][y + 2] == blank_square)
							{
								return true;
							}
						}
					}
					// Black checker capture down and left
					if (_Board[x + 1][y - 1] == white_checker || _Board[x + 1][y - 1] == white_king)
					{
						if (x + 2 <= bottom_border && y - 2 >= left_border)
						{
							if (_Board[x + 2][y - 2] == blank_square)
							{
								return true;
							}
						}
					}
					// Black king capture up and right
					if ((_Board[x - 1][y + 1] == white_checker || _Board[x - 1][y + 1] == white_king) && _Board[x][y] == black_king)
					{
						if (x - 2 >= top_border && y + 2 <= right_border)
						{
							if (_Board[x - 2][y + 2] == blank_square)
							{
								return true;
							}
						}
					}
					// Black king capture up and left
					if ((_Board[x - 1][y - 1] == white_checker || _Board[x - 1][y - 1] == white_king) && _Board[x][y] == black_king)
					{
						if (x - 2 >= top_border && y - 2 >= left_border)
						{
							if (_Board[x - 2][y - 2] == blank_square)
							{
								return true;
							}
						}
					}
				}
			}
			else
			{
				// Player is white
				if (_Board[x][y] == white_checker || _Board[x][y] == white_king)
				{
					// White checker capture up and right
					if (_Board[x - 1][y + 1] == black_checker || _Board[x - 1][y + 1] == black_king)
					{
						if (x - 2 >= top_border && y + 2 <= right_border)
						{
							if (_Board[x - 2][y + 2] == blank_square)
							{
								return true;
							}
						}
					}
					// White checker capture up and left
					if (_Board[x - 1][y - 1] == black_checker || _Board[x - 1][y - 1] == black_king)
					{
						if (x - 2 >= top_border && y - 2 >= left_border)
						{
							if (_Board[x - 2][y - 2] == blank_square)
							{
								return true;
							}
						}
					}
					// White king checker capture down and right
					if ((_Board[x + 1][y + 1] == black_checker || _Board[x + 1][y + 1] == black_king) && _Board[x][y] == white_king)
					{
						if (x + 2 <= bottom_border && y + 2 <= right_border)
						{
							if (_Board[x + 2][y + 2] == blank_square)
							{
								return true;
							}
						}
					}
					// White king checker capture up and left
					if ((_Board[x + 1][y - 1] == black_checker || _Board[x + 1][y - 1] == black_king) && _Board[x][y] == white_king)
					{
						if (x + 2 <= bottom_border && y - 2 >= left_border)
						{
							if (_Board[x + 2][y - 2] == blank_square)
							{
								return true;
							}
						}
					}
				}
			}
		}
	}

	return false;
}

bool DoubleJump(int Square[])
{
	// If there is an enemy checker adjacent to the source square
	//	Check if there is an empty square behind it
	// Player is black
	if (_Board[Square[0]][Square[1]] == black_checker || _Board[Square[0]][Square[1]] == black_king)
	{
		// Black checker double jump down and right
		if (_Board[Square[0] + 1][Square[1] + 1] == white_checker || _Board[Square[0]][Square[1]] == white_king)
		{
			if (Square[0] + 2 <= bottom_border && Square[1] + 2 <= right_border)
			{
				if (_Board[Square[0] + 2][Square[1] + 2] == blank_square)
				{
					return true;
				}
			}
		}
		// Black checker double jump down and left
		if (_Board[Square[0] + 1][Square[1] - 1] == white_checker || _Board[Square[0]][Square[1]] == white_king)
		{
			if (Square[0] + 2 <= bottom_border && Square[1] - 2 >= left_border)
			{
				if (_Board[Square[0] + 2][Square[1] - 2] == blank_square)
				{
					return true;
				}
			}
		}
		// Black king checker double jump up and right
		if ((_Board[Square[0] - 1][Square[1] + 1] == white_checker || _Board[Square[0]][Square[1]] == white_king) && _Board[Square[0]][Square[1]] == black_king)
		{
			if (Square[0] - 2 <= bottom_border && Square[1] + 2 <= right_border)
			{
				if (_Board[Square[0] - 2][Square[1] + 2] == blank_square)
				{
					return true;
				}
			}
		}
		// Black king checker double jump up and left
		if ((_Board[Square[0] - 1][Square[1] - 1] == white_checker || _Board[Square[0]][Square[1]] == white_king) && _Board[Square[0]][Square[1]] == black_king)
		{
			if (Square[0] - 2 >= top_border && Square[1] - 2 >= left_border)
			{
				if (_Board[Square[0] - 2][Square[1] - 2] == blank_square)
				{
					return true;
				}
			}
		}
	}
	else if (_Board[Square[0]][Square[1]] == white_checker || _Board[Square[0]][Square[1]] == white_king)
	{
		// White checker double jump up and right
		if (_Board[Square[0] - 1][Square[1] + 1] == black_checker || _Board[Square[0] - 1][Square[1] + 1] == black_king)
		{
			if (Square[0] - 2 >= top_border && Square[1] + 2 <= right_border)
			{
				if (_Board[Square[0] - 2][Square[1] + 2] == blank_square)
				{
					return true;
				}
			}
		}
		// White checker double jump up and left
		if (_Board[Square[0] - 1][Square[1] - 1] == black_checker || _Board[Square[0] - 1][Square[1] - 1] == black_king)
		{
			if (Square[0] - 2 >= top_border && Square[1] - 2 >= left_border)
			{
				if (_Board[Square[0] - 2][Square[1] - 2] == blank_square)
				{
					return true;
				}
			}
		}
		// White king checker double jump down and right
		if ((_Board[Square[0] + 1][Square[1] + 1] == black_checker || _Board[Square[0] + 1][Square[1] + 1] == black_king) && _Board[Square[0]][Square[1]] == white_king)
		{
			if (Square[0] + 2 <= bottom_border && Square[1] + 2 <= right_border)
			{
				if (_Board[Square[0] + 2][Square[1] + 2] == blank_square)
				{
					return true;
				}
			}
		}
		// White king checker double jump down and left
		if ((_Board[Square[0] + 1][Square[1] - 1] == black_checker || _Board[Square[0] + 1][Square[1] - 1] == black_king) && _Board[Square[0]][Square[1]] == white_king)
		{
			if (Square[0] + 2 <= bottom_border && Square[1] - 2 >= left_border)
			{
				if (_Board[Square[0] + 2][Square[1] - 2] == blank_square)
				{
					return true;
				}
			}
		}
	}
	return false;
}

/*
	Checks if the current move is valid
	return:
		the move is valid:		true
		the move is not valid:	false
		Double jump possible:	2
*/
int ValidMove(int Player, int PlayerPiece, int Source[], int Destination[])
{
	// Black checkers can move to (x + 1), (y +/- 1)
	// Black kings can move to (x +/- 1), (y +/- 1)
	// White checkers can move to (x - 1), (y +/- 1)
	// White kings can move to (x +/- 1) , (y +/- 1)

	if (PlayerPiece == black)
	{
		switch (_Board[Source[0]][Source[1]])
		{
			case (black_checker) :
			{
				// Ensure there is no piece in the destination square
				switch (_Board[Destination[0]][Destination[1]])
				{
					case (blank_square) :
					{
						// There is no piece in the destination square. Test if the destination and source square are plus or minus one of each other
						if ((Source[0] + 1) == Destination[0])
						{
							if ((Source[1] - 1) == Destination[1])
							{
								// The player is attempting to choose a square that is +1 or -1, check if a piece can be captured
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else if (Source[1] == (Destination[1] - 1))
							{
								// The player is attempting to choose a square that is +1 or -1, check if a piece can be captured
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else
							{
								cout << "You have selected an invalid destination square..." << endl;
								system("pause");
								return 0;
							}
						}
						// The player is attempting to capture a checker, ensure there is a piece +/- 1 of the destination
						else if ((Source[0] + 2) == Destination[0])
						{
							// Is the player capturing to the right?
							if ((Source[1] - 2) == Destination[1])
							{
								// Ensure the square that is + 1 of Source[1] is an enemy checker
								if (_Board[Source[0] + 1][Source[1] - 1] == white_checker || _Board[Source[0] + 1][Source[1] + 1] == white_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = {Source[0] + 1, Source[1] - 1};
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									// Can the player double jump?
									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
								else
								{
									cout << "Do you doubt your checkers? You are trying to capture your own piece..." << endl;
									system("pause");
									return 0;
								}
							}
							// Is the player capturing to the left?
							else if ((Source[1] + 2) == Destination[1])
							{
								// Ensure the square that -1 of Source[1] is an enemy checker
								if (_Board[Source[0] + 1][Source[1] + 1] == white_checker || _Board[Source[0] + 1][Source[1] - 1] == white_king)
								{
									// An enemy checker has been captured, remove the captured piece from the board
									int Square[2] = {Source[0] + 1, Source[1] + 1};
									CapturePiece(PlayerPiece, Square);

									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
								else
								{
									cout << "You are trying to capture your own piece or a piece that does not exist..." << endl;
									system("pause");
									return 0;
								}
							}
							else
							{
								cout << "That is an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						else
						{
							cout << "That is an invalid move..." << endl;
							system("pause");
							return 0;
						}
						break;
					}
					case (black_checker) :
					{
						cout << "Only one checker per square please!" << endl;
						system("pause");
						return 0;
						break;
					}
					case (black_king) :
					{
						cout << "Only one checker per square please!" << endl;
						system("pause");
						return 0;
						break;
					}
					case (white_checker) :
					{
						cout << "If you are attempting to capture an enemy checker, move to the square that is behind the enemy. :)" << endl;
						cout << "Only one checker per square pleae..." << endl;
						system("pause");
						return 0;
						break;
					}
					case (white_king) :
					{
						cout << "If you are attempting to caputre an enemy checker, move to the square that is behind the enemy. :)" << endl;
						cout << "Only one checker per square please..." << endl;
						system("pause");
						return 0;
						break;
					}
					default :
					{
						cout << "There was an undefined error..." << endl;
						break;
					}
				}
				break;
			}
			case (black_king) :
			{
				switch (_Board[Destination[0]][Destination[1]])
				{
					case (blank_square) :
					{
						// Is the the player moving up or down?
						if ((Source[0] + 1) == Destination[0])
						{
							// The player is moving down. Is he moving left or right? Left?
							if (Source[1] == (Destination[1] + 1))
							{
								// The player is moving down and to the left
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							// Is the player moving to the right?
							else if (Source[1] == (Destination[1] - 1))
							{
								// The player is moving down and to the left
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else
							{
								cout << "You are moving too far away..." << endl;
								system("pause");
								return 0;
							}
						}
						// Is the player attempting to move up?
						else if ((Source[0] - 1) == Destination[0])
						{
							// The player is attempting to move down. Is he moving left or right?
							if ((Source[1] + 1) == Destination[1])
							{
								// The player is moving up and to the right
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else if ((Source[1] - 1) == Destination[1])
							{
								// The player is moving up and to the left
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else
							{
								cout << "That is an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						// Is the player attempting to capture a piece downwards?
						else if ((Source[0] + 2) == Destination[0])
						{
							// The player might be attempting to capture a piece downwards. Is he capturing to the left or right?
							if ((Source[1] + 2) == Destination[1])
							{
								// The player is attempting to capture a piece to the right.
								// Is there a piece for the player to capture?
								if (_Board[Source[0] + 1][Source[1] + 1] == white_checker || _Board[Source[0] + 1][Source[1] + 1] == white_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] + 1, Source[1] + 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
							}
							else if ((Source[1] - 2) == Destination[1])
							{
								// The player is attempting to capture a piece to the left
								// Is there a piece for the player to capture?
								if (_Board[Source[0] + 1][Source[1] - 1] == white_checker || _Board[Source[0] + 1][Source[1] - 1] == white_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] + 1, Source[1] + 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
							}
							else
							{
								// The player is attempting to capture a piece that is greater than two squares from the source...
								cout << "That is an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						// Is the player attempting to capture a piece upwards?
						else if ((Source[0] - 2) == Destination[0])
						{
							// The player might be capturing a piece upwards. Capture to the right?
							if ((Source[1] + 2) == Destination[1])
							{
								// Player is capturing a piece up and to the right
								// Is there a piece for the player to capture?
								if (_Board[Source[0] - 1][Source[1] + 1] == white_checker || _Board[Source[0] - 1][Source[1] + 1] == white_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] - 1, Source[1] + 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
							}
							// Capture to the left?
							else if ((Source[1] - 2) == Destination[1])
							{
								// Player is capturing a piece up and to the left
								// Is there a piece for the player to capture?
								if (_Board[Source[0] - 1][Source[1] - 1] == white_checker || _Board[Source[0] - 1][Source[1] - 1] == white_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] - 1, Source[1] - 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
							}
							else
							{
								// The player is attempting to capture a piece that is greater than two sqaures from the source...
								cout << "That is an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						else
						{
							cout << "You have selected an invalid destination square..." << endl;
							system("pause");
							return 0;
						}
						break;
					}
					case (black_checker) :
					{
						cout << "Only one checker per square please..." << endl;
						system("pause");
						return 0;
						break;
					}
					case (black_king) :
					{
						cout << "Only one checker per square please..." << endl;
						system("pause");
						return 0;
						break;
					}
					case (white_checker) :
					{
						cout << "If you are attempting to capture an enemy checker, move to the square that is behind the enemy. :)" << endl;
						cout << "Only one checker per square pleae..." << endl;
						system("pause");
						return 0;
						break;
					}
					case (white_king) :
					{
						cout << "If you are attempting to capture an enemy checker, move to the square that is behind the enemy. :)" << endl;
						cout << "Only one checker per square please..." << endl;
						system("pause");
						return 0;
						break;
					}
					default :
					{
						cout << "There was an unspecified error..." << endl;
						system("pause");
						return 0;
						break;
					}
				}
				break;
			}
			case (white_checker) :
			case (white_king) :
			{
				cout << "That is not your piece!" << endl;
				system("pause");
				return 0;
				break;
			}
			case (blank_square) :
			{
				cout << "One cannot move a piece that does not exist..." << endl;
				system("pause");
				return 0;
				break;
			}
			default :
			{
				cout << "There was an unspecified error..." << endl;
				system("pause");
				return 0;
				break;
			}
		}
	}
	else
	{
		// Process valid moves for white...
		switch (_Board[Source[0]][Source[1]])
		{
			case (white_checker) :
			{
				switch (_Board[Destination[0]][Destination[1]])
				{
					case (blank_square) :
					{
						// Test if the destination square is -1 of the source square
						if ((Source[0] - 1) == Destination[0])
						{
							// The player is moving up
							// Is the player moving to the left or right? Right?
							if ((Source[1] + 1) == Destination[1])
							{
								// The player is moving to the right
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							// Is the player moving to the left?
							else if ((Source[1] - 1) == Destination[1])
							{
								// The player is moving to the left
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else
							{
								// This is an error...
								cout << "You have made an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						// Test if the destination square is -2 from the source square, they are trying to capture
						else if ((Source[0] - 2) == Destination[0])
						{
							// Is the player capturing to the right or left?
							// Is he capturing to the right?
							if ((Source[1] + 2) == Destination[1])
							{
								// Is there an enemy piece that is +1 from the source?
								if (_Board[Source[0] - 1][Source[1] + 1] == black_checker || _Board[Source[0] + 1][Source[1] + 1] == black_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] - 1, Source[1] + 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
								else
								{
									cout << "This is an invalid move..." << endl;
									system("pause");
									return 0;
								}
							}
							// Is he capturing to the left?
							else if ((Source[1] - 2) == Destination[1])
							{
								// Is there an enemy piece that is -1 fomr the source?
								if (_Board[Source[0] - 1][Source[1] - 1] == black_checker || _Board[Source[0] - 1][Source[1] - 1] == black_king)
								{
									// Valid capture
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] - 1, Source[1] - 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
								else
								{
									cout << "You tried to capture a piece that does not exist or you are trying to capture your own piece..." << endl;
									system("pause");
									return 0;
								}
							}
							else
							{
								cout << "This is an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						else
						{
							cout << "This is an invalid move..." << endl;
							system("pause");
							return 0;
						}
						break;
					}
					case (black_checker) :
					case (black_king) :
						cout << "If you are trying to capture a checker, move chose the square that is behind the current square..." << endl;
						system("pause");
						return 0;
						break;
					case (white_checker) :
					case (white_king) :
						cout << "Only one checker per square please..." << endl;
						system("pause");
						return 0;
						break;
					default :
						break;
				}
				break;
			}
			case (white_king) :
			{
				switch (_Board[Destination[0]][Destination[1]])
				{
					case (blank_square) :
					{
						// Valid moves for white's kings here...
						// Is the the player moving up or down?
						if ((Source[0] + 1) == Destination[0])
						{
							// The player is moving down. Is he moving left or right? Left?
							if (Source[1] == (Destination[1] + 1))
							{
								// The player is moving down and to the left
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							// Is the player moving to the right?
							else if (Source[1] == (Destination[1] - 1))
							{
								// The player is moving down and to the left
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else
							{
								cout << "You are moving too far away..." << endl;
								system("pause");
								return 0;
							}
						}
						// Is the player attempting to move up?
						else if ((Source[0] - 1) == Destination[0])
						{
							// The player is attempting to move up. Is he moving left or right?
							if ((Source[1] + 1) == Destination[1])
							{
								// The player is moving up and to the right
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else if ((Source[1] - 1) == Destination[1])
							{
								// The player is moving up and to the left
								if (force_capture && ForceCaptureScan(PlayerPiece))
								{
									cout << "Force Capture has been turned on and a capture is possible..." << endl;
									system("pause");
									return 0;
								}
								else
								{
									MovePiece(Source, Destination);
									return 1;
								}
							}
							else
							{
								cout << "That is an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						// Is the player attempting to capture a piece downwards?
						else if ((Source[0] + 2) == Destination[0])
						{
							// The player might be attempting to capture a piece downwards. Is he capturing to the left or right?
							if ((Source[1] + 2) == Destination[1])
							{
								// The player is attempting to capture a piece to the right.
								// Is there a piece for the player to capture?
								if (_Board[Source[0] + 1][Source[1] + 1] == black_checker || _Board[Source[0] + 1][Source[1] + 1] == black_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] + 1, Source[1] + 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
							}
							else if ((Source[1] - 2) == Destination[1])
							{
								// The player is attempting to capture a piece to the left
								// Is there a piece for the player to capture?
								if (_Board[Source[0] + 1][Source[1] - 1] == black_checker || _Board[Source[0] + 1][Source[1] - 1] == black_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] + 1, Source[1] - 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
							}
							else
							{
								// The player is attempting to capture a piece that is greater than two squares from the source...
								cout << "That is an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						// Is the player attempting to capture a piece upwards?
						else if ((Source[0] - 2) == Destination[0])
						{
							// The player might be capturing a piece upwards. Capture to the right?
							if ((Source[1] + 2) == Destination[1])
							{
								// Player is capturing a piece up and to the right
								// Is there a piece for the player to capture?
								if (_Board[Source[0] - 1][Source[1] + 1] == black_checker || _Board[Source[0] - 1][Source[1] + 1] == black_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] - 1, Source[1] + 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
							}
							// Capture to the left?
							else if ((Source[1] - 2) == Destination[1])
							{
								// Player is capturing a piece up and to the left
								// Is there a piece for the player to capture?
								if (_Board[Source[0] - 1][Source[1] - 1] == black_checker || _Board[Source[0] - 1][Source[1] - 1] == black_king)
								{
									// An enemy piece has been captured, remove the captured piece from the board
									int Square[2] = { Source[0] - 1, Source[1] - 1 };
									CapturePiece(PlayerPiece, Square);

									// Move piece to the new square and remove the original
									MovePiece(Source, Destination);

									if (DoubleJump(Destination))
									{
										return 2;
									}
									else
										return 1;
								}
							}
							else
							{
								// The player is attempting to capture a piece that is greater than two sqaures from the source...
								cout << "That is an invalid move..." << endl;
								system("pause");
								return 0;
							}
						}
						else
						{
							cout << "You have selected an invalid destination square..." << endl;
							system("pause");
							return 0;
						}
						break;
					}
					case (black_checker) :
					case (black_king) :
						cout << "If you are trying to capture a checker, move chose the square that is behind the current square..." << endl;
						system("pause");
						return 0;
						break;
					case (white_checker) :
					case (white_king) :
						cout << "Only one checker per square please..." << endl;
						system("pause");
						return 0;
						break;
					default:
						break;
				}
				break;
			}
			case (black_checker) :
			case (black_king) :
				cout << "That is not your piece!" << endl;
				system("pause");
				return 0;
				break;
			case (blank_square) :
				cout << "One cannot move a piece that does not exist..." << endl;
				system("pause");
				return 0;
				break;
			default :
				cout << "There was an unspecified error..." << endl;
				system("pause");
				return 0;
				break;
		}
	}
	return 0;
}

bool CordinateInput(string test, int *SquarePointer)
{
	const char alpha[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	const char nums[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
	bool condition1 = false;
	bool condition2 = false;
	bool condition3 = false;

	// if the first char is a letter A - H, assign the numerical value - 1 to *(SquarePointer + 0)
	// if the second char is a number 1 - 8, assign the value - 1 to *(SquarePointer + 1)
	for (int i = 0; i < 8; ++i)
	{
		if (test[0] == alpha[i])
		{
<<<<<<< HEAD
			Player2(Player);
			if (CheckWinner() == 3)
				Player1(Player);
=======
			*(SquarePointer + 0) = i;
			condition1 = true;
>>>>>>> origin/master
		}
		if (test[1] == nums[i])
		{
<<<<<<< HEAD
			Player1(Player);
			if (CheckWinner() == 3)
				Player2(Player);
=======
			*(SquarePointer + 1) = i;
			condition2 = true;
>>>>>>> origin/master
		}
	}

	// Does the string have exactly 2 characters?
	if (strlen(test.c_str()) == 2)
		condition3 = true;

	if (condition1 && condition2 && condition3)
		return true;
	else
		return false;
}

void Player1(int Player)
{
	int Source[2] = { 0, 0 };
	int *SourcePointer = Source;
	int Destination[2] = { 0, 0 };
	int *DestinationPointer = Destination;
	int PlayerPiece;
	string input;

	if (Player == black)
		PlayerPiece = black;
	else
		PlayerPiece = white;

	do
	{
		system("cls");
		PrintHeader();
		PrintBoard();
		do
		{
			if (PlayerPiece == black)
			{
				cout << "Player 1 - Select a black piece to move: ";
				getline(cin, input);
			}
			else
			{
				cout << "Player 1 - Select a white piece to move: ";
				getline(cin, input);
			}

		} while (!CordinateInput(input, SourcePointer));

		do
		{
			cout << "Where do you want to move?: ";
			getline(cin, input);
		} while (!CordinateInput(input, DestinationPointer));

	} while (ValidMove(Player, PlayerPiece, Source, Destination) != 1);
	KingMe(PlayerPiece, Destination);
}

void Player2(int Player)
{
	int Source[2] = { 0, 0 };
	int *SourcePointer = Source;
	int Destination[2] = { 0, 0 };
	int *DestinationPointer = Destination;
	int PlayerPiece;
	string input;

	if (Player == black)
		PlayerPiece = white;
	else
		PlayerPiece = black;

	do
	{
		system("cls");
		PrintHeader();
		PrintBoard();
		do
		{
			if (PlayerPiece == black)
			{
				cout << "Player 2 - Select a black piece to move: ";
				getline(cin, input);
			}
			else
			{
				cout << "Player 2 - Select a white piece to move: ";
				getline(cin, input);
			}

		} while (!CordinateInput(input, SourcePointer));

		do
		{
			cout << "Where do you want to move?: ";
			getline(cin, input);
		} while (!CordinateInput(input, DestinationPointer));

	} while (ValidMove(Player, PlayerPiece, Source, Destination) != 1);
	KingMe(PlayerPiece, Destination);
}

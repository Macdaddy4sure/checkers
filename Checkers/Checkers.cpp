#include "stdafx.h"

using namespace std;

// This program, well... plays checkers!

int _Board[8][8];
int Captured[2] = { 0, 0 };
bool force_capture = true;

// Captured Pieces legend:
//	White pieces black has captured: 0
//	Black Pieces white has captured: 1

bool ValidInput(string menu, string *test, int *pointer)
{
	if (menu == "main")
	{
		if (*test == "black" || *test == "0" || *test == "BLACK" || *test == "Black")
		{
			*pointer = 0;
			return true;
		}
		else if (*test == "white" || *test == "1" || *test == "WHITE" || *test == "White")
		{
			*pointer = 1;
			return true;
		}
		else
		{
			cout << "You have entered an invalid response..." << endl;
			system("pause");
			return false;
		}
	}

	return false;
}

int main()
{
	int Player = 2;
	int *PlayerPointer = &Player;
	string input;
	string *inputPointer = &input;

	ResetBoard();

	do
	{
		system("cls");

		PrintHeader();
		PrintBoard();

		cout << "Player 1, what color would you like to be?" << endl;
		cout << "Black or White?: ";
		getline(cin, input);
	} while (!ValidInput("main", inputPointer, PlayerPointer));

	do
	{
		if (Player == black)
		{
			Player2(Player);
			Player1(Player);
		}
		else
		{
			Player1(Player);
			Player2(Player);
		}
	} while (CheckWinner() == 3);

	switch (CheckWinner())
	{
		case (black) :
			if (Player == black)
				cout << "Player 1 Wins!" << endl;
			else
				cout << "Player 2 Wins!" << endl;
			break;
		case (white) :
			if (Player == black)
				cout << "Player 2 Wins!" << endl;
			else
				cout << "Player 1 Wins!" << endl;
			break;
		case (2) :
			cout << "The game is a draw!" << endl;
			break;
		default :
			cout << "There was an unspecified error..." << endl;
			break;
	}

	system("pause");

    return 0;
}

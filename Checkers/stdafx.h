// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

#define black_checker	1
#define black_king		2
#define white_checker	3
#define white_king		4
#define blank_square	0
#define black			0
#define white			1

// Define Board borders
#define left_border		0
#define right_border	7
#define top_border		0
#define bottom_border	7

extern int _Board[8][8];
extern int Captured[2];
extern bool force_capture;

void PrintHeader();
void PrintBoard();
void ResetBoard();
void Player1(int Player);
void Player2(int Player);
int CheckWinner();
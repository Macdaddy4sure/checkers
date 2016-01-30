# Checkers
Beginner C++ console checkers game

##Description
This application allows two players to player checkers against eacher other. The project is meant for novice programmers as this is my first project on github. Any criticism is appreciated! Up to and including advising me to quit pursing porgramming.
  
##Planned Features
AI: I plan to implement a variation of the MiniMax algorithm for the AI.
    
##Project Files:

    Checkers.cpp:
        Defines the entry point for the application.
        Functions:
            ValidInput() - String parsing and input checking for the main menu.
            main() - Application entry point, main menu, and game loop
            
    Game.cpp:
        Handles all game functions except for the main menu.
        Functions: 
            CheckWinner() - Self explanatory.
            CapturePiece() - Executed when a piece is captured, self-explanatory.
            MovePiece() - Executed when a piece is moved.
            KingMe() - When a normal checker of either color reaches the opposite side, the piece is magically transformed into a 'King'.
            ForceCaptureScan() - If ForceCapture is enabled, players must capture any piece given the oppertunity. This function scans the board to check if the player is capable of capturing a piece.
            DoubleJump() - After a player captures a piece,  this function scans all squares adjacent to the destination square to determine if the player can 'Double Jump'.
            ValidMove() - Is the player making a valid move, and if not tell them why. (The 'meat and potatoes' of the program...)
            CordinateInput() - When the user keys in tile cordinates, this function ensures they are within acceptable bounds.
            Player1() - Invoked when it is Player 1's turn.
            Player2() - Invoked when it is Player 2's turn.
            
    AI.cpp:
        This file is merely a stub for a new feature coming in v2.0.
        Functions:
            AI() - Will be invoked when it is the AI's turn, but for now serves as a stub.
            
    Extras.cpp:
      This file is home to extra functions
      Functions:
        ResetBoard() - Sets the board to initial values, black on top, and white on bottom. (No pun intended)
        PrintHeader() - Prints the program's header from Banner.txt
        PrintBoard() - Prints the board and sets pieces.
        
    stdafx.h:
        Include file for standard system include files or project specific include files.
        
Thanks again!
  - Tyler Crockett (Macdaddy4sure)

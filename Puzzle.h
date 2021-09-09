//Daniel Martín & Laura San Martín
#include "UtilitiesSYS.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#ifndef Puzzle_h
#define Puzzle_h

typedef enum
{
	OneDim,
	TwoDim
} tGameMode; // Enumerated type fot the game mode (1D or 2D)


struct tPuzzle
{
	string name;
	string file;
	tGameMode GameMode = OneDim;
	int attempts = 0;
	tMatrixChar initialMatrix;
	tMatrixChar objetiveMatrix;
};

void mainPuzzle(tPuzzle& p); // Function that solves a puzzle
bool load(tPuzzle& p, tGameMode type); // Opens the corresponding file and calls the load function of the Matrix module
void show(const tPuzzle& p); // Displays the matrices
void showOne(tMatrixChar matrix); // Shows one matrix
bool play(tPuzzle& p); // Allows the user to perform the actions necessary to play and controls whether the limit of allowed actions has been reached
bool action(tPuzzle& p); // According to the action command typed by the user, it calls the corresponding action defined in the Matrix module

bool operator <(const tPuzzle& p1, const tPuzzle& p2); // less attempts than
bool operator >(const tPuzzle& p1, const tPuzzle& p2); // more attempts than
bool operator ==(const tPuzzle& p1, const tPuzzle& p2); // Same file name

#endif
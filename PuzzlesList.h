//Daniel Martín & Laura San Martín
#pragma once

#include "Puzzle.h"
#ifndef PuzzlesList_h
#define PuzzlesList_h
#include <iostream>
#include <string>
using namespace std;

const int MAX_PUZZLES = 100;

typedef tPuzzle *tPtrPuz;

struct tPuzzlesList
{
	int numpuzzles;
	tPtrPuz puzzles[MAX_PUZZLES];
};

typedef tPuzzlesList tGatheredPuzzles[2];

void initialize(tGatheredPuzzles& gp); // initialize the two lists of puzzels.
bool load(tGatheredPuzzles& gp); // loads the data contained in the file puzzlesData.txt.The data is arranged in the file in the same order they should be in the list, in increasing order of the maximum number of attempts to complete the puzzleand equal attempts in alphabetical order of the name of the puzzle.
void save(const tGatheredPuzzles& gp); // saves in the file puzzlesData.txt the list of 1D and 2D puzzles with the same format as the input file, and ordered according to the lists.
int choosePuzzle(tPuzzlesList& pl); // displays the list of puzzles and allows the user to choose one of them.It must give the option of displaying the list from highest to lowest number of movements or vice versa.
bool sortedInsert(tPuzzlesList& pl, tPuzzle* p); // inserts a new puzzle in the list of puzzles in order.
void showList(tPuzzlesList& pl); // displays a list of puzzles(with name of puzzle + máximum number ofmovements) and also the 0, -1 and -2 options of the assignment.
void sortIncreasing(tPuzzlesList& pl); // sort a list of puzzles in increasing order.
void sortDecreasing(tPuzzlesList& pl); // sorts a list of puzzles in decreasing order.
void freeMem(tGatheredPuzzles& gp); // frees Dynamic memory


#endif

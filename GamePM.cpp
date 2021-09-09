//Daniel Martín & Laura San Martín
#include "GamePM.h"
#include <string>
using namespace std;

int mainGatheredPuzzles()
{
	tGatheredPuzzles gp;
	int op = -1;
	int p = 0;
	bool loaded = false;
	string name, file;

	tPuzzle puzzle;
	typedef tPuzzle* tPtrPuz;
	tPtrPuz pointer = new tPuzzle;

	initialize(gp); //Initializing the game, counters to zero


	if (load(gp))
	{
		for (int i = 0; i < gp[0].numpuzzles; i++)
		{
			load(*gp[0].puzzles[i], OneDim); // Loads the 1D puzzles
		}
		for (int i = 0; i < gp[1].numpuzzles; i++)
		{
			load(*gp[1].puzzles[i], TwoDim); // Loads the 2D puzzles
		}

	}

	while (op != 0) // Not exiting the game
	{
		op = menu(); // The user chooses the game mode
		//Lists always in increasing order
		sortIncreasing(gp[0]);
		sortIncreasing(gp[1]);
		switch (op)
		{
		case 1:
		
			//Game mode : 1D
			p = choosePuzzle(gp[0]);
			if (p != 0)
			{
				p--;
				mainPuzzle(*gp[0].puzzles[p]);
			}
			break;
		
		case 2:
			
			//Game mode : 2D
			p = choosePuzzle(gp[1]);
			if (p != 0)
			{
				p--;
				mainPuzzle(*gp[1].puzzles[p]);
			}
			break;
		
		case 3:
		
			//Inserting a new puzzle
			int type;


			sortIncreasing(gp[0]); // 1D in increasing order
			sortIncreasing(gp[1]); // 2D in increasing order
			cout << endl;
			cout << "1D Challenges" << endl;
			for (int i = 0; i < gp[0].numpuzzles; i++) // Prints list of 1D puzzles
			{
				cout << 1 + i << ".  " << gp[0].puzzles[i]->name << " with a maximum number of " << gp[0].puzzles[i]->attempts << " movement(s)" << endl;
			}
			cout << endl;
			cout << "2D Challenges:" << endl;
			for (int i = 0; i < gp[1].numpuzzles; i++) //  Prints list of 2D puzzles
			{
				cout << 1 + i << ".  " << gp[1].puzzles[i]->name << " with a maximum number of " << gp[1].puzzles[i]->attempts << " movement(s)" << endl;
			}
			cout << endl;
			cout << "Name for the new puzzle: "; 
			cin.ignore();
			getline(cin, pointer->name); // Name of the new challenge
			cout << "Name of the file for the new puzzle (with .txt): ";
			cin >> pointer->file; // File to load
			cout << "Choose the type:" << endl; // 1D or 2D
			cout << "1. OneDim" << endl;
			cout << "2. TwoDim" << endl;
			cout << "Option:";
			cin >> type;


			// Assigning the game mode
			if (type == 1)
			{
				(*pointer).GameMode = OneDim; 

			}
			else if (type == 2)
			{
				(*pointer).GameMode = TwoDim;
			}

			loaded = load(*pointer, (*pointer).GameMode); // Loads the new puzzle
			if (loaded)
			{
				sortedInsert(gp[type - 1], pointer); // Inserts the new puzzle in the list
				showList(gp[type - 1]); // Shows the list again with the new puzzle inserted
			}
			break;

		
		}
	}
	// Saving the gathered puzzles and freeing dynamic memory
	save(gp); 
	freeMem(gp);

	return 0;
}


int menu() // To choose the mode or to insert a new puzzle
{
	int op = 0;
	cout << "1. Solve a 1D puzzle" << endl;
	cout << "2. Solve a 2D puzzle" << endl;
	cout << "3. Add a puzzle to the catalog" << endl;
	cout << "0. Exit" << endl;
	cout << endl;
	cout << "Choose an option :";
	cin >> op;

	return op;
}






//Daniel Martín & Laura San Martín
#include "PuzzlesList.h"
#include <string>
using namespace std;
const string FileName = "puzzlesData.txt";

bool find(const tPuzzlesList& pl, tPuzzle* p, int& pos); // Private function

void initialize(tGatheredPuzzles& gp) // Counters to zero
{
	gp[0].numpuzzles = 0;
	gp[1].numpuzzles = 0;
}
bool load(tGatheredPuzzles& gp) //loads the data contained in the file puzzlesData.txt
{
	ifstream file;
	bool ok = false;
	char c;

	for (int i = 0; i < MAX_PUZZLES; i++) //To initialize the pointers
	{
		gp[0].puzzles[i] = NULL;
		gp[1].puzzles[i] = NULL;

	}

	file.open(FileName);
	if (file.is_open())
	{
		ok = true;
		file >> gp[0].numpuzzles; // 1D counter
		file.get(c);
		for (int i = 0; i < gp[0].numpuzzles; i++)
		{
			gp[0].puzzles[i] = new tPuzzle;
			gp[0].puzzles[i]->GameMode = OneDim; // 1D
			getline(file, gp[0].puzzles[i]->name); // reads the name of the challenge
			getline(file, gp[0].puzzles[i]->file); // reads the file where is located
		}

		file >> gp[1].numpuzzles; // 2D counter
		file.get(c);

		for (int i = 0; i < gp[1].numpuzzles; i++)
		{
			gp[1].puzzles[i] = new tPuzzle;
			gp[1].puzzles[i]->GameMode = TwoDim; // 2D
			getline(file, gp[1].puzzles[i]->name);  // reads the name of the challenge
			getline(file, gp[1].puzzles[i]->file); // reads the file where is located
		}
	}
	else
	{
		cout << "File not found!" << endl;
	}


	file.close();

	return ok;
}
void save(const tGatheredPuzzles& gp) //saves in the file puzzlesData.txt the list of 1D and 2D puzzles with the same format as the input file, and ordered according to the lists
{
	ofstream file;

	file.open(FileName, ios::trunc);
	if (file.is_open())
	{
		int max = 0;

		max = gp[0].numpuzzles; // max = 1D counter
		file << max << endl; // Writing in the file the number of challenges (1D) that are on the list


		for (int i = 0; i < max; i++)
		{

			// Writing the name of the puzzle anf the name of the file
			file << gp[0].puzzles[i]->name;
			file << endl;
			file << gp[0].puzzles[i]->file;
			file << endl;

		}

		max = gp[1].numpuzzles; // max = 2D counter
		file << max << endl; // Writing in the file the number of challenges (2D) that are on the list

		for (int i = 0; i < max; i++)
		{
			// Writing the name of the puzzle anf the name of the file
			file << gp[1].puzzles[i]->name;
			file << endl;
			file << gp[1].puzzles[i]->file;
			file << endl;
		}
	}

	file.close();
}

int choosePuzzle(tPuzzlesList& pl) // Displays the list of puzzles and allows the user to choose one of them 
{
	int op = 0;

	cout << "The following challenges are available in this version:" << endl;
	showList(pl);
	cout << "Choose a challenge: " << endl;
	cin >> op;

	//It must give the option of displaying the list from highest to lowest number of movements or vice versa
	while ((op == -2) || (op == -1))
	{
		if (op == -2)
		{
			sortIncreasing(pl);
			cout << "The following challenges are available in this version:" << endl;
			showList(pl);
		}
		else if (op == -1)
		{
			sortDecreasing(pl);
			cout << "The following challenges are available in this version:" << endl;
			showList(pl);
		}
		cout << "Choose a challenge: " << endl;
		cin >> op;
	}


	return op;
}
void showList(tPuzzlesList& pl) //Displays a list of puzzles(with name of puzzle + máximum number of movements) 
{
	cout << endl;

	for (int i = 0; i < pl.numpuzzles; i++) // Prints List
	{
		cout << 1 + i << ".  " << pl.puzzles[i]->name << " with a maximum number of " << pl.puzzles[i]->attempts << " movement(s)" << endl;
	}

	//Also displays the 0, -1 and -2 options of the assignment
	cout << "0.  Exit" << endl;
	cout << "-1. Show the list ordered from highest to lowest" << endl;
	cout << "-2. Show the list ordered from lowest to highest" << endl;

	cout << endl;


}
void sortIncreasing(tPuzzlesList& pl) // sort a list of puzzles in increasing order.
{
	for (int i = 0; i < pl.numpuzzles - 1; i++)
	{
		int lowest = i;
		for (int j = i + 1; j < pl.numpuzzles; j++)
		{
			/*if (lessThan(*pl.puzzles[j], *pl.puzzles[lowest]))*/
			if (*pl.puzzles[j] < *pl.puzzles[lowest])
			{
				lowest = j;
			}
		}
		if (lowest > i)
		{
			tPtrPuz tmp;
			tmp = pl.puzzles[i];
			pl.puzzles[i] = pl.puzzles[lowest];
			pl.puzzles[lowest] = tmp;
		}

	}

}

void sortDecreasing(tPuzzlesList& pl) // sorts a list of puzzles in decreasing order.
{
	for (int i = 0; i < pl.numpuzzles - 1; i++)
	{
		int biggest = i;
		for (int j = i + 1; j < pl.numpuzzles; j++)
		{
			if (*pl.puzzles[j] > *pl.puzzles[biggest])

			{
				biggest = j;
			}
		}
		if (biggest > i)
		{
			tPtrPuz tmp;
			tmp = pl.puzzles[i];
			pl.puzzles[i] = pl.puzzles[biggest];
			pl.puzzles[biggest] = tmp;
		}
	}
}

bool sortedInsert(tPuzzlesList& pl, tPuzzle* p) // Inserts a new puzzle in the list of puzzles in order
{
	bool ok = false;
	int pos = 0;

	if (pl.numpuzzles < MAX_PUZZLES) // Check if the counter of the list is equal to MAX_PUZZLES
	{
		// Call the find function 

		if (!find(pl, p, pos))
		{
			ok = true;
			pl.numpuzzles++; // One more puzzle
			for (int i = pl.numpuzzles - 1; i > pos; i--) // Shift and insert
			{
				pl.puzzles[i] = pl.puzzles[i - 1];
			}
			pl.puzzles[pos] = p;
		}
	}
	if (ok)
	{
		cout << endl;
		cout << "Puzzle added to the list" << endl;
	}
	else
	{
		cout << endl;
		cout << "Something went wrong. Puzzle not added" << endl;
	}

	return ok;
}

bool find(const tPuzzlesList& pl, tPuzzle* p, int& pos) //  Binary search
{
	int beg = 0, end = pl.numpuzzles - 1, middle;
	bool found = false;

	while ((beg <= end) && !found)
	{
		middle = (beg + end) / 2; // Integer division
		if (*p == *pl.puzzles[middle])
		{
			found = true;
		}
		if (*p < *pl.puzzles[middle])
		{
			end = middle - 1;
		}
		else {
			beg = middle + 1;
		}
	}

	if (found)
	{
		pos = middle;
	}
	else // If the puzzle is not found 
	{
		pos = beg; // Return INI as a pos
	}

	return found;
}

void freeMem(tGatheredPuzzles& gp) // Returns all the  dynamic memory used to the heap and puts counters to 0
{
	for (int i = 0; i < gp[0].numpuzzles; i++)
	{
		delete gp[0].puzzles[i];
	}

	for (int i = 0; i < gp[1].numpuzzles; i++)
	{
		delete gp[1].puzzles[i];
	}

	gp[0].numpuzzles = 0;
	gp[1].numpuzzles = 0;
}



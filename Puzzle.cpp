//Daniel Martín & Laura San Martín

#include <string>
#include "Puzzle.h"
using namespace std;

void mainPuzzle(tPuzzle& pm)  // Function that solves a puzzle
{
	load(pm, pm.GameMode);
	if (play(pm)) // Returns true when the initial and the objective matrix are equal
	{
		cout << endl;
		cout << "Congratulations! You've won :) " << endl;
		cout << endl;
	}
}
bool load(tPuzzle& pm, tGameMode type) // Opens the corresponding file and calls the load function of the Matrix module
{	bool loaded = false;
	ifstream file;

	file.open(pm.file); // The name of the file is already loaded 

	if (file.is_open())
	{
		loaded = loadMatrix(pm.initialMatrix, file); // Loading the initial matrix
		loaded = loadMatrix(pm.objetiveMatrix, file); // Loading the onjective matrix

		file >> pm.attempts; // Reading the attempts
		file.close();
	}
	else
	{
		cout << "Error opening the file!" << endl; // Not loaded
	}

	return loaded;
}
void show(const tPuzzle& pm) // Displays the matrices
{
	showOne(pm.initialMatrix); // Shows the initial puzzle
	cout << endl;
		
	showOne(pm.objetiveMatrix); // Shows the objective puzzle
	cout << endl;
	cout << "Attempt(s): " << pm.attempts << endl; // Shows the number of attempts for the corresponding puzzle
	cout << endl;

}

void showOne(tMatrixChar matrix) // Shows one matrix
{
	for (int i = 0; i < matrix.columns; i++) // Show the column numbers with setw(2)
	{
		if (i == 0)
		{
			cout << " ";
		}
		cout << setw(2); // print TWO spaces
		cout << left << i;
	}
	cout << endl;

	for (int i = 0; i < matrix.rows; i++)
	{
		cout << setw(2) << left << i;

		for (int j = 0; j < matrix.columns; j++)
		{
			colorCTA(15, int(matrix.matrix[i][j])- int('0')); // Sets the color
			cout << "  "; // print TWO spaces
		}
		colorCTA(15,0);
		cout << endl;
	}
}

bool play(tPuzzle& pm) // Allows the user to perform the actions necessary to play and controls whether the limit of allowed actions has been reached
{
	show(pm);
	bool win = false;
	int attempts = pm.attempts;
	tMatrixChar iniMatrix = pm.initialMatrix;


	while ((pm.attempts != 0) && (!win)) // While the user does not win and there are attempts left
	{

		if (action(pm))
		{
			pm.attempts--; // The attempts decrease

			if (operator==(pm.initialMatrix, pm.objetiveMatrix)) // Checks if the two matrices are equal
			{
				cout << endl;
				show(pm);
				win = true;
			}
			else // The user keeps trying
			{
				cout << endl;
				show(pm);
			}
		}
		else // The command typed is not valid
		{
			cout << endl;
			cout << endl;
			cout << "Try again" << endl;
			cout << endl;
			show(pm);
		}
	}
	if ((pm.attempts == 0) &&(!win)) // Start over
	{
		cout << endl;
		cout << "No attempts left. Try again!" << endl;
		cout << endl;
	}

	//The values have been modified
	pm.attempts = attempts;
	pm.initialMatrix = iniMatrix;

	return win;
}
bool action(tPuzzle& pm) // According to the action command typed by the user, it calls the corresponding action defined in the Matrix module
{
	bool ok = false;
	string action;
	int a, b;

	cout << "Action: ";
	cin >> action;

	if (pm.GameMode == OneDim) // If the game mode is OneDim
	{
		if (action == "RS")
		{
			cout << "First row: ";
			cin >> a;
			cout << "Second row: ";
			cin >> b;
			ok = swapR(pm.initialMatrix, a, b); // swap rows
		}

		else if (action == "CS")
		{
			cout << "First column: ";
			cin >> a;
			cout << "Second column: ";
			cin >> b;

			ok = swapC(pm.initialMatrix, a, b); // swap columns
		}
		else if (action == "DS")
		{
			cout << "Diagonal to swap: ";
			cin >> a;
			ok = swapD(pm.initialMatrix, a); // swap diagonal
		}
		else if (action == "FR")
		{
			cout << "Row to flip: ";
			cin >> a;
			ok = flipR(pm.initialMatrix, a); // flip row
		}
		else if (action == "CF")
		{
			cout << "Column to flip: ";
			cin >> a;
			ok = flipC(pm.initialMatrix, a); // flip column
		}
		else if (action == "DF")
		{
			cout << "Diagonal to flip: ";
			cin >> a;
			ok = flipD(pm.initialMatrix, a); // flip diagonal
		}
		else // If the action is not valid, warn the user
		{
			cout << endl;
			cout << "Not a valid action" << endl;
		}
	}
	else if (pm.GameMode == TwoDim) // If the game mode is TwoDim

	{
		if (action == "VF")
		{ 
			flipV(pm.initialMatrix); // vertical flip
			ok = true;
		}
		else if (action == "HF")
		{
			flipH(pm.initialMatrix); // horizontal flip
			ok = true;
		}
		else if (action == "RR")
		{
			rotateR(pm.initialMatrix); // rotate right
			ok = true;
		}
		else if (action == "NS") 
		{
			tCoor pos1, pos2;
			cout << "First row: ";
			cin >> pos1.row;
			cout << "First column: ";
			cin >> pos1.column;
			cout << "Second row: ";
			cin >> pos2.row;
			cout << "Second column: ";
			cin >> pos2.column;
			ok = swapAdj(pm.initialMatrix, pos1, pos2); // swap the neighbouring positions
		}
		else if (action == "DF")
		{
			ok = flipID(pm.initialMatrix);
		}
		else // If the action is not valid, warn the user
		{
			cout << endl;
			cout << "Not a valid action" << endl;
		}
	}

	return ok;

}

//Overloading the operators <, > and =


bool operator <(const tPuzzle& p1, const tPuzzle& p2) // less attempts than
{
	if (p1.attempts != p2.attempts)
		return p1.attempts < p2.attempts;
	else
		return p1.name < p2.name;
}
bool operator >(const tPuzzle& p1, const tPuzzle& p2) // more attempts than

{
	if (p1.attempts != p2.attempts)
		return p1.attempts > p2.attempts;
	else
		return p1.name > p2.name;
}
bool operator ==(const tPuzzle& p1, const tPuzzle& p2) // Same file name
{
	bool ok = false;

	if (p1.file == p2.file)
		ok = true;

	return ok;
}

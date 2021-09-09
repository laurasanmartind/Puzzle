//Daniel Martín & Laura San Martín
#include <string>
#include "Matrix.h"
using namespace std;

bool loadMatrix(tMatrixChar& mat, std::istream& file) // Loads one matrix
{
	bool end = false;
	int i = 0, j = 0;

	file >> mat.rows; //loads the number of rows
	file >> mat.columns; //loads the number of columns

	for (i = 0; i < mat.rows; i++)
	{
		for (j = 0; j < mat.columns; j++)
		{
			file >> mat.matrix[i][j];
		}
	}
	if ((i == mat.rows) && (j == mat.columns))
	{
		end = true;
	}

	return end;
}

bool operator==(tMatrixChar const& mat1, tMatrixChar const& mat2) // Checks if two matrices are equal
{
	bool equal = false; 
	bool stop1 = false; 
	bool stop2 = false;

	while ((!equal) && (!stop2))
	{
		for (int i = 0; i < mat1.rows; i++)
		{
			for (int j = 0; j < mat2.columns; j++)
			{
				if (mat1.matrix[i][j] == mat2.matrix[i][j])
				{
					stop1 = false; 
				}
				else // Stops checking the moment one value is different 
				{
					stop2 = true;
					i = DIM_MAX;
					j = DIM_MAX;
				}
			}
		}
		if (!stop2) // stop2 = true if the matrices are different
		{
			equal = true;
		}
	}
	return equal;
}
bool rangeRow(int row, tMatrixChar mat) // Checks if a row is in the range of a matrix
{
	bool ok = true;
	if (row > mat.rows)
	{
		ok = false;
	}
	return ok;
}
bool rangeCol(int col, tMatrixChar mat) // Checks if a row is in the range of a matrix
{
	bool ok = true;
	if (col > mat.columns)
	{
		ok = false;
	}
	return ok;
}
bool range(tCoor coor, tMatrixChar mat) // Checks if a row and a column is in the range of a matrix
{
	bool ok = true;
	if ((coor.column > mat.columns) || (coor.row > mat.rows))
	{
		ok = false;
	}
	return ok;
}

bool swap(tMatrixChar& mat, tCoor pos1, tCoor pos2) // Swaps two coordinates
{
	bool ok = false;
	int aux;

	if ((range(pos1, mat)) && (range(pos2, mat)))
	{
		ok = true;
		aux = mat.matrix[pos1.row][pos1.column]; //Saves the first coordinate in aux
		mat.matrix[pos1.row][pos1.column] = mat.matrix[pos2.row][pos2.column];
		mat.matrix[pos2.row][pos2.column] = aux; //Rewrites the coordinate saved in aux
	}

	return ok;
}

bool swapR(tMatrixChar& mat, int r1, int r2) // Swaps two rows
{
	bool ok = false;
	int max = mat.columns;
	typedef int tRow[DIM_MAX];
	tRow aux;

	if ((rangeRow(r1, mat)) && (rangeRow(r2, mat))) // range must be the same
	{
		ok = true;
		for (int i = 0; i < mat.columns; i++)
		{
			aux[i] = mat.matrix[r2][i];
			mat.matrix[r2][i] = mat.matrix[r1][i];
			mat.matrix[r1][i] = aux[i];
		}
	}

	return ok;
}

bool swapC(tMatrixChar& mat, int c1, int c2) // Swaps two columns
{
	bool ok = false;
	int max = mat.rows;
	typedef int tRow[DIM_MAX];
	tRow aux;

	if ((rangeCol(c1, mat)) && (rangeCol(c2, mat))) // range must be the same
	{
		ok = true;
		for (int i = 0; i < mat.rows; i++)
		{
			aux[i] = mat.matrix[i][c2];
			mat.matrix[i][c2] = mat.matrix[i][c1];
			mat.matrix[i][c1] = aux[i];
		}
	}

	return ok;
}

bool swapD(tMatrixChar& mat, int d) // Swaps two diagonals
{
	bool ok = false;
	typedef int tDiagonal[DIM_MAX];
	tDiagonal diagonal;
	int row = 0;

	if (mat.columns == mat.rows) // The matrix  has to be square
	{
		if (rangeRow(d, mat)) // The diagonal must be in the range
		{
			ok = true;

			for (int i = 0; i < mat.rows; i++)
			{
				diagonal[i] = mat.matrix[row][d]; // Auxiliar array for saving the matrix
				mat.matrix[row][d] = mat.matrix[d][row];
				mat.matrix[d][row] = diagonal[i];
				row++;
				d++;
			}
		}
	}
	return ok;
}

bool flipR(tMatrixChar& mat, int r) // Flips one row
{
	bool ok = false;
	int max = mat.columns / 2;
	int num = mat.columns - 1;
	typedef int tRow[DIM_MAX];
	tRow row;

	if (rangeRow(r, mat)) // The row must be in the range
	{
		ok = true;
		for (int i = 0, j = num; i < max; i++, j--)
		{
			row[i] = mat.matrix[r][i];
			mat.matrix[r][i] = mat.matrix[r][j];
			mat.matrix[r][j] = row[i];
		}
	}

	return ok;
}

bool flipC(tMatrixChar& mat, int c) // Flips one column
{
	bool ok = false;
	int max = mat.rows / 2;
	int num = mat.rows - 1;
	typedef int tCol[DIM_MAX];
	tCol column;

	if (rangeCol(c, mat)) // The column must be in the range
	{
		ok = true;
		for (int i = 0, j = num; i < max; i++, j--)
		{
			column[i] = mat.matrix[i][c];
			mat.matrix[i][c] = mat.matrix[j][c];
			mat.matrix[j][c] = column[i];
		}
	}

	return ok;
}

bool flipD(tMatrixChar& mat, int d) // Flips Diagonal
{
	bool ok = false;
	int POSmax = (mat.rows - d) / 2;
	int NEGmax = (mat.rows + d) / 2;
	int num = mat.rows - 1;
	typedef int tDiag[DIM_MAX];
	tDiag diagonal;

	if (mat.columns == mat.rows) // The matrix  has to be square
	{
		if (rangeRow(d, mat))
		{
			if (d >= 0) // If the diagonal is positive 
			{
				for (int i = 0, j = num; i < POSmax; i++, j--)
				{
					ok = true;
					diagonal[i] = mat.matrix[i][d];
					mat.matrix[i][d] = mat.matrix[j - d + i][j];
					mat.matrix[j - d + i][j] = diagonal[i];
					d++;
				}
			}
			else if (d < 0) // If the diagonal is negative
			{
				for (int i = 0, j = num; i < NEGmax; i++, j--)
				{
					ok = true;
					diagonal[i] = mat.matrix[-d][i];
					mat.matrix[-d][i] = mat.matrix[j][j + d + i];
					mat.matrix[j][j + d + i] = diagonal[i];
					-d++;
				}
			}
		}
	}

	return ok;
}

void flipV(tMatrixChar& mat) // Flips the entire image around its central vertical axis
{
	for (int i = 0; i < (mat.columns / 2); i++)
	{
		swapC(mat, i, mat.columns - 1 - i);
	}
}

void flipH(tMatrixChar& mat) // Flips the entire image around its central horizontal axis
{
	for (int i = 0; i < mat.rows / 2; i++)
	{
		swapR(mat, i, mat.rows - 1 - i);
	}
}

void rotateR(tMatrixChar& mat) // Rotates an image 90 degrees clockwise
{
	tMatrixChar aux = mat;
	mat.rows = aux.columns;
	mat.columns = aux.rows;
	for (int i = 0; i < aux.rows; i++)
	{
		for (int j = 0; j < aux.columns; j++)
		{
			mat.matrix[j][aux.rows - i - 1] = aux.matrix[i][j];
		}
	}
}
bool swapAdj(tMatrixChar& mat, tCoor pos1, tCoor pos2) // Swaps neighboring or adjacent cells of positions pos1 and pos2
{
	int position1, position2;
	bool ok = false;

	int max = 3;
	typedef int tRow[3];
	tRow aux;

	//Save the centers
	position1 = mat.matrix[pos1.row][pos1.column];
	position2 = mat.matrix[pos2.row][pos2.column];

	if ((range(pos1, mat)) && (range(pos2, mat))) // Matrix has to be square
	{
		if ((pos1.row != 0 || pos1.row != mat.rows - 1) || (pos1.column != 0 || pos1.column != mat.columns - 1) || (pos2.row != 0 || pos2.row != mat.rows - 1) || (pos2.column != 0 || pos2.column != mat.columns - 1)) // Neighbors in the range
		{
			if ((pos1.row - pos2.row >= 3) || (pos2.row - pos1.row >= 3)) // No overlap
			{
				ok = true;

				for (int i = 0; i < max; i++)
				{
					for (int j = 0; j < max; j++)
					{
						aux[i] = mat.matrix[pos2.row - 1 + i][pos2.column - 1 + j];
						mat.matrix[pos2.row - 1 + i][pos2.column - 1 + j] = mat.matrix[pos1.row - 1 + i][pos1.column - 1 + j];
						mat.matrix[pos1.row - 1 + i][pos1.column - 1 + j] = aux[i];
					}
				}
				// Writes the centers again
				mat.matrix[pos1.row][pos1.column] = position1;
				mat.matrix[pos2.row][pos2.column] = position2;
			}
		}
	}

	return ok;
}

bool flipID(tMatrixChar& mat) // Flips the entire image relative to the main diagonal
{
	bool ok = false;

	if (mat.rows == mat.columns) // Square matrix
	{
		ok = true;

		for (int i = 0; i < mat.rows; i++)
		{
			swapD(mat, i);
		}
	}
	return ok;
}

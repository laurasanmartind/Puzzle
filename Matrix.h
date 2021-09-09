//Daniel Martín & Laura San Martín
#ifndef MATRIX_H
#define MATRIX_H

#include "Coordinates.h"
#include "UtilitiesSYS.h"
#include <string>
#include <fstream>
using namespace std;


const int DIM_MAX = 64;

typedef uint8 tMatrix[DIM_MAX][DIM_MAX];

struct tMatrixChar
{
	int rows = 0;
	int columns = 0;
	tMatrix matrix;
};

bool loadMatrix(tMatrixChar& mat, std::istream& file); // Loads one matrix
bool operator== (tMatrixChar const& mat1, tMatrixChar const& mat2); // Checks if two matrices are equal
bool swap(tMatrixChar& mat, tCoor pos1, tCoor pos2); // Swaps two coordinates
bool swapR(tMatrixChar& mat, int r1, int r2); // Swaps two rows
bool swapC(tMatrixChar& mat, int c1, int c2); // Swaps two columns
bool swapD(tMatrixChar& mat, int d); // Swaps two diagonals
bool flipR(tMatrixChar& mat, int r); // Flips one row
bool flipC(tMatrixChar& mat, int c); // Flips one column
bool flipD(tMatrixChar& mat, int d); // Flips Diagonal
void flipV(tMatrixChar& mat); // Flips the entire image around its central vertical axis
void flipH(tMatrixChar& mat); // Flips the entire image around its central horizontal axis
void rotateR(tMatrixChar& mat);  // Rotates an image 90 degrees clockwise
bool swapAdj(tMatrixChar& mat, tCoor pos1, tCoor pos2);  // Swaps neighboring or adjacent cells of positions pos1 and pos2
bool flipID(tMatrixChar& mat); // Flips the entire image relative to the main diagonal
bool rangeRow(int row, tMatrixChar mat); // Checks if a row is in the range of a matrix
bool rangeCol(int col, tMatrixChar mat); // Checks if a row is in the range of a matrix
bool range(tCoor coor, tMatrixChar mat); // Checks if a row and a column is in the range of a matrix

#endif

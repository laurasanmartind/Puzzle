//Daniel Martín & Laura San Martín
#include "Coordinates.h"
#include <string>
using namespace std;

bool operator== (tCoor c1, tCoor c2) // Compares if two coordinates are equal
{
    bool equal = false;
    if ((c1.column == c2.column) && (c1.row == c1.row))
    {
        equal = true;
    }
    return equal;
}

bool operator!= (tCoor c1, tCoor c2) // Compares if two coordinates are different
{
    bool notEqual = false;
    if ((c1.column != c2.column) && (c1.row != c2.row))
    {
        notEqual = true;
    }
    return notEqual;
}

tCoor operator+ (tCoor c1, tCoor c2) // Returns the coordinate resulting from adding the two coordinates given by parameters
{
    tCoor c3;

    c3.row = c1.row + c2.row;
    c3.column = c1.column + c2.column;

    return c3;
}
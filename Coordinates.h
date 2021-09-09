//Daniel Martín & Laura San Martín
#ifndef COORDINATES_H
#define COORDINATES_H

#include <string>
using namespace std;

struct tCoor
{
    int row = 0;
    int column = 0;
};

bool operator== (tCoor c1, tCoor c2); // Compares if two coordinates are equal
bool operator!= (tCoor c1, tCoor c2); // Compares if two coordinates are different
tCoor operator+ (tCoor c1, tCoor c2); // Returns the coordinate resulting from adding the two coordinates given by parameters



#endif


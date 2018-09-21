/* 
 * File:   rect.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 1, 2018, 5:18 PM
 */

#ifndef RECT_H
#define RECT_H

#include <vector>
#include <string>

using namespace std;

class rectangle {
public:
    /* Initailized with two corners, represented as vector with size 2,
     * and a boolean, to indicate if the rectangle is inverted. */
    rectangle (vector < int > c1, vector < int > c2, bool inverted);
    /* Returns true if the point is in the rectangle, false otherwise. */
    bool contains (vector < float > pt);
    /* Returns a string representation of the rectangle that can be 
     * printed. */
    string draw (int k);
private:
    /* Left most x coordinate. */
    int left;
    /* Right most x coordinate. */
    int right;
    /* Bottom most y coordinate. */
    int bottom;
    /* Top most y coordinate. */
    int top;
    /* Boolean indicating if the rectangle is inverted. */
    bool inv;
    /* Boolean indicating if y1 < y2. */
    bool climbs;
};

#endif /* RECT_H */


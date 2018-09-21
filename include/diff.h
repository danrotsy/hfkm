/* 
 * File:   diff.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 20, 2018, 7:00 PM
 */

#ifndef DIFF_H
#define DIFF_H

#include <vector>
#include "rect.h"
#include "cgen.h"
#include "cgrp.h"
#include "grid.h"

using namespace std;

class diff {
public:
    /* Constructs a Heegaard Floer differential using a grid diagram, and two 
     * chain groups (i.e. the domain and range). */
    diff (grid g, cgrp dom, cgrp ran);
    /* Returns the differential as a 2D vector. */
    vector < vector < bool > > get_d () const;
private:
    /* Alexander grading of the differential. */
    int a;
    /* Maslov grading of the differential. */
    int m;
    /* Returns true if there is a differential flow between x and y, and
     * false otherwise. */
    bool d (grid g, cgen x, cgen y);
    /* Returns true if the rectangle connects x and y, and false otherwise. */
    bool is_valid (grid g, rectangle r, cgen x, cgen y);
    /* The differential, stored as a 2D vector of booleans. */
    vector< vector < bool > > d_mat;
};

#endif /* DIFF_H */


/* 
 * File:   diff.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 20, 2018, 7:00 PM
 */

#ifndef DIFF_H
#define DIFF_H

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <NTL/mat_GF2.h>
#include "rect.h"
#include "expsni.h"
#include "cgen.h"
#include "cgrp.h"
#include "grid.h"

using namespace std;
using namespace NTL;

class diff {
public:
    /* Constructs a Heegaard Floer differential using a grid diagram, and two 
     * chain groups (i.e. the domain and range). */
    diff (grid g, cgrp dom, cgrp ran);
    /* Returns the differential as a 2D vector. */
    Mat < GF2 > get_D () const;
private:
    /* Alexander grading of the differential. */
    int a;
    /* Maslov grading of the differential. */
    int m;
    /* The differential, stored as boolean NTL matrix. */
    Mat < GF2 > D;
    /* i to n_i hash. */
    unordered_map < int, vector < vector < int > > > ui_hash;
    /* Returns true if the rectangle connects x and y, and false otherwise. */
    bool is_valid (grid g, rectangle r, cgen x, cgen y);
    /* Finds the scalar U_1^n_1 ... U_k^n_k corresponding to a rectangle r on 
     * a grid g. */
    vector < int > get_rect_olst (grid g, rectangle r);
    /* Updates ui_hash to account for degree deg. Does nothing if deg hash is
     * already stored. */
    void update (grid g, int deg);
    /* Edits the block of D corresponding to (x, y). */
    void gen_block (grid g, cgen x, cgen y, vector < int > olst);
};

#endif /* DIFF_H */

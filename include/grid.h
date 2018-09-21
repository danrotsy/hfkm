/* 
 * File:   grid.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 1, 2018, 11:12 AM
 */

#ifndef GRID_H
#define GRID_H
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <boost/progress.hpp>
#include "jta.h"
#include "rect.h"
#include "gridgen.h"
#include "gridio.h"

using namespace std;

/* Used to calculate all the Alexander and Maslov gradings of a grid. */
class grid {
public:
    /* Instantiates grid, finds the knot path, and alexander shift.
     * vector < int > x_in: the permutation corresponding to positions 
     *      of {x_i}.
     * vector < int > o_in: the permutation corresponding to positions 
     *      of {o_i}. */
    grid (vector < int > x_in, vector < int > o_in);
    /* Returns the grid diagram as a string, printable in the terminal. */
    string to_str ();
    /* Finds the next n gens of grid, using info specified in directory 
     * dir. */
    void find_gens (string dir, int n);
    /* Prints all gens found to the terminal. */
    void print_gens ();
    /* Sorts and saves all generators in grid::grid_gens in directory dir. */
    void save_gens (string dir);
    /* Returns grid size. */
    int get_k () const;
    /* Returns the two rectangles between two permutations corresponding to 
     * generators on the grid, if they exist. */
    vector < rectangle > get_rectangles (vector < int > p1, 
        vector < int > p2);
    /* Computes the weighted sum (times four) of a point on a rectangle, used
     * to find the Maslov index of a rectangle using Lipshitz' rules. 
     * Guaranteed to be an integer. */
    int p_x4 (vector < int > p, rectangle r);
    /* Finds the intersection number of a rectangle with o_i on the 
     * diagram. */
    int n_o (int i, rectangle r);
    /* Finds sum of all intersection numbers of a rectangle over all o_i on
     * the diagram. */
    int o_ct (rectangle r); 
private:
    /* Grid size. */
    int k;
    /* List/permutation corresponding to the positions of {x_i}. */
    vector < int > x;
    /* List/permutation corresponding to the positions of {o_i}. */
    vector < int > o;
    /* List of all generators whose Alexander and Maslov gradings computed in 
     * the current instance. */
    vector < gridgen > grid_gens;
    /* An ordered list of points on the grid, representing the knot path on
     * the grid diagram. */
    vector < vector < float > > path;
    /* The mathematical constant, pi. */
    double pi;
    /* The shift in Alexander grading, added to the sum of the winding
     * numbers of a given generator to find the overall grading. */
    int a_shift;
    /* Finds the winding number of a point on the grid relative to the knot
     * path, times negative one. */
    int w (vector < int > pt);
    /* Returns the Alexander grading of a generator with a given jtp. */
    int calc_a (jtp j);
    /* Returns the Maslov grading of a generator with a given jtp. */
    int calc_m (jtp j);
};

#endif /* GRID_H */


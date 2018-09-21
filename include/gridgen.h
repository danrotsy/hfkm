/* 
 * File:   gridgen.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 1, 2018, 10:37 AM
 */

#ifndef GRIDGEN_H
#define GRIDGEN_H

#include <vector>

using namespace std;

/* Used to store grid generators, without coefficients in F[U_1, U_k]. */
class gridgen {
public:
    /* Initializes gridgen with a given permutations. */
    gridgen (vector < int > p_in);
    /* Returns the permutation. */
    vector < int > get_p () const;
    /* Returns the Alexander grading. */
    int get_a () const;
    /* Returns the Maslov grading. */
    int get_m () const;
    /* Sets the Alexander grading. */
    void set_a (int a_new);
    /* Sets the Maslov grading. */
    void set_m (int m_new);
private:
    /* Grid permutation. */
    vector < int > p;
    /* Alexander grading. */
    int a;
    /* Maslov grading. */
    int m;
};

#endif /* GRIDGEN_H */

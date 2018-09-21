/* 
 * File:   hom.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 24, 2018, 4:46 AM
 */

#ifndef HOM_H
#define HOM_H

#include <iostream>
#include <vector>
#include <string>
#include "cgen.h"
#include "jta.h"

using namespace std;

/* Used to store grid generators, with coefficients in F[U]. */
class hgen {
public:
    /* Initializes cgen with a given permutations. */
    hgen (cgen c);
    /* Returns the permutation. */
    vector < int > get_p () const;
    /* Returns the exponents of each U_i. */
    int get_n () const;
    /* Returns U_1^n_1 ... U_k^n_k (p) as a string. */
    string tos (); 
    /* Returns true if p and n_i are the same. */
    bool equals (hgen b);
private:
    /* Grid permutation. */
    vector < int > p;
    /* Exponent of U. */
    int n;
};

/* Used to store sums of hgens, in the resulting homology. */
class hvec {
public:
    /* Initializer. */
    hvec (vector < cgen > cgv_in);
    /* Returns a printable string. */
    string tos ();
    /* Evaluates if two hvecs are equal. */
    bool equals (hvec b);
    /* Returns the vector hgv. */
    vector < hgen > get_v () const;
private:
    /* The list of generators. */
    vector < hgen > v;
    /* Evaluates whether hgen g is in hgv. */
    bool is_in (hgen hg);
};

#endif /* HOM_H */

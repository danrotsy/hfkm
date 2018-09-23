/* 
 * File:   cgen.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 20, 2018, 7:33 PM
 */

#ifndef CGEN_H
#define CGEN_H

#include <vector>
#include <string>
#include "jta.h"

using namespace std;

/* Used to store grid generators, with coefficients in F[U_1, U_k]. */
class cgen {
public:
    /* Initializes cgen with a given permutations. */
    cgen (vector < int > p_in);
    /* Returns the permutation. */
    vector < int > get_p () const;
    /* Returns the Alexander grading. */
    int get_a () const;
    /* Returns the Maslov grading. */
    int get_m () const;
    /* Returns the index of the hash to use for n_i conversion. */
    int get_deg_diff () const;
    /* Returns the index of the generator in the matrix d_mat. */
    int get_D_index () const;
    /* Returns the exponents of each U_i. */
    vector < int > get_n_i () const;
    /* Sets the Alexander grading. */
    void set_a (int a_new);
    /* Sets the Maslov grading. */
    void set_m (int m_new);
    /* Sets the index of the hash for n_i conversion. */
    void set_deg_diff (int deg_diff_new);
    /* Sets the index of the generator in the matrix d_mat. */
    void set_D_index (int d_mat_index_new);
    /* Sets the exponents of each U_i. */
    void set_n_i (vector < int > n_i_new);
    /* Returns U_1^n_1 ... U_k^n_k (p) as a string. */
    string tos (); 
    /* Returns true if p and n_i are the same. */
    bool operator == (cgen &b);
private:
    /* Grid permutation. */
    vector < int > p;
    /* Alexander grading. */
    int a;
    /* Maslov grading. */
    int m;
    /* Exponents of each U_i. */
    vector < int > n_i;
    /* The index of the hash for n_i conversion. */
    int deg_diff;
    /* The index of the generator in the matrix d_mat */
    int D_index;
};

#endif /* CGEN_H */

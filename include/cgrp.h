/* 
 * File:   cgrp.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 20, 2018, 6:56 PM
 */

#ifndef CGRP_H
#define CGRP_H

#include <string>
#include <vector>
#include <cmath>
#include "gridio.h"
#include "cgen.h"
#include "expsni.h"

using namespace std;

class cgrp {
public:
    /* Finds all basis elements of C^-(a, m) for a grid of size k, using
     * generators specified in a given directory. */
    cgrp (int a_in, int m_in, string dir_in, int k_in);
    /* Returns the base gens of C^-(a, m). */
    vector < cgen > get_base_gens () const;
    /* Returns the basis of C^-(a, m). */
    vector < cgen > get_basis () const;
    /* Returns dimension of cgrp. */
    int dim () const;
    /* Returns the ith basis element. */
    cgen get_x (int i) const;
    /* Returns Alexander grading. */
    int get_a () const;
    /* Returns Maslov grading. */
    int get_m () const;
private:
    /* Alexander grading of C^-(a, m). */
    int a;
    /* Maslov grading of C^-(a, m). */
    int m;
    /* Directory from which generators are found. */
    string dir;
    /* Grid size. */
    int k;
    /* The basis of C^-(a, m). */
    vector < cgen > basis;
    /* The generators of C^-(a, m) independent of U_i. */
    vector < cgen > base_gens;
    /* Finds all generators (with coefficients in F[U_1, ..., U_n]) given the
     * difference in Alexander grading. */
    void add_all_relevant_gens_to_basis (int da);
};

#endif /* CGRP_H */


/* 
 * File:   expsni.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 21, 2018, 9:33 PM
 */

#ifndef EXPSNI_H
#define EXPSNI_H

#include <vector>
#include <algorithm>

using namespace std;

/* Computes the binomial nCk. */
vector < vector < int > > combinations (int n, int k);

/* Finds all monomials of degree deg in k variables. */
vector < vector < int > > all_ni (int k, int deg);

#endif /* EXPSNI_H */


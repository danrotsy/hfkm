/* 
 * File:   jta.h
 * Author: Daniel Rostovtsev
 *
 * Created on August 1, 2018, 2:14 PM
 */

#ifndef JTA_H
#define JTA_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

/* Calculates n!. */
int factorial (int n);

/* Converts an integer (corresponding to a factoradic index) to a 
 * permutation. */
vector < int > itop (int n, int k);

/* Converts a permutation to its corresponding factoradic permutation. */
int ptoi (vector < int > p, int k);

/* Converts a permutation to its corresponding factoradic index. */
string ptos (vector < int > p);

/* Used to store information relevant for the Johnson-Trotter algorithm, and
 * the calculation of Alexander and Maslov indices in grid.cpp. */
class jtp {
public:
    /* Instantiation of jtp class. 
     * val_in: { {x_0, dir0}, ... , {x_k-1, dir_k-1} }
     * o_in: {o_0, ... , o_k-1} */
    jtp (vector < vector < int > > val_in, vector < int > o_in);
    /* Returns the index of jtp in the Johnson-Trotter algorithm relative to 
     * o. */
    int get_i () const;
    /* Returns the permutation of jtp relative to o. */
    vector < int > get_p () const;
    /* Returns the val of jtp { {x_0, dir0}, ... , {x_k-1, dir_k-1} }. */
    vector < vector < int > > get_val () const;
    /* Returns the Maslov index of the previous jtp, if it exists, otherwise
     * ABORTS. Only call if jtp.get_p() != o or jtp.get_i() != 0. */
    int get_m_prev () const;
    /* Returns the previous val, if it exists, otherwise, ABORTS. Only call if
     * jtp.get_p() != 0, or jtp.get_i() != 0. */
    vector < vector < int > > get_val_prev () const;
    /* Returns the boolean m_prev_set. */
    bool get_m_prev_set () const;
    /* Returns the previous permutation, specified by val_prev. */
    vector < int > get_p_prev () const;
    /* Setter for m_prev, the Maslov index of the previous jtp. */
    void set_m_prev (int m_prev_in);
    /* Setter for val_prev, or {{x_0, dir0}, ... , {x_k-1, dir_k-1}} of the
     * previous jtp. */
    void set_val_prev (vector < vector < int > > val_prev_in);
    /* Returns a string representation of jtp: "(x_0, dir_0)...
     * (x_k-1, dir_k-1)". */
    string tos ();
    /* Returns the val of the next jtp, using the Johnson-Trotter 
     * algorithm. */
    vector< vector < int > > next () const;
private:
    /* o.size(), or, equivalently, grid size.  */
    int k;
    /* o's on the grid, in the form { o_0, ..., o_k-1 }. */
    vector < int > o;
    /* Value of the jtp, independent from o: {{x0, dir0} , ... {xk, dirk}}. */
    vector< vector < int > > val;
    /* Maslov index of the previous jtp, used when needed in grid, only
     * sometimes defined. */
    int m_prev;
    /* Value of the previous jtp, used when needed in grid, only sometimes
     * defined. */
    vector< vector < int > > val_prev;
    /* Indicator of whether m_prev has been set, used in jtp::get_m_prev(). */
    bool m_prev_set;
    /* Indicator of whether val_prev has been set, used in 
     * jtp::get_val_prev(). */
    bool val_prev_set;
};

/* Returns the first jtp in the Johnson-Trotter algorithm, permuted by o. */
jtp jtp0 (vector < int > o);

/* Used to find elements in lists, outdated by lambda functions in c++11. */
struct Is_Int {
    Is_Int( int i ) : toFind(i) { }
    bool operator() (const int &n)
        { return n == toFind; }
    int toFind;
};

#endif /* JTA_H */


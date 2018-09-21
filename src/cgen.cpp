/* 
 * File:   cgen.cpp
 * Author: Daniel Rostovtsev
 * 
 * Created on August 1, 2018, 7:33 PM
 */

#include "cgen.h"

cgen::cgen (vector < int > p_in) { 
    p = p_in;
    int k = p_in.size();
    for (int i = 0; i < k; i++) { /* defaults all exponents to zero */
        n_i.push_back(0);
    }
}

vector < int > cgen::get_p () const { return p; }

int cgen::get_a () const { return a; }

int cgen::get_m () const { return m; }

vector < int > cgen::get_n_i () const { return n_i; }

void cgen::set_a (int a_new) { a = a_new; }

void cgen::set_m (int m_new) { m = m_new; }

void cgen::set_n_i (vector < int > n_i_new) { n_i = n_i_new; }

string cgen::tos () {
    string out = "";
    int k = p.size();
    for (int i = 0; i < k; i++) {
        if (n_i[i] != 0) {
            out += ("U_" + to_string(i) + "^" + to_string(n_i[i]) + " ");
        }
    }
    out += ptos(p);
    return out;
}

bool cgen::operator == (cgen &b) {
    if ((p == b.get_p()) and (n_i == b.get_n_i())) {
        return true;
    } else {
        return false;
    }
}

/* 
 * File:   diff.cpp
 * Author: Daniel Rostovtsev
 * 
 * Created on August 20, 2018, 7:00 PM 
 */

#include "diff.h"

diff::diff (grid g, cgrp dom, cgrp ran) {
    a = dom.get_a();
    m = dom.get_m();
    int cols = dom.dim();
    int rows = ran.dim();
    if ((cols != 0) and (rows != 0)) {
        vector < bool > tmp(cols);
        int cap = cols * rows;
        clock_t t0 = clock();
        boost::progress_display d_progress(cap);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                tmp[j] = d(g, dom.get_x(j), ran.get_x(i));
                ++d_progress;
            }
            d_mat.push_back(tmp);
        }
        clock_t t1 = clock();
        clock_t dt = t1 - t0;
        cout << "Time elapsed: " << to_string( dt / (double) CLOCKS_PER_SEC) 
            << "s\n";
    } else if ((cols == 0) and (rows != 0)) {
        for (int i = 0; i < rows; i++) {
            vector < bool > tmp; tmp.push_back(0);
            d_mat.push_back(tmp);
        }
    } else if ((cols != 0) and (rows == 0)) {
        vector < bool > tmp;
        for (int i = 0; i < cols; i++) {
            tmp.push_back(0);
        }
        d_mat.push_back(tmp);
    } else {
        vector < bool > tmp;
        tmp.push_back(0);
        d_mat.push_back(tmp);
    }
}

bool diff::d (grid g, cgen x, cgen y) {
    vector < rectangle > rxy = g.get_rectangles(x.get_p(), y.get_p());
    if (rxy.size() == 0) { return false; }
    /* Now we know that there must be two rectangles, exactly. */
    return (is_valid(g, rxy[0], x, y) != is_valid(g, rxy[1], x, y));
}

bool diff::is_valid (grid g, rectangle r, cgen x, cgen y) {
    /* Maslov Grading 1. */
    if ((g.p_x4(x.get_p(), r) + g.p_x4(y.get_p(), r)) != 4) {
        return false;
    }
    /* Difference in exponents is correct. (FROM x TO y !!!) */
    for (int i = 0; i < g.get_k(); i++) {
        if (y.get_n_i()[i] - x.get_n_i()[i] != g.n_o(i, r)) {
            return false;
        }
    }
    return true;
}

vector< vector < bool > > diff::get_d () const { return d_mat; }

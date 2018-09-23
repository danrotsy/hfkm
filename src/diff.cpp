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
        D.SetDims(rows, cols);
        clock_t t0 = clock();
        /* Collecting all base generators from domain and range. */
        vector < cgen > dom_base_gens = dom.get_base_gens();
        vector < cgen > ran_base_gens = ran.get_base_gens();
        int num_dom_base_gens = dom_base_gens.size();
        int num_ran_base_gens = ran_base_gens.size();
        /* Starting progress bar. */
        int cap = num_dom_base_gens * num_ran_base_gens;
        boost::progress_display d_progress(cap);
        /* Editing D block by block, where each block corresponds to (x, y). */
        for (int i = 0; i < num_dom_base_gens; i++) {
            for (int j = 0; j < num_ran_base_gens; j++) {
                /* Get rectangles between x and y. */
                cgen x = dom_base_gens[i];
                cgen y = ran_base_gens[j];
                vector < rectangle > rxy = g.get_rectangles(x.get_p(),
                        y.get_p());
                if (rxy.size() != 0) { /* If rectangles exist: */
                    rectangle r1 = rxy[0]; rectangle r2 = rxy[1];
                    bool r1valid = is_valid(g, r1, x, y);
                    bool r2valid = is_valid(g, r2, x, y);
                    /* ... and only one rectangle is valid: */
                    if (r1valid != r2valid) {
                        /* Find intersection points of valid rectangle: */
                        vector < int > olst;
                        if (r1valid) {
                            olst = get_rect_olst(g, r1);
                        } else { /* (If r2valid.) */
                            olst = get_rect_olst(g, r2);
                        }
                        /* Edit block corresponding to (x, y). */
                        gen_block(g, x, y, olst); 
                    }
                }
                ++d_progress;
            }
        }
        clock_t t1 = clock();
        clock_t dt = t1 - t0;
        cout << "Time elapsed: " << to_string( dt / (double) CLOCKS_PER_SEC) 
            << "s\n";
    } else if ((cols == 0) and (rows != 0)) { 
        D.SetDims(rows, 1);
    } else if ((cols != 0) and (rows == 0)) {
        D.SetDims(1, cols);
    } else {
        D.SetDims(1, 1);
    }
}

Mat < GF2 > diff::get_D () const { return D; }

bool diff::is_valid (grid g, rectangle r, cgen x, cgen y) {
    /* Maslov Grading 1. */
    if ((g.p_x4(x.get_p(), r) + g.p_x4(y.get_p(), r)) != 4) {
        return false;
    }
    /* cout << "(DEBUGGING) x.a = " << to_string(x.get_a()) << 
        ", y.a = " << to_string(y.get_a()) << ", o_ct(r) = " <<
        to_string(g.o_ct(r)) << "\n"; */
    /* Intersection number is correct. */
    if (y.get_a() - x.get_a() != g.o_ct(r)) {
        return false;
    }
    /* If no problems, the rectange is valid. */
    return true;
}

vector < int > diff::get_rect_olst (grid g, rectangle r) {
    vector < int > olst (g.get_k());
    for (int i = 0; i < g.get_k(); i ++) {
        olst[i] = g.n_o(i, r);
    }
    return olst;
}

void diff::update (grid g, int deg) {
    try {
        ui_hash.at(deg);
    } catch (const out_of_range& e) {
        ui_hash[deg] = all_ni(g.get_k(), deg);
    }
    /* cout << "(DEBUGGING) Updated ui_hash at deg = " << 
       to_string(deg) << "\n"; */
}

void diff::gen_block (grid g, cgen x, cgen y, vector < int > olst) {
    /* First, update ni hashes, and find block width. */
    update(g, x.get_deg_diff());
    update(g, y.get_deg_diff());
    int n = ui_hash[x.get_deg_diff()].size();
    /* For each element in block domain: */
    for (int i = 0; i < n; i++) {
        vector < int > x_ni = ui_hash[x.get_deg_diff()][i];
        vector < int > y_ni (g.get_k());
        for (int j = 0; j < g.get_k(); j++) {
            y_ni[j] = x_ni[j] + olst[j];
        }
        vector < vector<int> >::iterator it = find(ui_hash[y.get_deg_diff()].begin(),
                ui_hash[y.get_deg_diff()].end(), y_ni);
        int j = distance(ui_hash[y.get_deg_diff()].begin(), it);
        D[y.get_D_index() + j][x.get_D_index() + i] = 1;
    }
}

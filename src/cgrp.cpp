/* 
 * File:   cgrp.cpp
 * Author: Daniel Rostovtsev
 * 
 * Created on August 20, 2018, 6:56 PM 
 */

#include "cgrp.h"

cgrp::cgrp (int a_in, int m_in, string dir_in, int k_in) {
    added = 0;
    a = a_in;
    m = m_in;
    dir = dir_in;
    k = k_in;
    vector< vector < int > > all_am = list_all_am(dir);
    int num_bigradings = all_am.size();
    for (int i = 0; i < num_bigradings; i++) {
        int a_file = all_am[i][0];
        int m_file = all_am[i][1];
        if (a <= a_file) {
            int da = a_file - a;
            if ((m_file - m) == (2 * da)) {
                add_all_relevant_gens_to_basis(da);
            }
        }
    }
}

vector < cgen > cgrp::get_base_gens () const { return base_gens; }

vector < cgen > cgrp::get_basis () const { return basis; }

int cgrp::dim () const { return basis.size(); }

cgen cgrp::get_x (int i) const { return basis[i]; }

int cgrp::get_a () const { return a; }

int cgrp::get_m () const { return m; } 

void cgrp::add_all_relevant_gens_to_basis (int da) {
    int a_add = a + da;
    int m_add = m + (2 * da);
    vector < cgen > base_gens_read = read_am(dir, a_add, m_add, k);
    int num_bg = base_gens_read.size();
    vector < vector < int > > exps = all_ni(k, da);
    int num_ni = exps.size();
    /* Read all base gens from file, and save D indices. */
    for (int i = 0; i < num_bg; i++) {
        cgen x = base_gens_read[i];
        x.set_D_index(added);
        x.set_deg_diff(da);
        x.set_a(a_add);
        x.set_m(m_add);
        added += num_ni;
        base_gens.push_back(x);
    }
    /* Save the rest of the generators. */
    for (int i = 0; i < num_bg; i++) {
        for (int j = 0; j < num_ni; j++) {
            vector < int > ni = exps[j];
            cgen g = cgen(base_gens_read[i].get_p());
            g.set_n_i(ni);
            basis.push_back(g);
        }
    }
}

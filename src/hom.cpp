/* 
 * File:   hom.cpp
 * Author: Daniel Rostovtsev
 * 
 * Created on August 24, 2018, 4:46 AM
 */

#include "hom.h"

hgen::hgen (cgen c) { 
    p = c.get_p();
    int k = p.size();
    n = 0;
    vector < int > n_i = c.get_n_i();
    for (int i = 0; i < k; i++) {
        n += n_i[i];
    }
}

vector < int > hgen::get_p () const { return p; }

int hgen::get_n() const { return n; }

string hgen::tos () {
    string out = "";
    int k = p.size();
    if (n == 1) {
        out += "U ";
    } else {
        out += ("U^" + to_string(n) + " ");
    }
    out += ptos(p);
    return out;
}

bool hgen::equals(hgen b) {
    if ((p == b.get_p()) and (n == b.get_n())) {
        return true;
    } else {
        return false;
    }
}

hvec::hvec (vector < cgen > cgv_in) {
    int cgv_sz = cgv_in.size();
    for (int i = 0; i < cgv_sz; i++) {
        hgen hg = hgen(cgv_in[i]);
        if (! is_in(hg)) {
            v.push_back(hg);
        }
    }
}

string hvec::tos() {
    string out = "";
    int sz = v.size();
    if (v.size() == 0) {
        return "0";
    }
    for (int i = 0; i < sz - 1; i++) {
        out += v[i].tos();
        out += " + ";
    }
    out += v[sz - 1].tos();
    return out;
}

bool hvec::equals(hvec b) {
    int sz = v.size();
    vector < hgen > bv = b.get_v();
    if (sz != bv.size()) {
        return false;
    }
    for (int i = 0; i < sz; i++) {
        if (! is_in(bv[i])) {
            return false;
        }
    }
    return true;
}

vector < hgen > hvec::get_v() const { return v; }

bool hvec::is_in(hgen hg) {
    int sz = v.size();
    for (int i = 0; i < sz; i++) {
        if (v[i].equals(hg)) {
            return true;
        }
    }
    return false;
}

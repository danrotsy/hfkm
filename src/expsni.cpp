/*
 * File: expsni.cpp
 * Author: Daniel Rostovtsev
 *
 * Created on August 21, 2018, 9:33 PM
 */

#include "expsni.h"

vector< vector < int > > combinations(int n, int k) {
    vector< vector < int > > combs;
    vector < int > selected;
    vector < int > selector(n);
    fill(selector.begin(), selector.begin() + k, 1);
    do {
        for (int i = 0; i < n; i++) {
            if (selector[i]) {
                selected.push_back(i);
            }
        }
        combs.push_back(selected);
        selected.clear();
    } while (prev_permutation(selector.begin(), selector.end()));
    return combs;
}

vector< vector < int > > all_ni(int k, int deg) {
    vector< vector < int > > combs = combinations(deg + k - 1, k - 1);
    int cap = combs.size();
    vector< vector < int > > exps;
    for (int i = 0; i < cap; i++) {
        vector < int > endpts;
        endpts.push_back(0);
        vector < int > comb (combs[i]);
        sort(comb.begin(), comb.end());
        for (int j = 0; j < k - 1; j++) {
            endpts.push_back(comb[j] + 1);
        }       
        endpts.push_back(deg + k);
        vector < int > exp;
        for (int j = 0; j < k; j++) {
            exp.push_back(endpts[j + 1] - endpts[j] - 1);
        }
        exps.push_back(exp);
    }
    return exps;
}

/* 
 * File: diff_test.cpp
 * Author: Daniel Rostovtsev
 *
 * Created on August 17, 2018, 7:23 PM
 */

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "gridio.h"
#include "grid.h"
#include "cgrp.h"
#include "diff.h"

using namespace std;

/* ./diff <dir> <a> <m>
 * ./diff <dir> <i> 
 * Used to find the differential of a given grid generator.
 * - <dir>: The knot directory.
 * - <a>: The Alexander grading.
 * - <m>: The Maslov grading.
 * - <i>: The factoradic index of a grid permutation. */
int main(int argc, char** argv) {
    string dir (argv[1]);
    if (argc == 4) {
        string as (argv[2]);
        int a = stoi(as);
        string ms (argv[3]);
        int m = stoi(ms);
        if (get_done(dir) == false) {
            cout << "Generators not yet computed.\n";
            abort();
        }
        vector < int > x_in = load_xo(dir)[0];
        vector < int > o_in = load_xo(dir)[1];
        grid g(x_in, o_in);
        cout << g.to_str();
        int k = g.get_k();
        cout << "Creating d_{" << as << "," << ms << "}...\n";
        cgrp dom = cgrp(a, m, dir, k);
        cout << "C_{" << as << "," << ms << "} BASIS:\n";
        cout << "{  ";
        for (int i = 0; i < dom.dim(); i++) {
            cout << dom.get_x(i).tos() << "  ";
        }
        cout << "}\n";
        cgrp ran = cgrp(a, m - 1, dir, k);
        cout << "C_{" << as << "," << to_string(m - 1) << "} BASIS:\n";
        cout << "{  ";
        for (int i = 0; i < ran.dim(); i++) {
            cout << ran.get_x(i).tos() << "  ";
        }
        cout << "}\n}";
        diff d_am = diff(g, dom, ran);
        vector< vector < bool > > d = d_am.get_d();
        cout << "DIFFERENTIAL:\n";
        for (int i = 0; i < d.size(); i++) {
            for (int j = 0; j < d[0].size(); j++) {
                cout << to_string(d[i][j]) << " ";
            }
            cout << "\n";
        }
        for (int j = 0; j < d[0].size(); j++) { /* One column at a time. */
            cout << "d( " << dom.get_x(j).tos() << " = SUM( \n";
            for (int i = 0; i < d.size(); i++) { /* For each row in column: */
                if (d[i][j] == 1) {
                    cout << ran.get_x(i).tos() << "\n";
                }
            }
            cout << ") \n";
        }
        cout << "Done.\n";
    }
    if (argc == 3) {
        cout << "Not yet implemented.\n";
    }
    return 0;
}

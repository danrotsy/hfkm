/* 
 * File:   main.cpp
 * Author: Daniel Rostovtsev
 *
 * Created on August 1, 2018, 10:04 AM
 */

#include <cstdlib>
#include <sstream>
#include "math.h"
#include "gridgen.h"
#include "grid.h"

using namespace std;

/* ./grid <x_in> <o_in> <dir>
 * Used to find grid generators, and their gradings, for a given knot.
 * - <x_in>: The permutation describing X intersections.
 * - <o_in>: The permutation describing O intersections.
 * - <dir>: The directory in which the generators are to be placed. 
 * Example: hfk_minus 2,1,0 0,2,1 u3x3
 * Note: dir must be made a directory, otherwise saving/loading will fail. */
int main(int argc, char** argv) {
    stringstream ssx(argv[1]);  /* Converts to argv[1] to x_in. */
    vector < int > x_in;
    while (ssx.good()) {
        string substr;
        getline(ssx, substr, ',');
        x_in.push_back(stoi(substr));
    }
    stringstream sso(argv[2]); /* Converts to argv[2] to o_in. */
    vector < int > o_in;
    while (sso.good()) {
        string substr;
        getline(sso, substr, ',');
        o_in.push_back(stoi(substr));
    }
    string dir (argv[3]);
    int k = x_in.size();
    int kfactorial = factorial(k);
    if (! get_done(dir)) {
        if (k <= 3) { /* If k < 12, just find and save the whole grid. */
            grid grd (x_in, o_in);
            cout << grd.to_str();
            grd.find_gens(dir, kfactorial);
            grd.save_gens(dir);
            set_done(dir, x_in, o_in);
        } else if (k > 3) {
            int n = kfactorial / k;
            for (int i = 0; i < k; i++) {
                grid grd(x_in, o_in);
                if (i == 0) { cout << grd.to_str(); }
                cout << "Finding generators " << to_string(n * i) << " to " <<
                    to_string((n + 1)*i) << ".\n";
                grd.find_gens(dir, n);
                grd.save_gens(dir);
            }
            set_done(dir, x_in, o_in);
        }
    } else {
        cout << "Generators already computed.\n";
    }
}

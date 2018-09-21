/*
 * File: itopcmd.cpp
 * Author: Daniel Rostovtsev
 *
 * Created on August 16, 2018, 2:33 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "jta.h"

using namespace std;

/* ./itop <k>
 * ./itop <k> <i>
 * Used to find permutations of size k given factoradic indices. If no index
 * is specified, then all permutations of size k, and their indices, are 
 * listed.
 * - <k>: permutation size
 * - <i>: factoradic index
 * Example 1: ./itop 3
 * Example 2: ./itop 3 0 */
int main(int argc, char** argv) {
    string kstr (argv[1]);
    int k = stoi(kstr);
    if (argc == 2) {
        cout << "Listing all permutations for k=" << to_string(k) << "...\n";
        int n = factorial(k);
        for (int i = 0; i < n; i++) {
            cout << to_string(i) << ": p=" << ptos(itop(i, k)) << "\n";
        }
    }
    if (argc == 3) {
        string istr (argv[2]);
        int i = stoi(istr);
        cout << to_string(i) << ": p=" << ptos(itop(i, k)) << "\n"; 
    }
    return 0;
}

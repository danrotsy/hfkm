/* 
 * File: hfkmcmd.cpp
 * Author: Daniel Rostovtsev
 *
 * Created on August 22, 2018, 5:20 PM
 */

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <NTL/mat_GF2.h>
#include "gridio.h"
#include "grid.h"
#include "cgrp.h"
#include "diff.h"
#include "hom.h"

using namespace std;
using namespace NTL;

/* ./hfkm <dir> <a> <m>
 * Used to find HFK^-(K) for a given bigrading (a, m)
 * - <dir>: The knot directory.
 * - <a>: The Alexander grading.
 * - <m>: The Maslov grading. */
int main(int argc, char** argv) {
    /* Loading up grid diagram information. */
    vector < int > x_in;    
    vector < int > o_in; 
    string dir (argv[1]);
    if (! get_done(dir)) {
        cout << "Directory is not fully generated.\n";
        abort();
    }
    string as (argv[2]);
    int a = stoi(as);
    string ms (argv[3]);
    int m = stoi(ms);
    x_in = load_xo(dir)[0];
    o_in = load_xo(dir)[1];
    grid grd (x_in, o_in);
    int k = x_in.size();
    /* Finding the chain groups of the desired gradings. */
    cout << "Finding C_{" << to_string(a) << "," << to_string(m + 1) << 
        "}...\n";
    cgrp cip1 = cgrp(a, m + 1, dir, k);
    cout << "Finding C_{" << to_string(a) << "," << to_string(m) << 
        "}...\n";
    cgrp ci = cgrp(a, m, dir, k);
    cout << "Finding C_{" << to_string(a) << "," << to_string(m - 1) << 
        "}...\n";
    cgrp cim1 = cgrp(a, m - 1, dir, k);
    cout << "Computing d_{" << to_string(a) << "," << to_string(m + 1) <<
        "}...\n";
    /* Computing the differentials at the desired gradings. */
    diff dip1 = diff(grd, cip1, ci);
    cout << "Computing d_{" << to_string(a) << "," << to_string(m) <<
        "}...\n";
    diff di = diff(grd, ci, cim1);
    Mat < GF2 > Di = di.get_D();
    Mat < GF2 > Dip1 = dip1.get_D();
    int rowsDi = Di.NumRows(); int colsDi = Di.NumCols();
    int rowsDip1 = Dip1.NumRows(); int colsDip1 = Dip1.NumCols();
    cout << "d_{" << to_string(a) << "," <<  to_string(m) << "}: " 
        << to_string(rowsDi) << "x" << to_string(colsDi) << ", d_{" 
        << to_string(a) << "," << to_string(m + 1) << "}: "
        << to_string(rowsDip1) << "x" << to_string(colsDip1) << "\n";
    /* Finding im Dip1 and ker Di. */
    cout << "Computing ker d_{" << to_string(a) << "," << to_string(m) 
        << "}...\n";
    Mat < GF2 > K;
    kernel(K, transpose(Di));
    Mat < GF2 > I;
    cout << "Computing im d_{" << to_string(a) << "," << to_string(m + 1)
        << "}...\n";
    image(I, transpose(Dip1));
    cout << "Row reducing d_{" << to_string(a) << "," << to_string(m + 1)
        << "}...\n";
    gauss(Dip1);
    long dimK = K.NumRows();
    long dimI = I.NumRows();
    if ((dimK != 0) and (ci.dim() != 0)) { /* Compute quotient. */
        vector < vector < bool > > h_basis;
        if (dimI != 0) { /* If quotient is non trivial. */
            cout << "Generating quotient matrix...\n";
            /* Stitch image and kernel together, then row reduce. */
            Vec < Vec < GF2 > > qvals = rep(I); /* Kernel added later. */
            Vec < Vec < GF2 > > kvals = rep(K);
            for (long i = 0; i < dimK; i++) { /* Adding kernel. */
                qvals.append(kvals[i]);
            }
            Mat < GF2 > Q;
            Q = to_mat_GF2(qvals);
            Q = transpose(Q);
            cout << "Reducing the kernel by the image...\n";
            long rkQ = gauss(Q);
            if (dimI != rkQ) {
                /* Find pivot columns. */
                vector < long > pcols; /* Only stores columns of kernel */
                long pcol = 0;
                long qrows = Q.NumRows();
                long qcols = Q.NumCols();
                for (long i = 0; i < rkQ; i++) {
                    for (long j = pcol; j < qrows; j++) {
                        if (IsOne(Q[i][j])) {
                            pcol = j;
                            if (j >= dimI) {
                                pcols.push_back(j);
                            }
                            break;
                        }
                    }
                }
                /* Augment h_basis to store pivot columns of K in Q. */
                for (long i = 0; i < (rkQ - dimI); i++) {
                    vector < bool > tmp;
                    for (long j = 0; j < qrows; j++) {
                        if (IsOne(K[pcols[i] - dimI][j])) {
                            tmp.push_back(1);
                        } else {
                            tmp.push_back(0);
                        }
                    }
                    h_basis.push_back(tmp);
                }
            } else { /* Quotient is trivial. */
                cout << "rk H_{" << to_string(a) << "," << to_string(m) 
                    << "} = 0\n";
                return 0;
            }
        } else { /* If quotient is trivial. */
            cout << "Quotient is trivial. Computing the basis...\n";
            long n = K.NumCols();
            for (long i = 0; i < dimK; i++) {
                vector < bool > tmp;
                for (long j = 0; j < n; j++) {
                    if (IsZero(K[i][j])) {
                        tmp.push_back(0);
                    } else {
                        tmp.push_back(1);
                    }
                }
                h_basis.push_back(tmp);
            }
        }
        cout << "Identifying quotient basis...\n";
        int cap = h_basis.size();
        vector < hvec > identified_h_basis;
        for (int i = 0; i < cap; i++) {
            /* Create hvec from vector in h_basis. */
            vector < cgen > cgv;
            for (int j = 0; j < ci.dim(); j++) {
                if (h_basis[i][j] == 1) {
                    cgv.push_back(ci.get_x(j));
                }
            }
            hvec hv = hvec(cgv);
            bool is_in = false;
            for (int j = 0; j < identified_h_basis.size(); j++) {
                if (hv.equals(identified_h_basis[j])) {
                    is_in = true;
                    break;
                }
            }
            if (!is_in) {
                identified_h_basis.push_back(hv);
            }
        }
        cout << "rk H_{" << to_string(a) << "," << to_string(m) << "} = " 
            << identified_h_basis.size() << "\n";
        for (int i = 0; i < identified_h_basis.size(); i++) {
            cout << identified_h_basis[i].tos() << "\n";
        }
    } else { /* Just 0. */
        cout << "rk H_{" << to_string(a) << "," << to_string(m) << "} = 0\n";
    }
    return 0;
}

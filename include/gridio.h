/* 
 * File:    gridio.h
 * Author:  Daniel Rostovtsev
 *
 * Created on August 16, 2018, 3:51 PM 
 */

#ifndef GRIDIO_H
#define GRIDIO_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem.hpp>
#include "jta.h"
#include "gridgen.h"
#include "cgen.h"

using namespace std;

/* If jtp.txt exists, in the directory dir, with one line:
 * x_0,dir_0:...:x_k-1,dir_k-1|m 
 * then returns the next jtp with m_prev and jtp_prev read from jtp.txt.
 * Otherwise, returns jtp corresponding to o. */
jtp get_start_jtp (string dir, vector < int > o);

/* Writes/overwrites to jtp.txt, in directory dir, the line:
 * x_0,dir_0:...:x_k-1,dir_k-1|m. */
void save_last_jtp (string dir, jtp j, int m);

/* Saves the generator, with factoradic index i relative to o, and bigrading
 * (a, m) to a new line in <dir>/<a>_<m>.txt. */
void write_gen (string dir, gridgen x_lst);

/* Returns a list of all generators in <dir>/<a>_<m>.txt, if the file exists.
 * Otherwise returns an empty list. */
vector < cgen > read_am (string dir, int a, int m, int k);

/* Returns a list of all Alexander-Maslov bigradings in a given directory. */
vector < vector < int > > list_all_am (string dir);

/* Puts the file done.txt into the directory, so that future runs of the 
 * program know the computation has already been made. */
void set_done (string dir, vector < int > x, vector < int > o);

/* Checks to see if the computation is done, by searching for done.txt. */
bool get_done (string dir);

vector< vector < int > > load_xo(string dir);

#endif /* GRIDIO_H */

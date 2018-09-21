/* 
 * File:   gridgen.cpp
 * Author: Daniel Rostovtsev
 * 
 * Created on August 1, 2018, 10:37 AM
 */

#include "gridgen.h"

gridgen::gridgen (vector < int > p_in) { p = p_in; }

vector < int > gridgen::get_p () const { return p; }

int gridgen::get_a () const { return a; }

int gridgen::get_m () const { return m; }

void gridgen::set_a (int a_new) { a = a_new; }

void gridgen::set_m (int m_new) { m = m_new; }

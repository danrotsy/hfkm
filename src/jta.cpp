/*
 * File: jta.cpp
 * Author: Daniel Rostovtsev
 *
 * Created on August 1, 2018, 2:14 PM
 */

#include "jta.h"

int factorial (int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

vector < int > itop (int n, int k) {
    vector < int > l;
    l.push_back(0);
    int m, r;
    for (int q = 1; q <= k; q++) {
        m = floor(n/q);
        r = n % q;
        l.insert(l.begin(), r);
        n = m;
    }
    vector < int > p;
    vector < int > nums;
    for (int i = 0; i < k; i++) {
        nums.push_back(i);
    }
    for (int i = 0; i < k; i++) {
        p.push_back(nums[l[i]]);
        nums.erase(nums.begin() + l[i]);
    }
    return p;
}

int ptoi (vector < int > p, int k) {
    vector < int > l;
    int l_i;
    for (int i = 0; i < k; i++) {
        l_i = 0;
        for (int j = i + 1; j < k; j++) {
            if (p[j] < p[i]) {
                l_i += 1;
            }
        }
        l.push_back(l_i);
    }
    int n = 0;
    for (int i = 0; i < k; i++) {
        n += l[k - i - 1] * factorial(i);
    }
    return n;
}

string ptos (vector < int > p) {
    string out = "( ";
    int k = p.size();
    for (int i = 0; i < k; i++) {
        out += to_string(p[i]);
        out += " ";
    }
    out += ")";
    return out;
}

jtp::jtp (vector < vector < int > > val_in, vector < int > o_in) {
    k = o_in.size();
    o = o_in;
    val = val_in;
    m_prev_set = false;
    val_prev_set = false;
}

vector < vector < int > > jtp::next () const {
    vector < int > mobile; /* Finding all mobile entries. */
    for (int i = 0; i < k; i ++) {
        if ((i == 0) and (val[0][1] == 1) and (val[0][0] > val[1][0])) {
            mobile.push_back(val[i][0]);
        }
        else if ((i == k - 1) and (val[k - 1][1] == -1) and 
                (val[k - 1][0] > val[k - 2][0])) {
            mobile.push_back(val[i][0]);
        }
        else if ((i > 0) and (i < k - 1)) { 
            if ((val[i][1] == 1) and (val[i][0] > val[i + 1][0])) {
                mobile.push_back(val[i][0]);
            } else if ((val[i][1] == -1) and (val[i][0] > val[i - 1][0])) {
                mobile.push_back(val[i][0]);
            }
        }
    }
    int max_mobile = 0; /* Finding the mobile entry with the largest index. */
    int max_mobile_i = 0;
    for (int i = 0; i < mobile.size(); i ++) {
        if (mobile[i] > max_mobile) {
            max_mobile = mobile[i];
        }
    }
    for (int i = 0; i < k; i++) {
        if (val[i][0] == max_mobile) {
            max_mobile_i = i;
        }
    }
    /* Constructing a copy of val for new jtp. */
    vector < vector < int > > next_val(val);
    /* Performing swaps according to max mobile. */
    int dir = next_val[max_mobile_i][1];
    vector < int > other = next_val[max_mobile_i + dir];
    next_val[max_mobile_i + dir] = next_val[max_mobile_i];
    next_val[max_mobile_i] = other;
    /* Swapping dir according to mobile. */
    for (int i = 0; i < k; i++) {
        if (next_val[i][0] > max_mobile) {
            next_val[i][1] = (-1) * next_val[i][1];
        }
    }
    return next_val; 
}

int jtp::get_i () const {
    vector < int > p;
    for (int i = 0; i < k; i++) {
        p.push_back(val[i][0]);
    }
    return ptoi(p, k);
}

vector < int > jtp::get_p () const {
    vector < int > p;
    for (int i = 0; i < k; i++) {
        p.push_back(o[val[i][0]]);
    }
    return p;
}

vector < vector < int > > jtp::get_val () const { return val; }

int jtp::get_m_prev () const {
    if (m_prev_set) {   
        return m_prev;
    } else {
        abort();
        return 0;
    }
}

vector < vector < int > > jtp::get_val_prev () const {
    if (val_prev_set) {
        return val_prev;
    } else {
        abort();
        vector < vector < int > > this_var_should_never_exist;
        return this_var_should_never_exist;
    }
}

bool jtp::get_m_prev_set () const { return m_prev_set; }

vector < int > jtp::get_p_prev () const {
    vector < int > p_prev;
    for (int i = 0; i < k; i++) {
        p_prev.push_back(o[val_prev[i][0]]);
    }
    return p_prev;
}

void jtp::set_m_prev (int m_prev_in) { 
    m_prev = m_prev_in; 
    m_prev_set = true; 
}

void jtp::set_val_prev (vector < vector < int > > val_prev_in) { 
    val_prev = val_prev_in;
    val_prev_set = true;
}

string jtp::tos () {
    string out = "";
    for (int i = 0; i < k - 1; i++) {
        out += to_string(val[i][0]);
        out += ",";
        out += to_string(val[i][1]);
        out += ":";
    }
    out += to_string(val[k - 1][0]);
    out += ",";
    out += to_string(val[k - 1][1]);
    return out;
}

jtp jtp0 (vector < int > o) {
    vector < vector < int > > val;
    int k = o.size();
    vector < int > tmp; tmp.push_back(0); tmp.push_back(0);
    for (int i = 0; i < k; i++) {
        tmp[0] = i; tmp[1] = -1;
        val.push_back(tmp);
    }
    return jtp(val, o);
}

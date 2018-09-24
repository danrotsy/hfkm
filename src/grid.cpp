/* 
 * File:   grid.cpp
 * Author: Daniel Rostovtsev
 * 
 * Created on August 1, 2018, 11:12 AM
 */

#include "grid.h"

grid::grid ( vector < int > x_in,  vector < int > o_in) { 
    /* Simple definitions */
    x = x_in;
    o = o_in;
    k = x_in.size();
    pi = acos(-1.0);
    /* Finding the knot path (X->O vertical, O->X horizontal) */
    int column = 0;
    vector < float > tmp; tmp.push_back(0.0); tmp.push_back(0.0);
    for (int i = 0; i < k; i++) {
        tmp[0] = (float)(column + 0.5); tmp[1] = (float)(x[column] + 0.5);
        path.push_back(tmp);
        tmp[0] = (float)(column + 0.5); tmp[1] = (float)(o[column] + 0.5);
        path.push_back(tmp);
        vector < int > :: iterator it = find_if (x.begin(), x.end(), 
            Is_Int(o[column]));
        column = it - x.begin();
    }
    tmp[0] = (float)(0.5); tmp[1] = (float)(x[column] + 0.5);
    path.push_back(tmp);
    /* Computing the shift in Alexander grading, 
     * a_shift = - (1 / 8) \sum_{i, j} a(c_{i, j}) - (n - 1) / 2 */
    vector < int > pt; pt.push_back(0); pt.push_back(0);   
    a_shift = 0;
    /* Summing a_c{i, j} over corners of Xs and Os. */
    for (int i = 0; i < (2 * k); i++) {
        pt[0] = ((int) floor(path[i][0])) % k;
        pt[1] = ((int) floor(path[i][1])) % k;
        a_shift += w(pt);
        pt[0] = ((int) floor(path[i][0])) % k;
        pt[1] = ((int) floor(path[i][1] + 1)) % k;
        a_shift += w(pt);
        pt[0] = ((int) floor(path[i][0] + 1)) % k;
        pt[1] = ((int) floor(path[i][1])) % k;
        a_shift += w(pt);
        pt[0] = ((int) floor(path[i][0] + 1)) % k;
        pt[1] = ((int) floor(path[i][1] + 1)) % k;
        a_shift += w(pt);
    }
    a_shift = floor((-1) * (((float) a_shift) / 8.0) 
        - (((float)(k - 1.0)) / 2.0) + 0.5);
}

void grid::find_gens (string dir, int n) {
    cout << "Finding chunk of generators of " << dir
        << "...\n";
    cout << "Loading first Johnson Trotter permutation...\n";
    /* Finds the starting jtp using gridio.h. */
    jtp jy = get_start_jtp(dir, o);
    cout << "Using " << jy.tos() << " (m=" << to_string(calc_m(jy)) 
        << ")\n"; /* Shows which jtp was loaded */
    clock_t t0 = clock(); /* Starts timer */
    /* Creating BASE GENERATORS and assigning both ALEXANDER and MASLOV 
     * gradings according to  J.T.A. */
    cout << "Computing Alexander and Maslov gradings...\n";
    boost::progress_display am_progress(n); /* Starts the progress bar. */
    jtp jx = jtp(jy.next(), o);
    gridgen x = gridgen(jx.get_p());
    gridgen y = gridgen(jy.get_p());
    y.set_a(calc_a(jy)); y.set_m(calc_m(jy));
    jx.set_m_prev(y.get_m()); jx.set_val_prev(jy.get_val());
    grid_gens.push_back(y);
    ++am_progress; /* Ticks the progress bar once. */
    x.set_a(calc_a(jx)); x.set_m(calc_m(jx));
    grid_gens.push_back(x);
    ++am_progress;
    for (int i = 2; i < n; i++) {
        jy = jtp(jx.get_val(), o);
        jx = jtp(jx.next(), o);
        jx.set_m_prev(x.get_m());
        jx.set_val_prev(jy.get_val());
        x = gridgen(jx.get_p());
        x.set_a(calc_a(jx)); x.set_m(calc_m(jx));
        grid_gens.push_back(x);
        ++am_progress;
    }
    cout << "Done.\n";
    clock_t t1 = clock(); /* Finds and displays time elapsed. */
    clock_t dt = t1 - t0;
    cout << "time elapsed: " << to_string( dt / (double) CLOCKS_PER_SEC) <<
        "s\n";
    save_last_jtp(dir, jx, calc_m(jx));
}

void grid::save_gens (string dir) {
    cout << "Saving generators...\n";
    clock_t t0 = clock();
    int n = grid_gens.size();
    boost::progress_display save_progress(n);
    for (int i = n - 1; i >= 0; i--) {
        write_gen(dir, grid_gens[i]);
        grid_gens.pop_back();
        ++save_progress;
    }
    cout << "Done.\n";
    clock_t t1 = clock();
    clock_t dt = t1 - t0;
    cout << "time elapsed: " << to_string( dt / (double) CLOCKS_PER_SEC) <<
        "s\n";
}

void grid::print_gens () {
    cout << "Printing all generators found:\n";
    for (int i = 0; i < grid_gens.size(); i++) {
        cout << ptos(grid_gens[i].get_p()) << " (" << grid_gens[i].get_a() << 
            "," << grid_gens[i].get_m() << ")\n";
    }
}

int grid::get_k () const { return k; }

int grid::w (vector < int > pt) {
    float dtheta = 0.0;
    float dx_a, dy_a, dx_b, dy_b, dx_c, dy_c;
    float a, b, c;
    for (int i = 0; i<(2 * k); i++) {
        dx_a = (float)(path[i][0]- pt[0]);
        dy_a = (float)(path[i][1] - pt[1]);
        dx_b = (float)(path[i + 1][0] - pt[0]);
        dy_b = (float)(path[i + 1][1] - pt[1]);
        dx_c = (float)(path[i + 1][0] - path[i][0]);
        dy_c = (float)(path[i + 1][1] - path[i][1]); 
        a = sqrt((dx_a * dx_a) + (dy_a * dy_a));
        b = sqrt((dx_b * dx_b) + (dy_b * dy_b));
        c = sqrt((dx_c * dx_c) + (dy_c * dy_c));
        if (((dx_a * dy_b) - (dx_b * dy_a)) > 0) {
            dtheta += acos(((a * a) + (b * b) - (c * c)) / (2 * a * b));
        } else {
            dtheta -= acos(((a * a) + (b * b) - (c * c))/(2 * a * b));
        }
    }
    return (int) floor(((-1) * (dtheta / (2 * pi))) + 0.5);
}

int grid::p_x4 (vector < int > p, rectangle r) {
    vector < float > pt; pt.push_back(0); pt.push_back(0);
    int a, b = 0;
    int sum = 0;
    for (int i = 0; i < k; i++) {
        a = i; b = p[i];
        pt[0] = ((float) a) - 0.5; pt[1] = ((float) b - 0.5);
        if (r.contains(pt)) {
            sum += 1;
        }
        pt[0] = ((float) a) - 0.5; pt[1] = ((float) b + 0.5);
        if (r.contains(pt)) {
            sum += 1;
        }
        pt[0] = ((float) a) + 0.5; pt[1] = ((float) b - 0.5);
        if (r.contains(pt)) {
            sum += 1;
        }
        pt[0] = ((float) a) + 0.5; pt[1] = ((float) b + 0.5);
        if (r.contains(pt)) {
            sum += 1;
        }
    }
    return sum;
}

int grid::n_o (int i, rectangle r) {
    vector < float > o_i_pt; 
    o_i_pt.push_back(i + 0.5); 
    o_i_pt.push_back(o[i] + 0.5);
    if (r.contains(o_i_pt)) {
        return 1;
    } else {
        return 0;
    }
}

int grid::o_ct (rectangle r) {
    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += n_o(i, r);
    }
    return sum;
}

vector< rectangle > grid::get_rectangles (vector < int > p1, 
        vector < int > p2) {
    vector < vector < int > > diff_pts;
    vector < rectangle > rectangles;
    vector < int > tmp; tmp.push_back(0); tmp.push_back(0);
    for (int i = 0; i < k; i++) {
        if (p1[i] != p2[i]) {
            tmp[0] = i; tmp[1] = p1[i];
            diff_pts.push_back(tmp);
        }
    }
    if (diff_pts.size() != 2) {
        return rectangles;
    } else {
        rectangles.push_back(rectangle(diff_pts[0], diff_pts[1], false));
        rectangles.push_back(rectangle(diff_pts[0], diff_pts[1], true));
        return rectangles;
    }
}

string grid::to_str () {
    string border_row = "+"; /* Creates border row. */
    for (int i = 0; i < k; i++) { border_row += "---+"; }
    border_row += "\n";
    string row = "|"; /* Creates the empty row template. */
    for (int i = 0; i < k; i++) { row += "   |"; }
    row += "\n";
    /* Stitches everything together to make an empty row. */
    string out = border_row; 
    for (int i = 0; i < k; i++) { out += (row + border_row); } 
    /* Adds Xs and Os. */
    vector < char > out_tmp(out.c_str(), out.c_str() + out.size() + 1u);
    int row_width = 2 + (4 * k);
    int x_pos;
    int o_pos;
    for (int i = 0; i < k; i++) {
        x_pos = (2 + (4 * i)) + (1 + 2 * (k - x[i] - 1)) * row_width;
        o_pos = (2 + (4 * i)) + (1 + 2 * (k - o[i] - 1)) * row_width;
        out_tmp[x_pos] = 'X';
        out_tmp[o_pos] = 'O';
    }
    out = string(out_tmp.begin(), out_tmp.end());

    return out;
}

int grid::calc_a (jtp j) {
    int s = 0;
    vector < int > pt; pt.push_back(0); pt.push_back(0); 
    for (int i = 0; i < k; i++) {
        pt[0] = i; pt[1] = j.get_p()[i];
        s += w(pt);
    }
    return s + a_shift;
}

int grid::calc_m (jtp j) {
    if (!j.get_m_prev_set()) { /* If it is the first permutation of J.T.A.: */
        return (1 - k);
    } else { /* If it is any other permutation of J.T.A.: */
        /* Assigning MASLOV GRADING using the Johnson Trotter algorithm 
         * (J.T.A.): M(x) - M(y) = P_x(r) + P_y(r) - 2 W(r) */
        int m_y = j.get_m_prev();
        vector < int > x = j.get_p();
        vector < int > y = j.get_p_prev();
        rectangle r = get_rectangles(x, y)[0];
        int m_r4 = p_x4(x, r) + p_x4(y, r);
        return m_y + ((int) m_r4 / 4) - (2 * o_ct(r));
    }
}

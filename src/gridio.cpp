/*
 * File:    gridio.cpp
 * Author:  Daniel Rostovtsev
 *
 * Created on August 16, 2018, 3:51 PM
 */

#include "gridio.h"

jtp get_start_jtp (string dir, vector < int > o) {
    string line;
    ifstream jtpfile (dir + "/jtp.txt");
    if (jtpfile.is_open()) { /* Checks that <dir>/jtp.txt exists. */
        getline(jtpfile, line); /* Gets the only line in <dir>/jtp.txt. */
        jtpfile.close();
        int m;
        /* The first split of jtp_m_split by ), is jtp_string
         * x_0,dir0:...:x_k-1,dirk_k-1 (with no last parenthesis) */
        vector < string > jtp_and_m;
        boost::split(jtp_and_m, line, boost::is_any_of("|"));
        string jtp_string = jtp_and_m[0];
        m = stoi(jtp_and_m[1]);
        /* Now to create jtp from jtp_string. First, splitting into 
         * x_i,dir_i */
        vector < string > x_dir;
        boost::split(x_dir, jtp_string, boost::is_any_of(":"));
        int k = x_dir.size();
        vector < vector < int > > val_prev;
        /* Now splitting x_i,dir_i into x & dir. */
        for (int i = 0; i < k; i++) {
            string jtp_substr = x_dir[i];
            vector < string > xi_diri;
            boost::split(xi_diri, jtp_substr, boost::is_any_of(","));
            vector < int > tmp;
            tmp.push_back(stoi(xi_diri[0]));
            tmp.push_back(stoi(xi_diri[1]));
            val_prev.push_back(tmp);
        }       
        /* Constructs the starting jtp and returns it */
        jtp j_prev = jtp(val_prev, o);
        vector< vector < int > > val = j_prev.next();
        jtp j = jtp(val, o);
        j.set_m_prev(m);
        j.set_val_prev(val_prev);
        return j;
    } else { /* If <dir>/jtp.txt does not exist, make default start jtp. */
        int k = o.size();
        vector< vector < int > > val;
        for (int i = 0; i < k; i++) {
            vector < int > tmp;
            tmp.push_back(i);
            tmp.push_back(-1);
            val.push_back(tmp);
        }
        return jtp(val, o);
    }
}

void save_last_jtp (string dir, jtp j, int m) {
    /* Delete <dir>/jtp.txt if it exists (remove needs const char*). */
    const char* filename = (dir + "/jtp.txt").c_str(); 
    /* Saves last jtp to <dir>/jtp.txt. */
    ofstream jtptxt (dir + "/jtp.txt");
    if (jtptxt.is_open()) {
        jtptxt << j.tos() << "|" << to_string(m);
        jtptxt.close();
    }
    jtptxt.close();
}

void write_gen (string dir, gridgen x) {
    int k = x.get_p().size();
    int a = x.get_a(); 
    int m = x.get_m();
    string am_filename = dir + "/" + to_string(a) + "_" + to_string(m) + 
        ".txt";
    ofstream am_file (am_filename, ios_base::app);
    am_file << to_string(ptoi(x.get_p(), k)) << "\n";
    am_file.close();
}

vector < cgen > read_am (string dir, int a, int m, int k) {
    vector < cgen > gens;
    string am_filename = dir + "/" + to_string(a) + "_" + to_string(m) 
        + ".txt";
    ifstream am_file (am_filename);
    if (am_file.is_open()) { /* If the file is opened: */
        string line;
        while (getline(am_file, line)) {
            int i = stoi(line);
            vector < int > p = itop(i, k);
            gens.push_back(cgen(p));
        }
        am_file.close();
        return gens;
    } else { /* If the file does not exist / cannot be opened: */
        return gens;
    }
}

vector < vector < int > > list_all_am (string dir) {
    vector< vector < int > > all_am;
    if (boost::filesystem::is_directory(dir)) {
        for (boost::filesystem::directory_iterator itr(dir); 
                itr != boost::filesystem::directory_iterator(); ++itr) {
            vector < int > tmp;
            string am_filename = itr->path().string();
            boost::erase_all(am_filename, dir);
            boost::erase_all(am_filename, "/");
            boost::erase_all(am_filename, ".txt");
            if ((am_filename != "jtp") and (am_filename != "done")) {
                vector < string > tmp_str;
                boost::split(tmp_str, am_filename, boost::is_any_of("_"));
                tmp.push_back(stoi(tmp_str[0]));
                tmp.push_back(stoi(tmp_str[1]));
                all_am.push_back(tmp);
            }
        }
    }
    return all_am;
}

void set_done (string dir, vector < int > x, vector < int > o) {
    string done_filename = dir + "/done.txt";
    ofstream done_file (done_filename, ios_base::app);
    int k = x.size(); /* Aassumed to be greater than or equal to two. */
    for (int i = 0; i < k - 1; i++) {
        done_file << to_string(x[i]) << ",";
    }
    done_file << to_string(x[k - 1]) << " ";
    for (int i = 0; i < k - 1; i++) {
        done_file << to_string(o[i]) << ",";
    }
    done_file << to_string(o[k - 1]);
    done_file.close();
}

bool get_done (string dir) {
    if (boost::filesystem::is_directory(dir)) {
        for (boost::filesystem::directory_iterator itr(dir); 
                itr != boost::filesystem::directory_iterator(); ++itr) {
            string filename = itr->path().string();
            boost::erase_all(filename, dir);
            boost::erase_all(filename, "/");
            boost::erase_all(filename, ".txt");
            if (filename == "done") {
                return true;
            }
        }
    }
    return false;
}

vector < vector < int > > load_xo(string dir) {
    string done_filename = dir + "/done.txt";
    ifstream done_file (done_filename);
    vector< vector < int > > out;
    vector < int > x;
    vector < int > o;
    string line;
    getline(done_file, line);
    vector < string > xo_str_vec;
    boost::split(xo_str_vec, line, boost::is_any_of(" "));
    vector < string > x_str_vec;
    vector < string > o_str_vec;
    boost::split(x_str_vec, xo_str_vec[0], boost::is_any_of(","));
    boost::split(o_str_vec, xo_str_vec[1], boost::is_any_of(","));
    int k = x_str_vec.size();
    for (int i = 0; i < k; i++) {
        x.push_back(stoi(x_str_vec[i]));
        o.push_back(stoi(o_str_vec[i]));
    }
    out.push_back(x);
    out.push_back(o);
    done_file.close();
    return out;
}

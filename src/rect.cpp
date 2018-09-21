/* 
 * File:   rectangle.cpp
 * Author: Daniel Rostovtsev
 * 
 * Created on August 1, 2018, 5:18 PM
 */

#include "rect.h"

rectangle::rectangle (vector < int > c1, vector < int > c2, bool inverted) {
    if (c1[0] < c2[0]) {
        left = c1[0]; right = c2[0];
    } else {
        left = c2[0]; right = c1[0];
    }
    if (c1[1] < c2[1]) {
        climbs = true;
        bottom = c1[1]; top = c2[1];
    } else {
        climbs = false;
        bottom = c2[1]; top = c1[1];
    }
    inv = inverted;
}

bool rectangle::contains (vector < float > pt) {
    if (climbs) {
        if (inv) {
            return ((pt[0] <= (float) left) or (pt[0] >= (float) right)) and 
                ((pt[1] <= (float) bottom) or (pt[1] >= (float) top));
        } else {
            return ((pt[0] >= (float) left) and (pt[0] <= (float) right)) and 
                ((pt[1] >= (float) bottom) and (pt[1] <= (float) top));
        }
    } else {
        if (inv) {
            return ((pt[0] >= (float) left) and (pt[0] <= (float) right)) and 
                ((pt[1] <= (float) bottom) or (pt[1] >= (float) top));
        } else {
            return ((pt[0] <= (float) left) or (pt[0] >= (float) right)) and
                ((pt[1] >= (float) bottom) and (pt[1] <= (float) top));
        }
    }
}

string rectangle::draw (int k) {
    string out = "";
    vector < float > pt; pt.push_back(0); pt.push_back(0);
    for (int y = k - 1; y >= 0; y--) {
        for (int x = 0; x < k; x++) {
            pt[0] = x + 0.5; pt[1] = y + 0.5;
            if (contains(pt)) {
                out += "X";
            } else {
                out += " ";
            }
        }
        out += "\n";
    }
    return out;
}    

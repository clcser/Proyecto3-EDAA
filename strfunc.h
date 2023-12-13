#ifndef SDSL_SUFFIX_ARRAYS_HPP
#include <sdsl/suffix_arrays.hpp>
#endif

using namespace sdsl;
using namespace std;

bool int_vector_strleq(int_vector<> &a, int froma, int toa, int_vector<> &b, int fromb, int tob) {
    int n = min(toa - froma, tob - fromb);

    for (int i=0;i<n;i++) {
        if (a[froma+i] < b[fromb+i])
            return true;

        else if (a[froma+i] > b[fromb+i])
            return false;
    }
    // cout << "lol\n";
    // cout << toa-froma << endl;
    // cout << tob-fromb << endl;

    // if (toa-froma > tob-fromb)
    //     return false;

    return true;
}

bool int_vector_strl(int_vector<> &a, int froma, int toa, int_vector<> &b, int fromb, int tob) {
    int n = min(toa - froma, tob - fromb);
    for (int i=0;i<n;i++) {
        if (a[froma+i] < b[fromb+i])
            return true;
        else if (a[froma+i] > b[fromb+i])
            return false;
    }

    if (toa-froma < tob-fromb)
        return true;
    return false;
}

void print_str_from(int_vector<> &s, int from) {
    int n = s.size();
    for (int i=from;i<n;i++) {
        cout << "[";
        cout << (char)s[i];
        cout << "]";
    }
}
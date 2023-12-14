#ifndef SDSL_SUFFIX_ARRAYS_HPP
#include <sdsl/suffix_arrays.hpp>
#endif

using namespace sdsl;
using namespace std;

typedef long long ll;

bool int_vector_strleq(int_vector<> &a, ll froma, ll toa, int_vector<> &b, ll fromb, ll tob) {
    ll n = min(toa - froma, tob - fromb);

    for (ll i=0;i<n;i++) {
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


// -1: a < b
//  0: a == b or one is prefix of the other
//  1: a > b
int strcmp_vector(int_vector<> &a, ll froma, ll toa, int_vector<> &b, ll fromb, ll tob) { 
    ll n = min(toa - froma, tob - fromb);

    for (ll i=0;i<n;++i) {
        if (a[froma+i] < b[fromb+i])
            return -1;

        else if (a[froma+i] < b[fromb+i])
            return 1;
    }
    return 0;
}


bool int_vector_strl(int_vector<> &a, ll froma, ll toa, int_vector<> &b, ll fromb, ll tob) {
    ll n = min(toa - froma, tob - fromb);
    for (ll i=0;i<n;i++) {
        if (a[froma+i] < b[fromb+i])
            return true;
        else if (a[froma+i] > b[fromb+i])
            return false;
    }

    if (toa-froma < tob-fromb)
        return true;
    return false;
}

void print_str_from(int_vector<> &s, ll from) {
    ll n = s.size();
    for (ll i=from;i<n;i++) {
        cout << "[";
        cout << (char)s[i];
        cout << "]";
    }
}
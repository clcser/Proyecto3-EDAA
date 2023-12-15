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
//  0: a == b
//  1: a > b
// compare(p, suff)
int strcmp_vector(const string &a, ll froma, ll toa, const string &b, ll fromb, ll tob) { 
    ll n = min(toa - froma, tob - fromb);

    for (ll i=0;i<n;i++) {

        if (a[froma+i] < b[fromb+i])
            return -1;
        else if (a[froma+i] > b[fromb+i])
            return 1;
    }
    
    if (toa-froma > tob-fromb)
        return 1;
    if (toa-froma < tob-fromb)
        return -1;
    return 0;
}

bool isPrefix(const string &a, ll froma, ll toa, const string &b, ll fromb, ll tob) {

    ll n = min(toa - froma, tob - fromb);

    // printf("%lld, %lld, %lld, %lld\n", froma, toa, fromb, tob);
    if (tob-fromb < toa-froma)
        return false;

    for (ll i=0;i<n;++i) {
        // cout << "comparing '" << (char)a[froma+i] << "' with '" << (char)b[fromb+i] << "'\n";
        if (a[froma+i] != b[fromb+i])
            return false;
    }

    return true;
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

void print_str_from(const string &s, ll from, ll to) {
    ll n = s.size();
    for (ll i=from;i<to;i++) {
        cout << "[";
        cout << s[i];
        cout << "]";
    }
}
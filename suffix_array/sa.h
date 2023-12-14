#ifndef SA_H
#define SA_H

#include <sdsl/suffix_arrays.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <set>

#include "strfunc.h"
#include "common.h"

typedef long long ll;
typedef pair<ll, ll> pll;

using namespace sdsl;
using namespace std;

pll sa_search(const string &seq, int_vector<> &sa, const string &p) {
    pll ans;

    ll n = seq.size();

    ll mid;
    ll low = 0;
    ll high = n;

    while (low < high) {
        mid = (low+high) / 2;

        // p > suff
        if (strcmp_vector(p, 0, p.size(), seq, sa[mid], seq.size()) == 1)
            low = mid + 1;
        // p <= suff
        else
            high = mid;
    }
    ans.first = low;

    high = n;

    while (low < high) {
        mid = (low+high) / 2;

        if (isPrefix(p, 0, p.size(), seq, sa[mid], seq.size())) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    ans.second = high;
    return ans;
}

ll sa_count(const string &seq, int_vector<> &sa, const string &p) {
    pll c = sa_search(seq, sa, p);
    return c.second - c.first;
}

set<ll> doc_locate(const string &seq, int_vector<> &sa, vector<ll> &docspos, const string &p) {
    pll bs = sa_search(seq, sa, p);
    cout << bs.first << " " << bs.second << "\n";
    vector<ll>::iterator it;
    set<ll> ans;


    for (ll i=bs.first;i<=bs.second;i++) {
        it = lower_bound(docspos.begin(), docspos.end(), sa[i]);
        ans.insert(it - docspos.begin());
    }
    return ans;
}

void printSuffixArray(const string &seq, int_vector<> &sa) {
    ll n = sa.size();
    for (ll i=0;i<n;++i) {
        // printf("%2d ", i);
        // if (seq[sa[i]] < 'a')
        //     break;
        cout << "'";
        for (ll j=sa[i];j<seq.size();++j) {
            cout << (char)seq[j];
            if (j-sa[i] > 10)
                break;
        }
        cout << "'\n";
    }
}

#endif

/*
int main(int argc, char** argv) {
    // Leemos el archivo de entrada y guardamos el contenido en 'seq'


    // Testeo de funcionalidad para suffix array
    // load_vector_from_file(seq, "ejemplo.txt", 1);
    // seq.resize(seq.size()+1);
    // seq[seq.size()-1] = '$';


    string pf = "datasets/dblp/dblp5MB_";
    vector<string> doc_names({pf+"1.xml", pf+"2.xml", pf+"3.xml", pf+"4.xml"});
    // vector<string> doc_names({pf+"1.xml"});

    vector<ll> docspos;
    string seq;
    int_vector<> empty_vec;
    load_documents(doc_names, true, seq, empty_vec, docspos);


    ll n = seq.size();
    cout << "Construyendo el Suffix array ..." << endl;
    
    int_vector<> sa(1, 0, bits::hi(n)+1);
    sa.resize(n);
    algorithm::calculate_sa((const unsigned char*)seq.data(), n, sa);

    cout << "Tamaño del SA " << size_in_mega_bytes(sa) << " MB." << endl;

    string p;
    stringstream buffer;
    ifstream file("patron.txt");
    buffer << file.rdbuf();
    p = buffer.str();

    // printSuffixArray(seq, sa);
    cout << "ocurrencias: " << sa_count(seq, sa, p) << "\n";




    set<ll> docs_ans = doc_locate(seq, sa, docspos, p);
    cout << "docs_size: " << docs_ans.size() << "\n"; 
    for (set<ll>::iterator it=docs_ans.begin();it!=docs_ans.end();it++) {
        cout << doc_names[*it] << "\n";
    }
    
    return 0;
}
*/
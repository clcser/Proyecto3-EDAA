#include <sdsl/suffix_arrays.hpp>
#include <string>
#include <iostream>
#include <algorithm>

#include "strfunc.h"
#include "common.h"

typedef long long ll;
typedef pair<ll, ll> pii;


using namespace sdsl;
using namespace std;

ll upper_bound_str(int_vector<> &seq, int_vector<> &sa, int_vector<> &p) {
    ll n = sa.size();
    ll mid;
    ll low = 1;
    ll high = n;

    while (low < high) {
        mid = (low + high) / 2;

        // if (int_vector_strleq(seq, sa[mid], seq.size()-1, p, 0, p.size())) {
        if (strcmp_vector(seq, sa[mid], seq.size()-1, p, 0, p.size()) <= 0) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    if (low < n && strcmp_vector(seq, sa[low], seq.size()-1, p, 0, p.size()) <= 0)
        low++;
    
    return low;

}

ll lower_bound_str(int_vector<> &seq, int_vector<> &sa, int_vector<> &p) {
    ll n = sa.size();
    ll mid;
    ll low = 1;
    ll high = n;

    while (low < high) {
        mid = (low + high) / 2;

        if (int_vector_strleq(p, 0, p.size(), seq, sa[mid], seq.size()-1) )
            high = mid;

        else
            low = mid + 1;
    }

    if (low < n && int_vector_strl(p, 0, p.size(), seq, sa[low], seq.size()-1))
        low++;
    
    return low;

}

pii sa_search(int_vector<> &seq, int_vector<> &sa, int_vector<> &p) {
    pii ans;
    ans.first = lower_bound_str(seq, sa, p);
    ans.second = upper_bound_str(seq, sa, p);
    return ans;
}

ll sa_count(int_vector<> &seq, int_vector<> &sa, int_vector<> &p) {
    pii c = sa_search(seq, sa, p);
    return c.second - c.first + 1;
}

vector<ll> doc_locate(int_vector<> &seq, int_vector<> &sa, vector<ll> &docspos, int_vector<> &p) {
    pii bs = sa_search(seq, sa, p);
    cout << bs.first << " " << bs.second << "\n";
    vector<ll> ans;
    vector<ll>::iterator result, it;
    // ll i = lower_bound_str(seq, sa, p);
    // while (i < n && )
    for (ll i=bs.first;i<=bs.second;i++) {
        result = lower_bound(docspos.begin(), docspos.end(), sa[i]);
        it = result;
        // if (!ans.empty() && ans.back() == *result)
        //     continue;
        ans.push_back(result-docspos.begin());
        while (i < seq.size() && *result == *it) {
            i++;
            it = lower_bound(docspos.begin(), docspos.end(), sa[i]);
        }
        i--;
    }
    return ans;
}



int main(int argc, char** argv) {
    if (argc !=  2) {
        cout << "Uso: " << argv[0] << " <archivo entrada>" << endl;
        return 1;
    }

    // Leemos el archivo de entrada y guardamos el contenido en 'seq'
    string infile(argv[1]);
    
    int_vector<> seq;

    string pf = "datasets/dblp/dblp5MB_";
    // vector<string> doc_names({pf+"1.xml", pf+"2.xml", pf+"3.xml", pf+"4.xml"});
    vector<string> doc_names({pf+"1.xml"});

    vector<ll> docspos;
    string empty_string("");
    load_documents(doc_names, false, empty_string, seq, docspos);
    ll n = seq.size();
    cout << "Construyendo el Suffix array ..." << endl;
    
    int_vector<> sa(1, 0, bits::hi(n)+1);
    sa.resize(n);
    algorithm::calculate_sa((const unsigned char*)seq.data(), n, sa);

    cout << "Tamaño del SA " << size_in_mega_bytes(sa) << " MB." << endl;

    int_vector<> p;
    load_vector_from_file(p, "patron.txt", 1);


    // cout << lower_bound_str(seq, sa, p) << "\n";
    // cout << upper_bound_str(seq, sa, p) << "\n";
    // cout << sa_count(seq, sa, p) << "\n";

    vector<ll> docs_ans = doc_locate(seq, sa, docspos, p);
    cout << "docs_size: " << docs_ans.size() << "\n"; 
    for (ll i=0;i<docs_ans.size();i++) {
        cout << doc_names[docs_ans[i]] << "\n";
    }
    
    return 0;
}

#include <sdsl/suffix_arrays.hpp>
#include <string>
#include <iostream>
#include <algorithm>

#include "strfunc.h"
#include "common.h"

typedef pair<int, int> pii;

using namespace sdsl;
using namespace std;

int upper_bound_str(int_vector<> &seq, int_vector<> &sa, int_vector<> &p) {
    int n = sa.size();
    int mid;
    int low = 1;
    int high = n;

    while (low < high) {
        mid = (low + high) / 2;

        if (int_vector_strleq(seq, sa[mid], seq.size()-1, p, 0, p.size())) {
            low = mid + 1;
        }
        else {
            high = mid;
        }
    }

    if (low < n && int_vector_strleq(seq, sa[low], seq.size()-1, p, 0, p.size()))
        low++;
    
    return low;

}

int lower_bound_str(int_vector<> &seq, int_vector<> &sa, int_vector<> &p) {
    int n = sa.size();
    int mid;
    int low = 1;
    int high = n;

    while (low < high) {
        mid = (low + high) / 2;

        if (int_vector_strleq(p, 0, p.size(), seq, sa[mid], seq.size()-1))
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

int sa_count(int_vector<> &seq, int_vector<> &sa, int_vector<> &p) {
    pii c = sa_search(seq, sa, p);
    return c.second - c.first + 1;
}

// int_vector<> doc_locate(int_vector<> &seq, int_vector<> &sa, vector<int> &docs, int_vector<> &p) {
//     pii bs = sa_search(seq, sa, p);

//     for (int i=bs.first;i<=bs.second;i++) {

//     }
// }



int main(int argc, char** argv) {
    if (argc !=  2) {
        cout << "Uso: " << argv[0] << " <archivo entrada>" << endl;
        return 1;
    }

    // Leemos el archivo de entrada y guardamos el contenido en 'seq'
    string infile(argv[1]);
    
    int_vector<> seq;

    string pf = "datasets/dblp/dblp5MB_";
    vector<string> v({pf+"1.xml", pf+"2.xml", pf+"3.xml", pf+"4.xml"});

    load_documents(v, false, pf, seq);
    int32_t n = seq.size();
    cout << "Construyendo el Suffix array ..." << endl;
    
    int_vector<> sa(1, 0, bits::hi(n)+1);
    sa.resize(n);
    algorithm::calculate_sa((const unsigned char*)seq.data(), n, sa);

    cout << "Tamaño del SA " << size_in_mega_bytes(sa) << " MB." << endl;

    // int_vector<> ex{'a'};
    // int_vector<> ex1{'a'};
    // int_vector<> p({'t', 'r', 'i'});
    int_vector<> p;
    load_vector_from_file(p, "patron.txt", 1);

    // print_str_from(seq, sa[1]);
    // cout << endl;
    // print_str_from(seq, 0);
    // cout << endl;
    // cout << int_vector_strleq(ex, 0, ex.size(), ex1, 0, ex1.size()) << "\n";
    // cout << int_vector_strleq(ex1, 0, ex1.size(), ex, 0, ex.size()) << "\n";
    // cout << int_vector_strleq(seq, sa[1], seq.size()-1, p, 0, p.size()) << "\n";
    // cout << int_vector_strleq(p, 0, p.size(), seq, sa[1], seq.size()-1) << "\n";

    


    cout << lower_bound_str(seq, sa, p) << "\n";
    cout << upper_bound_str(seq, sa, p) << "\n";
    cout << sa_count(seq, sa, p) << "\n";
    
    return 0;
}

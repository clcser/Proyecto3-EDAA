#include <algorithm>
#include <iostream>
#include <sdsl/suffix_arrays.hpp>
#include <string>

#include "./fm_index/fm_index.h"
#include "./suffix_array/sa.h"

#define RUNS 50

using namespace sdsl;
using namespace std;

int main() {

    double fm_time, sa_time;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - begin_time;

    std::ofstream structure_size_sa, structure_size_fm;
    structure_size_sa.open("experimental_data/structure_size_ms_sa.csv");
    structure_size_fm.open("experimental_data/structure_size_ms_fm.csv");
    structure_size_sa << "file_num, sa_size\n";
    structure_size_fm << "file_num, fm_size\n";

    //vector<string> file_names;
    string pfx = "datasets/dblp/dblp5MB_";
    string sfx = ".xml";

    for(int i = 1; i <= 10; ++i) {
        fm_time = sa_time = 0;
        // leer archivos y concatenarlos
        file_names.push_back(pfx+to_string(i)+sfx);
        vector<ll> docspos;
        string seq;
        load_documents(file_names, seq, docspos);

        //cout << "DOCSPOS:\n";
        //for(int i = 0; i < docspos.size(); i++) {
        //    cout << docspos[i] << " ";
        //}
        //cout << endl;
        
        // armar sa y fm-index
        FM_INDEX_SEARCH fm_index;
        fm_index.constructIndex(seq);

        long long n = seq.size();
        int_vector<> sa(1, 0, bits::hi(n)+1);
        sa.resize(n);
        algorithm::calculate_sa((const unsigned char*)seq.data(), n, sa);
        structure_size_sa << n << "," << size_in_mega_bytes(sa) << endl;
        structure_size_fm << n << "," << fm_index.fm_size() << endl;
    }
}
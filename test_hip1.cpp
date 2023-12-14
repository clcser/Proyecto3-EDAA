#include <algorithm>
#include <iostream>
#include <sdsl/suffix_arrays.hpp>
#include <string>

#include "./fm_index/fm_index.h"
#include "./suffix_array/sa.h"

#define RUNS 50

using namespace sdsl;
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " [archivos]" << endl;
        return 1;
    }

    double fm_time, sa_time;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - begin_time;

    std::ofstream text_size;
    text_size.open("experimental_data/text_size_ms.csv");
    text_size << "file_num, fm_time, sa_time\n";

    string seq = "";
    for(int i = 1; i < argc; ++i) {
        fm_time = sa_time = 0;
        // leer archivos y concatenarlos
        file_names.push_back(argv[i]);
        //int_vector<> tmp;
        //load_vector_from_file(tmp, argv[i], 1);
        //string str(tmp.begin(), tmp.end());
        //seq += str + (char)3;
        vector<ll> docspos;
        string seq;
        int_vector<> empty_vec;
        load_documents(doc_names, true, seq, empty_vec, docspos);
        
        // armar sa y fm-index
        FM_INDEX_SEARCH fm_index;
        fm_index.constructIndex(seq);

        int_vector<> sa(1, 0, bits::hi(n)+1);
        sa.resize(n);
        algorithm::calculate_sa((const unsigned char*)seq.data(), n, sa);
        cout << "Tamaño del SA " << size_in_mega_bytes(sa) << " MB." << endl;

        // hacer busqueda sobre esos archivos
        string pattern = "Incorrect IRQ";
        
        for(int j = 0; j < RUNS; ++j) {
            // BUSCAR EN FM INDEX
            begin_time = std::chrono::high_resolution_clock::now();
            fm_index.file_locate(pattern);
            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            fm_time += elapsed_time.count();

            // BUSCAR EN SUFFIX ARRAY
            begin_time = std::chrono::high_resolution_clock::now();
            set<ll> docs_ans = doc_locate(seq, sa, docspos, p);
            cout << "docs_size: " << docs_ans.size() << "\n"; 
            for (set<ll>::iterator it=docs_ans.begin();it!=docs_ans.end();it++) {
            //cout << doc_names[*it] << "\n";
            end_time = std::chrono::high_resolution_clock::now();
            elapsed_time = end_time - begin_time;
            sa_time += elapsed_time.count();
    }
        }
        fm_time /= RUNS;
        sa_time /= RUNS;
        text_size << i << "," << fm_time << "," << sa_time << "\n";
    }
}
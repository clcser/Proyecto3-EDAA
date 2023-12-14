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

    double fm_time, sa_time;
    auto begin_time = std::chrono::high_resolution_clock::now();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - begin_time;

    std::ofstream text_size;
    text_size.open("experimental_data/text_size_ms.csv");
    text_size << "file_num, fm_time, sa_time\n";

    vector<string> file_names;
    string pfx = "datasets/dblp/dblp5MB_";
    string sfx = ".xml";
    // for (ll i=1;i<=10;i++) 
    //     file_names.push_back(pfx+to_string(i)+sfx);
    // }


    for(int i = 1; i <= 10; ++i) {
        fm_time = sa_time = 0;
        // leer archivos y concatenarlos
        file_names.push_back(pfx+to_string(i)+sfx);
        //int_vector<> tmp;
        //load_vector_from_file(tmp, argv[i], 1);
        //string str(tmp.begin(), tmp.end());
        //seq += str + (char)3;
        vector<ll> docspos;
        string seq;
        load_documents(file_names, seq, docspos);
        cout << seq.size() << "\n";

        cout << "DOCSPOS:\n";
        for(int i = 0; i < docspos.size(); i++) {
            cout << docspos[i] << " ";
        }
        cout << endl;
        
        // armar sa y fm-index
        FM_INDEX_SEARCH *fm_index = new FM_INDEX_SEARCH();
        cerr << "?????\n";
        fm_index->constructIndex(seq);

        long long n = seq.size();
        int_vector<> sa(1, 0, bits::hi(n)+1);
        sa.resize(n);
        algorithm::calculate_sa((const unsigned char*)seq.data(), n, sa);
        cout << "Tamaño del SA " << size_in_mega_bytes(sa) << " MB." << endl;

        // hacer busqueda sobre esos archivos
        string pattern = "university";
        
        for(int j = 0; j < RUNS; ++j) {
            // BUSCAR EN FM INDEX
            cerr << "FLAG1\n";
            begin_time = std::chrono::high_resolution_clock::now();
            cerr << "FLAG2\n";
            fm_index->file_locate(pattern);
            cerr << "FLAG4\n";
            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            fm_time += elapsed_time.count();

            cerr << "FLAG3\n";
            // BUSCAR EN SUFFIX ARRAY
            begin_time = std::chrono::high_resolution_clock::now();
            set<ll> docs_ans = doc_locate(seq, sa, docspos, pattern);
            end_time = std::chrono::high_resolution_clock::now();
            cout << "SUFFIX ARRAY RESPONSE: " << docs_ans.size() << "\n";
            for (set<ll>::iterator it=docs_ans.begin();it!=docs_ans.end();it++) {
               cout << file_names[*it] << "; ";
            }
            cout << "\n";
            
            elapsed_time = end_time - begin_time;
            sa_time += elapsed_time.count();
        }
        fm_time /= RUNS;
        sa_time /= RUNS;
        text_size << i << "," << fm_time << "," << sa_time << "\n";
    }
}
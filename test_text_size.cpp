#include <algorithm>
#include <iostream>
#include <sdsl/suffix_arrays.hpp>
#include <string>

#include "fm_index.h"
//#include "suffix_array.h"

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
        int_vector<> tmp;
        load_vector_from_file(tmp, argv[i], 1);
        string str(tmp.begin(), tmp.end());
        seq += str + (char)3;

        // armar sa y fm-index
        FM_INDEX_SEARCH fm_index;
        fm_index.constructIndex(seq);

        // CONSTRUIR SUFFIX ARRAY

        // hacer busqueda sobre esos archivos
        string pattern = "Incorrect IRQ";
        
        for(int j = 0; j < RUNS; ++j) {
            begin_time = std::chrono::high_resolution_clock::now();
            fm_index.file_locate(pattern);
            end_time = std::chrono::high_resolution_clock::now();

            elapsed_time = end_time - begin_time;
            fm_time += elapsed_time.count();
            // BUSCAR EN SUFFIX ARRAY
        }
        fm_time /= RUNS;
        sa_time /= RUNS;
        text_size << i << "," << fm_time << "," << sa_time << "\n";
    }
}
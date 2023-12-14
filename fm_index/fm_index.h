#include <algorithm>
#include <iostream>
#include <sdsl/suffix_arrays.hpp>
#include <string>

#ifndef FM_INDEX_H
#define FM_INDEX_H

using namespace sdsl;
using namespace std;

vector<string> file_names;

class FM_INDEX_SEARCH {
   private:
    csa_wt<wt_huff<rrr_vector<127>>> fm_index;

   public:
    FM_INDEX_SEARCH() {}

    void constructIndex(string seq) {
        cout << seq.size() << "\n";
        cout << "FLAG13\n";
        construct_im(fm_index, seq, 1);
        cout << "FLAG14\n";

    }

    auto occurrences_position(const string& query) {
        cerr << "FLAG9\n";
        auto pos = locate(fm_index, query.begin(), query.end());
        cerr << "FLAG10\n";
        sort(pos.begin(), pos.end());
        cerr << "FLAG11\n";
        return pos;
    }

    void file_locate(const string& query) {
        // encontrar posiciones del patron
        cerr << "FLAG12\n";
        auto pattern_positions = occurrences_position(query);

        cerr << "FLAG5\n";
        // encontrar posiciones de los delimitadores de archivos
        string doc_delim = "\3";
        auto doc_positions = occurrences_position(doc_delim);
        cerr << "FLAG6\n";

        // calcular nombres de archivos en que se encuentra patron
        set<string> files;
        int p_size = pattern_positions.size();
        cerr << "FLAG7\n";
        for (int i = 0; i < p_size; i++) {
            int pos = lower_bound(doc_positions.begin(), doc_positions.end(), pattern_positions[i]) - doc_positions.begin();
            files.insert(file_names[pos]);
        }
        cerr << "FLAG8\n";

        cout << "The pattern: <" << query << "> matches in files: " << endl;
        for (auto f : files) cout << f << endl;
    }
};

#endif
/*
int main(int argc, char** argv) {
    // TODO:
    //      -hacer el input bkn
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " [archivos]" << endl;
        return 1;
    }

    // leer archivos y concatenarlos
    string seq;
    for (int i = 1; i < argc; i++) {
        file_names.push_back(argv[i]);
        int_vector<> tmp;
        load_vector_from_file(tmp, argv[i], 1);
        string str(tmp.begin(), tmp.end());
        seq += str + (char)3;
    }

    // construir FM-index
    FM_INDEX_SEARCH fm_index;
    fm_index.constructIndex(seq);

    // encontrar posiciones del patron
    string pattern = "Incorrect IRQ";
    fm_index.file_locate(pattern);

    return 0;
}
*/
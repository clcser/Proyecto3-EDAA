#include <algorithm>
#include <iostream>
#include <sdsl/suffix_arrays.hpp>
#include <string>

using namespace sdsl;
using namespace std;

// Por mientras ingresar los nombres de los archivos por argv, luego voy a poner el input bkn :)

class FM_INDEX_SEARCH {
   private:
    csa_wt<wt_huff<rrr_vector<127>>> fm_index;

   public:
    FM_INDEX_SEARCH() {}

    void constructIndex(string seq) { 
        construct_im(fm_index, seq, 1); 
    }

    auto occurrences_position(const string& query) {
        auto pos = locate(fm_index, query.begin(), query.end());
        sort(pos.begin(), pos.end());
        return pos;
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " [archivos]" << endl;
        return 1;
    }

    // leer archivos y concatenarlos
    vector<string> file_names;
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
    auto pattern_positions = fm_index.occurrences_position(pattern);

    // encontrar posiciones de los delimitadores de archivos
    string doc_delim = "\3";
    auto doc_positions = fm_index.occurrences_position(doc_delim);
   
    // calcular nombres de archivos en que se encuentra patron
    set<string> files;
    int p_size = pattern_positions.size();
    for (int i = 0; i < p_size; i++) {
        int pos = lower_bound(doc_positions.begin(), doc_positions.end(), pattern_positions[i]) - doc_positions.begin();
        files.insert(file_names[pos]);
    }

    cout << "The pattern: <" << pattern << "> matches in files: " << endl;
    for (auto f : files) cout << f << endl;

    return 0;
}
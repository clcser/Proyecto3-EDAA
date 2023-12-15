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

    void constructIndex(const string& seq) {
        cout << seq.size() << "\n";
        construct_im(fm_index, seq, 1);

    }

    auto occurrences_position(const string& query) {
        auto pos = locate(fm_index, query.begin(), query.end());
        sort(pos.begin(), pos.end());
        return pos;
    }

    void file_locate(const string& query) {
        auto pattern_positions = occurrences_position(query);
        string doc_delim = "\3";
        auto doc_positions = occurrences_position(doc_delim);

        // encontrar los archivos en donde se encuentra el patron
        set<string> files;
        int p_size = pattern_positions.size();
        for (int i = 0; i < p_size; i++) {
            int pos = lower_bound(doc_positions.begin(), doc_positions.end(), pattern_positions[i]) - doc_positions.begin();
            files.insert(file_names[pos]);
        }

        cout << "The pattern: <" << query << "> matches in files: " << endl;
        for (auto f : files) cout << f << endl;
    }
    
    long long fm_size() {
        return size_in_mega_bytes(fm_index);
    }
};

#endif
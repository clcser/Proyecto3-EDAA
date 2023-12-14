#ifndef SDSL_SUFFIX_ARRAYS_HPP
#include <sdsl/suffix_arrays.hpp>
#endif

#include <algorithm>
#include <string>
#include <vector>


bool load_documents(const std::vector<std::string> v, bool as_str, std::string &sdocs, sdsl::int_vector<> &vdocs, vector<long long> &docspos) {
    int n = v.size();
    if (as_str) { // return docs in string docs

        std::stringstream buffer;
        for (int i=0;i<n;i++) {
            std::ifstream t(v[i]);
            buffer << t.rdbuf();
            sdocs += buffer.str();
            sdocs += (char)3;
        }

    }
    else { // return docs in vdocs

        int m;
        int vdocs_size = 0;
        int_vector<> t;
        for (int i=0;i<n;i++) {
            cout << v[i] << "\n";
            load_vector_from_file(t, v[i]);
            // for (ll i=0;i<t.size();++i)
            //     cout << (char)t[i];
            // cout << "\n";
            m = t.size();
            vdocs.resize(vdocs_size + m + 1);
            // for (int j=vdocs_size;j<vdocs_size+m+1;++j) {
            //     vdocs[j] = t[j-vdocs_size];
            // }
            ll j;
            for (j=vdocs_size;j<vdocs_size+m;++j) {
                vdocs[j] = t[j-vdocs_size];
            }
            vdocs[j] = (char)3;
            vdocs_size += m + 1;
            docspos.push_back(vdocs_size-1);
        }
    }
    return 1;
}
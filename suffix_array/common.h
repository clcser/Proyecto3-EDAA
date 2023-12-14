#ifndef SDSL_SUFFIX_ARRAYS_HPP
#include <sdsl/suffix_arrays.hpp>
#endif

#include <algorithm>
#include <string>
#include <vector>


bool load_documents(const std::vector<std::string> v, std::string &sdocs, vector<long long> &docspos) {
    int n = v.size();

    std::stringstream buffer;
    for (int i=0;i<n;i++) {
        std::ifstream t(v[i]);
        buffer << t.rdbuf();
        sdocs += buffer.str();
        sdocs += (char)3;
        docspos.push_back(sdocs.size()-1);
    }

    return 1;
}
#include <algorithm>
#include <boost/algorithm/string/predicate.hpp>
#include <iostream>
#include "locxxate.h"

int main(int argc, char *argv[]) {
    const auto fAll = fetchAllFiles(argv[1]);
    const std::string searched = argv[2];

    auto it = std::find_if(
        fAll.begin(), fAll.end(),
        [&searched](const auto &v) { return boost::contains(v, searched); });

    while (it != fAll.end()) {
        std::cout << *it << std::endl;
        it = std::find_if(++it, fAll.end(), [&searched](const auto &v) {
            return boost::contains(v, searched);
        });
    }
}

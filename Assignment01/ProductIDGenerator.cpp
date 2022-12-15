#include "ProductIDGenerator.h"
#include <sstream>
#include <filesystem>

namespace fs = filesystem;

ProductIDGenerator::ProductIDGenerator() {
    // Do nothing
}

ProductIDGenerator::ProductIDGenerator(string folder) {
    _Folder = folder;
}

string ProductIDGenerator::next() {
    int i = 0;
    string filename = "";

    do {
        i++;

        stringstream builder;
        builder << _Folder << "\\" << i << ".txt";
        filename = builder.str();
    } while (fs::exists(filename));

    stringstream builder;
    builder << i;

    string result = builder.str();
    return result;
}

#include "ProductDataSet.h"
#include <filesystem>
#include <fstream>
namespace fs = filesystem;

#include "Utils.h"

vector<Product> ProductDataSet::getAll() {
    vector<Product> result;

    for (const auto& file : fs::directory_iterator(_Folder)) {
        stringstream builder;
        builder << _Folder << "\\"
            << file.path().filename().string();
        string filename = builder.str();

        ifstream reader(filename, ios::in);
        string buffer = "";
        getline(reader, buffer);
        reader.close();

        // Chuyen du lieu thanh doi tuong
        Product p = ProductDataSet::parse(buffer);
        result.push_back(p);
    }



    return result;
}

Product ProductDataSet::parse(string data) {
    const string Space = " ";

    size_t foundPos = data.find_first_of(Space);
    string info = data.substr(foundPos + 1,
        data.length() - foundPos - 1);

    const string Separator = ", ";
    auto tokens = Utils::String::split(info, Separator);

    const string Divider = "=";
    auto pair1 = Utils::String::split(tokens[0], Divider);
    string id = pair1[1];

    auto pair2 = Utils::String::split(tokens[1], Divider);
    string name = pair2[1];

    auto pair3 = Utils::String::split(tokens[2], Divider);
    string buffer = pair3[1];
    int price = stoi(buffer);

    Product p(id, name, price);
    return p;
}

ProductDataSet::ProductDataSet()
{

}

ProductDataSet::ProductDataSet(string Folder)
{
    _Folder = Folder;
    _idGen = new ProductIDGenerator(Folder);
}

int ProductDataSet::add(const Product& p) {
    if (!fs::exists(_Folder)) {
        fs::create_directory(_Folder);
    }

    stringstream builder;
    builder << _Folder << "\\" << p.id() << ".txt";
    string filename = builder.str();

    ofstream writer(filename, ios::out);

    writer << p.toString();

    writer.close();
    return 1;
}

ProductIDGenerator* ProductDataSet::IdGen() {
    return _idGen;
}
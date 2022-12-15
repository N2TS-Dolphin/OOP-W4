#pragma once
#include <string>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

#include "Product.h"
#include "ProductIDGenerator.h"

class ProductDataSet {
private:
    string _Folder = "";
    ProductIDGenerator* _idGen = NULL;
public:
    ProductDataSet();
    ProductDataSet(string Folder);
    vector<Product> getAll();
    int add(const Product& p);
public:
    ProductIDGenerator* IdGen();
    Product parse(string data);
};
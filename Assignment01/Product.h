#pragma once
#include <string>
using namespace std;

class Product {
private:
    string _id;
    string _name;
    int _price;
public:
    Product();
    Product(string, string, int);
public:
    string id() const;
public:
    string toString() const;
};
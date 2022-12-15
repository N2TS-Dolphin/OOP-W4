#include "Product.h"

#include <sstream>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>

namespace fs = filesystem;

#include "Utils.h"

Product::Product()
{

}

Product::Product(int id, string name, int price)
{
	this->_id = id;
	this->_name = name;
	this->_price = price;
}

string Product::toString() const
{
	stringstream builder;

	builder << "ID = " << _id << ", Name = " << _name << ", Price = " << _price << ".";

	string result = builder.str();
	return result;
}

int Product::id() const
{
	return _id;
}

IDGenerator::IDGenerator()
{

}

IDGenerator::IDGenerator(string folder)
{
	_Folder = folder;
}

int IDGenerator::next()
{
    int i = 0;
    string filename = "";

    do {
        i++;

        stringstream builder;
        builder << _Folder << "\\" << i << ".txt";
        filename = builder.str();
    } while (fs::exists(filename));

    return i;
}

ProductGenerator::ProductGenerator()
{
    srand(time(NULL));
}

ProductGenerator::ProductGenerator(string name, int price)
{
    _name = name;
    _price = price;
}

string ProductGenerator::NameNext()
{
    IntegerGenerator* IntGen = IntegerGenerator::instance();
    string nsx, model;

    vector <string> MSI = { "Alpha", "Bravo", "Katana" };
    vector <string> Lenovo = { "Legion 5", "ThinkPad", "IdeaPad" };
    vector <string> Apple = { "Macbook Air", "Macbook Pro" };
    vector <string> Asus = { "Ultrabook", "TUF Gaming", "Vivobook" };
    vector <string> Acer = { "Nitro 5", "Spin", "Predator" };
    vector <string> Dell = { "XPS", "Inspiron", "Vostro" };
    vector <float> size = { 13.3, 14, 15.6, 16.1, 17.3 };

    int x = IntGen->next(0, 5);

    switch (x)
    {
    case 0:
        nsx = "MSI";
        model = MSI[IntGen->next(0, 2)];
        break;

    case 1:
        nsx = "Lenovo";
        model = Lenovo[IntGen->next(0, 2)];
        break;

    case 2:
        nsx = "Apple";
        model = Apple[IntGen->next(0, 2)];
        break;

    case 3:
        nsx = "Asus";
        model = Asus[IntGen->next(0, 2)];
        break;

    case 4:
        nsx = "Acer";
        model = Acer[IntGen->next(0, 2)];
        break;

    case 5:
        nsx = "Dell";
        model = Dell[IntGen->next(0, 2)];
        break;
    }

    stringstream builder;

    builder << nsx << " " << model << " " << size[IntGen->next(0, 4)]<<" inches";

    string result = builder.str();
    return result;
}

int ProductGenerator::PriceNext()
{
    IntegerGenerator* IntGen = IntegerGenerator::instance();
    int price;
    price = IntGen->next(15, 50) * 1000000;
    
    return price;
}

vector<Product> WriteProduct::getAll() 
{
    vector<Product> result;
    int i = 1;

    for (const auto& file : fs::directory_iterator(_Folder)) 
    {
        stringstream builder;
        builder << _Folder << "\\" << i <<".txt";
        string filename = builder.str();

        ifstream reader(filename, ios::in);
        string buffer = "";
        getline(reader, buffer);
        reader.close();

        // Chuyen du lieu thanh doi tuong
        Product p = WriteProduct::parse(buffer);
        result.push_back(p);
        i++;
    }

    return result;
}

Product WriteProduct::parse(string data) {
    const string Space = " ";
    string buffer;

    size_t foundPos = data.find_first_of(Space);
    string info = data.substr(foundPos + 1,
        data.length() - foundPos - 1);

    const string Separator = ", ";
    auto tokens = Utils::String::split(info, Separator);

    const string Divider = "=";

    auto pair1 = Utils::String::split(tokens[0], Divider);
    buffer = pair1[1];
    int id = stoi(buffer);

    auto pair2 = Utils::String::split(tokens[1], Divider);
    string name = pair2[1];

    auto pair3 = Utils::String::split(tokens[2], Divider);
    buffer = pair3[1];
    int price = stoi(buffer);

    Product p(id, name, price);
    return p;
}

WriteProduct::WriteProduct()
{

}

WriteProduct::WriteProduct(string Folder)
{
    _Folder = Folder;
    _idGen = new IDGenerator(Folder);
}

int WriteProduct::add(const Product& p) {
    if (!fs::exists(_Folder)) 
    {
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

IDGenerator* WriteProduct::IdGen() 
{
    return _idGen;
}

DataContext::DataContext()
{
    _dbFolder = "Product";
    _products = new WriteProduct(_dbFolder);
}

WriteProduct* DataContext::Products()
{
    return _products;
}
#include "Product.h"
#include <sstream>
#include <filesystem>

namespace fs = filesystem;

Product::Product()
{

}

Product::Product(string id, string name, int price)
{
	this->_id = id;
	this->_name = name;
	this->_price = price;
}

string Product::toString() const
{
	stringstream builder;
	builder << "Product ID = " << _id << ", " << "Name = " << _name << ", " << "Price = " << _price << ".";

	string result = builder.str();
	return result;
}

string Product::id() const
{
	return _id;
}
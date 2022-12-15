#pragma once
#include "IntegerGenerator.h"

using namespace std;

#include <vector>

class Product
{
private:
	int _id;
	string _name;
	int _price;

public:
	Product();
	Product(int, string, int);

public:
	string toString() const;
	int id() const;
};

class IDGenerator
{
private:
	string _Folder;

public:
	IDGenerator();
	IDGenerator(string _FolderPath);

public:
	int next();
};

class ProductGenerator
{
private:
	string _name;
	int _price;

public:
	ProductGenerator();
	ProductGenerator(string, int);

public:
	string NameNext();
	int PriceNext();
};

class WriteProduct
{
private:
	string _Folder = "";
	IDGenerator* _idGen = NULL;

public:
	WriteProduct();
	WriteProduct(string Folder);
	vector<Product>getAll();
	int add(const Product& p);

public:
	IDGenerator* IdGen();
	Product parse(string data);
};

class DataContext 
{
private:
	inline static DataContext* _instance = NULL;
public:
	static DataContext* instance() 
	{
		if (_instance == NULL) 
		{
			_instance = new DataContext();
		}

		return _instance;
	}

private:
	WriteProduct* _products = NULL;
	string _dbFolder = "";
private:
	DataContext();
public:
	WriteProduct* Products();
};
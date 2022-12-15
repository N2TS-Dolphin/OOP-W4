#pragma once
#include <string>

using namespace std;

class ProductIDGenerator
{
private:
	string _Folder;
public:
	ProductIDGenerator();
	ProductIDGenerator(string FolderPath);
public:
	string next();
};
#include "Header.h"
#include "Product.h"

#include <string>

void displayAllProducts() 
{
    cout << "Display all products" << endl
        << endl;

    auto context = DataContext::instance();
    auto products = context->Products()->getAll();

    for (auto p : products) 
    {
        cout << p.toString() << endl;
    }
}

void GenerateNProducts()
{
    IntegerGenerator* IntGen = IntegerGenerator::instance();
    ProductGenerator ProductGen;
    int id;
    string name;
    int price;
    auto context = DataContext::instance();

    int n = IntGen->next(5, 10);

    for (int i = 0; i < n; i++)
    {
        id = context->Products()->IdGen()->next();
        name = ProductGen.NameNext();
        price = ProductGen.PriceNext();

        Product p(id, name, price);
        context->Products()->add(p);
    }

}
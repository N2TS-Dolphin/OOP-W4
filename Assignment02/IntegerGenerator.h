#pragma once
#include <iostream>

using namespace std;

class IntegerGenerator
{
private:
    inline static IntegerGenerator* _instance = NULL;
    IntegerGenerator();

public:
    static IntegerGenerator* instance();
    int next();
    int next(int max);
    int next(int left, int right);
};
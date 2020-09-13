#ifndef VARIABLE_H
#define VARIABLE_H
#include <iostream>
#include <vector>

class Variable
{
private:
    double value;

public:
    std::string name;
    Variable(std::string outStr = " ", double outVal = 0): name(outStr), value(outVal) {}
    double get_value(std::string s);
    std::string get_name();
    void set_value(std::string s, double d);
};

#endif // VARIABLE_H

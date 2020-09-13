#include <iostream>
#include <stdexcept>
#include <cmath>
#include "std_lib_facilities.h"

#include "token_stream.h"
#include "variable.h"

vector<Variable> var_table; // Таблица символов

double Variable::get_value(std::string s)
{
    for(const Variable& v: var_table)
        if(v.name == s) return v.value;
    throw std::logic_error("get: Неопределённая переменная \"" + s+ "\"");
}

void Variable::set_value(std::string s, double d)
{
    for(Variable& v : var_table)
    {
        if(v.name == s)
        {
            v.value = d;
            return;
        }
    }
    throw std::logic_error("set: Неопределённая переменная \"" + s+ "\"");
}


size_t factorial(size_t value)
{
    if(value == 0) return 1;
    size_t res = 1;
    for(size_t i = 1; i < value; ++i, res *= i);
    return res;
}

double primary();
double term()
{
    double left = primary();
    Token t = ts.get();
    while(true)
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            t = ts.get();
            break;

        case '/':
        {
            double div = primary();
            if(div == 0)
            {
                throw std::logic_error("Деление на нуль!");
            }
            left /= div;
            t = ts.get();
            break;
        }

        case '%':
        {
            double d = primary();
            if(d == 0) throw std::logic_error("% Деление на ноль!");
            left = fmod(left, d);
            t = ts.get();
            break;
        }

        case '!':
        {
            return factorial(size_t(left));
        }

        default:
            ts.putback(t);
            return left;
        }
    }
}

double expression()
{
    double left = term();
    Token t = ts.get();
    while(true)
    {
        switch(t.kind)
        {
        case '+':
            left += term();
            t = ts.get();
            break;

        case '-':
            left -= term();
            t = ts.get();
            break;

        default:
            ts.putback(t);
            return left;
        }
    }
}

double primary()
{
    Token t = ts.get();
    switch(t.kind)
    {
    case '{':
    {
        double d = expression();
        t = ts.get();
        if(t.kind != '}')
        {
            throw std::logic_error("Требуется '}'");
        }
        return d;
    }

    case '(':
    {
        double d = expression();
        t = ts.get();
        if(t.kind != ')')
        {
            throw std::logic_error("Требуется ')'");
        }
        return d;
    }

    case number:
    {
        Token factcheck = ts.get();
        if(factcheck.kind == '!') return factorial(size_t(t.value));
        else ts.putback(factcheck);
        return t.value;
    }

    case '-':
    {
        return -primary();
    }

    case '+':
    {
        return primary();
    }

    default:
        throw std::logic_error("Требуется первичное выражение!");
    }
}


bool is_declared(string var)
{
    for(const Variable& v: var_table)
    {
        if(v.name == var) return true;
        return false;
    }
}

double define_name(string var, double val)
{
    if(is_declared(var)) throw std::logic_error("Повторное объявление!");
    var_table.push_back(Variable(var, val));
    return val;
}

double declaration()
{
    Token t = ts.get();
    if(t.kind != name) throw std::logic_error("В объявлении ожидается имя переменной!");
    string var_name = t.name;

    Token t2 = ts.get();
    if(t2.kind != '=') throw std::logic_error("Пропущен символ '=' в объявлении!");

    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement()
{
    Token t = ts.get();
    switch(t.kind)
    {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

using namespace std;

int main()
{
    system("chcp 1251 > nul");

    double val = 0;
    while(true)
    {
        try
        {
             Token t = ts.get();
             if(t.kind == quit) break;
             if(t.kind == result) cout << "= " << val << "\n\n";
             else {ts.putback(t); val = statement();}
        }
        catch (std::exception &e)
        {
            cerr << e.what() << "\n\n";
            cin.ignore(500, '\n');
        }
    }

    return 0;
}

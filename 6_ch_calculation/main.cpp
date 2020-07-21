#include <iostream>
#include <stdexcept>
#include "token_stream.h"

static Token_stream ts;

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

    case '8':
    {
        Token factcheck = ts.get();
        if(factcheck.kind == '!') return factorial(size_t(t.value));
        else ts.putback(factcheck);
        return t.value;
    }

    default:
        throw std::logic_error("Требуется первичное выражение!");
    }
}

using namespace std;

int main()
{
    system("chcp 1251 > nul");

    double val = 0;
    while(cin)
    {
        try
        {
             Token t = ts.get();
             if(t.kind == 'q') break;
             else ts.putback(t);
             if(t.kind == '=')
             {
                 cout << "= " << val << "\n\n";
                 break;
             }
             val = expression();
        }
        catch (std::exception &e)
        {
            cerr << e.what() << "\n\n";
        }
    }

    return 0;
}

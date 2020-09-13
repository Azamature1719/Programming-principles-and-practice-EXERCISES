#include <sstream>
#include <iostream>
#include "token_stream.h"

Token_stream::Token_stream(): full(false), buffer(' ', 0) {}

void Token_stream::putback(Token t)
{
    if(full) throw std::logic_error("Буфер заполнен");
    buffer = t;
    full = true;
}

Token Token_stream::get()
{
    if(full)
    {
        full = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;

    switch(ch)
    {
    case result:
    case quit:
    case '(':
    case ')':
    case '{':
    case '}':
    case '+':
    case '-':
    case '*':
    case '/':
    case '!':
    case '%':
    {
        return Token{ch, 0};
    }

    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        std::cin.putback(ch);
        double val; std::cin >> val;
        return Token {'8', val};
    }

    default:
        if(isalpha(ch))
        {
            std::string s;
            s+=ch;
            while(std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
            std::cin.putback(ch);
            if(s == declkey)
                return Token(let);
            return Token{name, s};
        }
        throw std::logic_error("Неверная лексема");
    }
}

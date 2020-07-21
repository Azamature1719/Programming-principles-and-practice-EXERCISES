#include "token_stream.h"
#include <sstream>
#include <iostream>

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
    case '=':
    case 'q':
    case '(': case ')': case '{': case '}':
    case'+': case '-': case '*': case '/': case '!':
    {
        return Token{ch, 0};
    }

    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        std::cin.putback(ch);
        double val;
        std::cin >> val;

     return Token {'8', val};
    }

    default:
        throw std::logic_error("Неверная лексема");
    }
}

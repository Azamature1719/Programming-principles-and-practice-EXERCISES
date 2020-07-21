#include <iostream>
#include "token_stream.h"

Token_stream::Token_stream(): full(false), buffer(Token(Token::char_type::number, "0")) {}

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
    {
        return Token(Token::char_type::result, std::to_string(ch));
    }

    case '{': case '(': case '}': case ')':
    case '~': case '!': case '^': case '&': case '|':
    {
        return Token{Token::char_type::sign, std::to_string(ch)};
    }

    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        int number;
        std::cin.putback(ch);
        std::cin >> number;
        return Token {Token::char_type::number, std::to_string(number)};
    }

    default:
    {
        std::cout << "\ndef = " << ch;
        throw std::logic_error("Неверная лексема");
    }
    }
}

#include <iostream>
#include "token_stream.h"

static Token_stream ts;

int primary();
int term()
{
    int left = primary();
    Token t = ts.get();
    while(true)
    {
        if(stoi(t.value) == '&')
        {
            int right = primary();
            left &= right;
            t = ts.get();
        }
        else
        {
            ts.putback(t);
            return left;
        }
    }
}

int derived_term()
{
    int left = term();
    Token t = ts.get();
    while(true)
    {
        if(stoi(t.value) == '^')
        {
            int right = term();
            left ^= right;
            t = ts.get();
        }
        else
        {
            ts.putback(t);
            return left;
        }
    }
}

int expression()
{
    int left = derived_term();
    Token t = ts.get();
    while(true)
    {
        if(stoi(t.value) == '|')
        {
            int right = derived_term();
            left |= right;
            t = ts.get();
        }
        else
        {
            ts.putback(t);
            return left;
        }
    }
}

int primary()
{
    Token t = ts.get();
    while(true)
    {
        switch(t.kind)
        {
        case Token::char_type::sign:
        {
            switch(stoi(t.value))
            {
                case '~':
                {
                    Token next = ts.get();
                    if(next.kind == Token::char_type::number) return ~stoi(next.value);
                    if(stoi(t.value)== '(' || stoi(t.value) == '{') return ~expression();
                }
                break;

                case '!':
                {
                    Token next = ts.get();
                    if(next.kind == Token::char_type::number) return !stoi(next.value);
                    if(stoi(t.value) == '(' || stoi(t.value) == '{') return !expression();
                }
                break;

                case '{':
                {
                    int d = expression();
                    t = ts.get();
                    if(stoi(t.value) != '}')
                    {
                        throw std::logic_error("Требуется '}'");
                    }
                    return d;
                }

                case '(':
                {
                    int d = expression();
                    t = ts.get();
                    if(stoi(t.value) != ')')
                    {
                        throw std::logic_error("Требуется ')'");
                    }
                    return d;
                }

            default:
                throw std::logic_error("Грамматически неверное выражение!");
            }
        }
        break;

        case Token::char_type::number:
        {
            return stoi(t.value);
        }

        default:
            throw std::logic_error("Требуется первичное выражение!");
        }
    }
}

using namespace std;

int main()
{
    system("chcp 1251 > nul");

    int val = 0;
    Token t;

    while(cin)
    {
        t = ts.get();
        try
        {
             if(t.kind == Token::char_type::quit) break;
             if(t.kind == Token::char_type::result) cout << "= " << val << "\n\n";
             else ts.putback(t);
             val = expression();
        }
        catch (std::exception &e)
        {
            cerr << e.what() << "\n\n";

            std::string shit; // Для всяких как
            cin >> shit;
        }
    }
    return 0;
}

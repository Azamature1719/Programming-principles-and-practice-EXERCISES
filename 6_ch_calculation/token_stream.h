#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <stdexcept>

// Константные переменные для удобства чтения
const char number = '8';
const char quit = 'q';
const char result = '=';
const char name = 'a';
const char let = 'L';
const std::string declkey = "let";

class Token
{
public:
    char kind;
    double value;
    std::string name;

    Token(char out_ch): kind(out_ch) {}
    Token(char out_kind, double out_val): kind(out_kind), value(out_val) {}
    Token(char out_ch, std::string out_str): kind(out_ch), name(out_str) {}
};

class Token_stream
{
public:
    Token_stream();
    Token get();
    void putback(Token t);

private:
    bool full;
    Token buffer;
};

static Token_stream ts;

#endif // TOKEN_STREAM_H

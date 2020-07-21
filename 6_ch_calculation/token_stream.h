#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <stdexcept>

class Token
{
public:
    char kind;
    double value;
    Token(char out_kind, double out_val): kind(out_kind), value(out_val) {}
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

#endif // TOKEN_STREAM_H

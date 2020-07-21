#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include <stdexcept>

class Token
{
public:
    enum class char_type
    {
        number,
        sign,
        result,
        quit
    };

    char_type kind;
    std::string value;
    Token(char_type out_kind = char_type::sign, std::string out_val = " "): kind(out_kind), value(out_val) {}
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

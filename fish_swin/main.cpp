#include <iostream>

enum class part_of_speech
{
    article,
    noun,
    verb,
    conjuction,
    comma
};

part_of_speech get()
{
    std::string text;
    std::cin >> text;

    if(text == "the")
        return part_of_speech::article;

    if(text == "birds" || text == "fish" || text == "C++")
        return part_of_speech::noun;

    if(text == "swim" || text == "fly" || text == "rules")
        return part_of_speech::verb;

    if(text == "and" || text == "or" || text == "but")
        return part_of_speech::conjuction;

    if(text == ".")
        return part_of_speech::comma;

    throw std::logic_error("Не является частью грамматики!");
}

bool sentence()
{
    part_of_speech word = get();

    while(true)
    {
        switch(word)
        {
        case part_of_speech::article:
            if(get() != part_of_speech::noun) return false;
            break;

        case part_of_speech::noun:
            if(get() != part_of_speech::verb) return false;
            return true;

        default: return false;
        }
    }
}

bool input()
{
    while(true)
    {
        if(sentence())
        {
            part_of_speech next = get();
            if(next == part_of_speech::comma) return true;
            if(next != part_of_speech::conjuction) return false;
        }
        else
        {
            return false;
        }
    }
}

using namespace std;

int main()
{
    system("chcp 1251 > nul");

    size_t i = 0;
    while(cin)
    {
        try
        {
            if(input()) cout << "\nДа, является\n";
            else cout << "\nНет, не является\n";
        }
        catch (std::exception &e)
        {
            cerr << e.what() << "\n";
        }
        ++i;
    }

    return 0;
}

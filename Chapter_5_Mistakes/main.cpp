#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

int main()
{
    string s = "Success!\n";
    for(int i = 0; i < 6; ++i)
    {
        cout << s[i];
    }

    return 0;
}

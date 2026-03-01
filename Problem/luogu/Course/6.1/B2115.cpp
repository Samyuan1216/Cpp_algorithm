#include <iostream>
using namespace std;

int main()
{
    char s[10010] = {};
    cin.getline(s, 10000);

    for (auto &x: s)
    {
        if (x >= 'a' && x <= 'z')
        {
            x = (x - 'a' + 25) % 26 + 'a';
        }
        else if (x >= 'A' && x <= 'Z')
        {
            x = (x - 'A' + 25) % 26 + 'A';
        }
    }

    cout << s << endl;
}
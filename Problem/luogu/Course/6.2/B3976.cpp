#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s, r;
    getline(cin, s);

    for (auto &c: s)
    {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            r += c;
        }
    }

    cout << r << endl;
}
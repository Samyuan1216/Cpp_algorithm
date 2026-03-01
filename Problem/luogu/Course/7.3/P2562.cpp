#include <iostream>
#include <string>
using namespace std;

string T(string s);

int main()
{
    string s;
    cin >> s;

    cout << T(s) << endl;
}

string T(string s)
{
    if (s.find('0') == string::npos)
    {
        return "B";
    }
    else if (s.find('1') == string::npos)
    {
        return "A";
    }
    else
    {
        int half = s.length() / 2;

        return "C" + T(s.substr(0, half)) + T(s.substr(half, half));
    }
}
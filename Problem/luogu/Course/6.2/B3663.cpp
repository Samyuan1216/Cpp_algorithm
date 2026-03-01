#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    getline(cin, s);

    int index = -1, cnt = 0;
    while (s.find("luogu", index + 1) != string::npos)
    {
        index = s.find("luogu", index + 1);
        cnt++;
    }

    cout << cnt << endl;
}
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char s[110] = {};
    cin.getline(s, 100);
    int n = strlen(s);

    for (int i = 0; i < n; i++)
    {
        cout << char(s[i] + s[(i + 1) % n]);
    }

    cout << endl;
}
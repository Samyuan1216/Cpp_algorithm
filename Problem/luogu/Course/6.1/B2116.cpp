#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    char s[52] = {};
    cin.getline(s, 50);

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = s[i] - 'A' + 'a';
            s[i] = (s[i] - 'a' + 3) % 26 + 'a';
        }
        else
        {
            s[i] = s[i] - 'a' + 'A';
            s[i] = (s[i] - 'A' + 3) % 26 + 'A';
        }
    }

    reverse(&s[0], &s[strlen(s)]);

    cout << s << endl;
}
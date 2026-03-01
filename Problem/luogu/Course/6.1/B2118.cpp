#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char s1[30] = {}, s2[30] = {};
    cin.getline(s1, 25);
    cin.getline(s2, 25);

    if (strstr(s2, s1))
    {
        cout << s1 << " is substring of " << s2 << endl;
    }
    else if (strstr(s1, s2))
    {
        cout << s2 << " is substring of " << s1 << endl;
    }
    else
    {
        cout << "No substring" << endl;
    }
}
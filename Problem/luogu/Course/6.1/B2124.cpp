#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char s[100] = {};
    cin.getline(s, 100);

    bool flag = true;
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        if (s[i] != s[j])
        {
            flag = false;
            break;
        }
    }

    if (flag == true)
    {
        cout << "yes" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
}
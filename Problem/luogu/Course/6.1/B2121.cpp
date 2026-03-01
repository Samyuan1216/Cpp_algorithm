#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char delimiter[] = " ,.";
    char s[22000] = {};
    cin.getline(s, 22000);

    char maxstr[110] = {}, minstr[110] = {};
    char *token = strtok(s, delimiter);
    strcpy(maxstr, token);
    strcpy(minstr, token);

    while (token)
    {
        if (strlen(maxstr) < strlen(token))
        {
            strcpy(maxstr, token);
        }

        if (strlen(minstr) > strlen(token))
        {
            strcpy(minstr, token);
        }

        token = strtok(NULL, delimiter);
    }

    cout << maxstr << endl;
    cout << minstr << endl;
}
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;
    getchar();

    string question[m];
    for (auto &str: question)
    {
        getline(cin, str);
    }

    for (int i = 0; i < n; i++)
    {
        string p;
        getline(cin, p);

        for (auto &str: question)
        {
            string correct = p + ".zip/" + p + "/" + str + "/" + str + ".cpp";

            string r;
            getline(cin, r);

            if (r == correct)
            {
                cout << "Fusu is happy!" << endl;
            }
            else
            {
                cout << "Fusu is angry!" << endl;
            }
        }
    }
}
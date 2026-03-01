#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
    int N = 0, k = 0;
    cin >> N >> k;

    map<string, int> m;
    for (int i = 0; i < N; i++)
    {
        string s;
        int v;
        cin >> s >> v;

        m.emplace(s, v);
    }

    getchar();

    while (k--)
    {
        string s;
        getline(cin, s);

        while (s.find("{") != string::npos)
        {
            int l = s.find("{"), r = s.find("}");
            string t = s.substr(l + 1, r - l - 1);

            s.replace(l, r - l + 1, to_string(m[t]));
        }

        cout << s << endl;
    }
}
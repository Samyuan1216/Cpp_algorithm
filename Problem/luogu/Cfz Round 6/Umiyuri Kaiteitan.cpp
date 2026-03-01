#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    map<int, int> file;

    int size = -1;
    while (n--)
    {
        int x;
        cin >> x;

        string s = to_string(x);
        if (file.find(x) == file.end())
        {
            size += 1 + s.length();
        }

        file[x] = 0;
        file[x] = size;
    }

    for (auto &ans: file)
    {
        cout << ans.second << " ";
    }
}
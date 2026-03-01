#include <iostream>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    int N = 0;
    cin >> N;

    stack<int> s;
    multiset<int> ms;
    while (N--)
    {
        int index = 0;
        cin >> index;

        if (index == 0)
        {
            int X = 0;
            cin >> X;

            s.push(X);
            ms.insert(X);
        }
        else if (index == 1)
        {
            if (s.empty() == false)
            {
                ms.erase(s.top());
                s.pop();
            }
        }
        else if (index == 2)
        {
            if (s.empty() == true)
            {
                cout << 0 << endl;
            }
            else
            {
                cout << *ms.rbegin() << endl;
            }
        }
    }
}
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    int q = 0;
    cin >> q;

    while (q--)
    {
        int n = 0;
        cin >> n;

        vector<int> pushed(n), poped(n);
        for (auto &x: pushed)
        {
            cin >> x;
        }

        for (auto &x: poped)
        {
            cin >> x;
        }

        stack<int> stk;

        int index = 0;
        for (auto &x: pushed)
        {
            stk.push(x);

            while (stk.empty() == false && poped[index] == stk.top())
            {
                stk.pop();
                index++;
            }
        }

        cout << (stk.empty() == true? "Yes": "No") << endl;
    }
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int T = 0;
    cin >> T;

    while (T--)
    {
        long long n = 0;
        cin >> n;

        if (n % 4 == 0)
        {
            cout << "Yes" << endl;
            continue;
        }

        vector<int> number;
        while (n > 0)
        {
            number.push_back(n % 10);
            n /= 10;
        }

        reverse(number.begin(), number.end());

        bool flag = false;
        for (auto i = 0; i < number.size() && flag == false; i++)
        {
            for (auto j = i + 1; j <= number.size() && flag == false; j++)
            {
                auto temp = number;
                temp.erase(temp.begin() + i, temp.begin() + j);

                if (temp.empty() == true)
                {
                    continue;
                }

                long long sum = 0;
                int index = 0;
                for (auto &x: temp)
                {
                    sum = sum * 10 + x;
                }

                if (sum % 4 == 0)
                {
                    flag = true;
                }
            }
        }

        cout << (flag == true? "Yes": "No") << endl;
    }
}
#include <iostream>
#include <string.h>
using namespace std;

class Big_Int
{
    int *digits = nullptr;
    int size = 0;
public:
    Big_Int& operator=(const string &rhs)
    {
        if (digits != nullptr)
        {
            delete[] digits;
            digits = nullptr;
        }

        size = rhs.size();
        digits = new int[size];
        for (int i = 0; i < size; i++)
        {
            digits[i] = rhs[size - 1 - i] - '0';
        }

        return *this;
    }

    Big_Int operator*(const Big_Int &rhs)
    {
        Big_Int res;
        res.size = size + rhs.size;
        res.digits = new int[res.size];
        memset(res.digits, 0, sizeof(int) * res.size);

        for (int i = 0; i < rhs.size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                res.digits[i + j] += rhs.digits[i] * digits[j];
                if (res.digits[i + j] >= 10)
                {
                    res.digits[i + j + 1] += res.digits[i + j] / 10;
                    res.digits[i + j] %= 10;
                }
            }
        }

        while (res.size > 1 && res.digits[res.size - 1] == 0)
        {
            res.size--;
        }

        return res;
    }

    friend istream& operator>>(istream &lhs, Big_Int &rhs)
    {
        string str;
        lhs >> str;
        rhs = str;

        return lhs;
    }

    friend ostream& operator<<(ostream &lhs, const Big_Int &rhs)
    {
        for (int i = rhs.size - 1; i >= 0; i--)
        {
            lhs << rhs.digits[i];
        }

        return lhs;
    }
};

int main()
{
    Big_Int a, b;
    cin >> a >> b;
    cout << a * b << endl;
}
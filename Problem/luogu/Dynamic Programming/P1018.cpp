#include <bits/stdc++.h>
using namespace std;

class Big_Int
{
    int *digits = nullptr;
    int size = 0;
public:
    Big_Int& operator=(const int &rhs)
    {
        if (digits != nullptr)
        {
            delete[] digits;
            digits = nullptr;
        }

        if (rhs == 0)
        {
            size = 1;
            digits = new int[1]{0};
            return *this;
        }

        int num = rhs;
        int len = 0;
        while (num > 0)
        {
            num /= 10;
            len++;
        }

        num = rhs;
        size = len;
        digits = new int[size];
        
        for (int i = 0; i < size; i++)
        {
            digits[i] = num % 10;
            num /= 10;
        }

        return *this;
    }

    Big_Int& operator=(const Big_Int &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        if (digits != nullptr)
        {
            delete[] digits;
            digits = nullptr;
        }

        size = rhs.size;
        digits = new int[size];

        for (int i = 0; i < size; i++)
        {
            digits[i] = rhs.digits[i];
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
                res.digits[i + j] += digits[j] * rhs.digits[i];
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

    Big_Int operator*(const int &rhs)
    {
        Big_Int res;
        res = rhs;
        res = *this * res;
        
        return res;
    }

    Big_Int operator+(const int &rint)
    {
        Big_Int ret;
        Big_Int rhs;
        rhs = rint;
        ret.size = (size >= rhs.size? size: rhs.size) + 1;
        ret.digits = new int[ret.size];
        memset(ret.digits, 0, sizeof(int) * ret.size);
        
        for (int i = 0; i < ret.size - 1; i++)
        {
            if (i < size)
            {
                ret.digits[i] += digits[i];
            }

            if (i < rhs.size)
            {
                ret.digits[i] += rhs.digits[i];
            }

            if (ret.digits[i] >= 10)
            {
                ret.digits[i] -= 10;
                ret.digits[i + 1]++;
            }
        }

        while (ret.size > 1 && ret.digits[ret.size - 1] == 0)
        {
            ret.size--;
        }

        return ret;
    }

    bool operator<(const Big_Int &rhs) const
    {
        if (size != rhs.size)
        {
            return size < rhs.size;
        }

        for (int i = size - 1; i >= 0; i--)
        {
            if (digits[i] != rhs.digits[i])
            {
                return digits[i] < rhs.digits[i];
            }
        }

        return false;
    }

    static Big_Int max(const Big_Int &x, const Big_Int &y)
    {
        Big_Int res;
        if (x < y)
        {
            res = y;
        }
        else
        {
            res = x;
        }
        
        return res;
    }

    static Big_Int stobi(const string &s)
    {
        Big_Int res;
        res.size = s.length();
        res.digits = new int[res.size];

        for (int i = 0; i < res.size; i++)
        {
            res.digits[i] = s[res.size - 1 - i] - '0';
        }

        return res;
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
    int N = 0, K = 0;
    cin >> N >> K;

    string s;
    cin >> s;

    vector<vector<Big_Int>> dp(K + 1, vector<Big_Int>(N));
    dp[0][0] = s[0] - '0';

    for (int i = 1; i < N; i++)
    {
        dp[0][i] = dp[0][i - 1] * 10 + (s[i] - '0');
    }
    
    Big_Int maxn;
    for (int i = 1; i <= K; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i > j)
            {
                continue;
            }

            for (int k = i; k <= j; k++)
            {
                dp[i][j] = Big_Int::max(dp[i][j], dp[i - 1][k - 1] * Big_Int::stobi(s.substr(k, j - k + 1)));
            }

            if (i == K && maxn < dp[i][j])
            {
                maxn = dp[i][j];
            }
        }
    }

    cout << maxn << endl;
}
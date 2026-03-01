#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000010;
vector<int> inv(MAXN);
int n = 0, p = 0;

template<typename T> inline T read()
{
    T x = 0, f = 1;
    char ch = '\0';

    for (; isdigit(ch) == 0; ch = getchar())
    {
        if (ch == '-')
        {
            f = -1;
        }
    }

    for (; isdigit(ch) != 0; ch = getchar())
    {
        x = (x << 3) + (x << 1) + (ch - '0');
    }

    return x * f;
}

template<typename T> inline void write(T x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }

    static int sta[40];
    int top = 0;

    do
    {
        sta[top++] = x % 10;
        x /= 10;
    } while (x > 0);
    
    while (top > 0)
    {
        putchar(sta[--top] + '0');
    }
}

int main()
{
    n = read<int>(), p = read<int>();

    inv[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        inv[i] = (int)(p - (long long)inv[p % i] * (p / i) % p);
    }

    for (int i = 1; i <= n; i++)
    {
        write<int>(inv[i]);
        putchar('\n');
    }
}
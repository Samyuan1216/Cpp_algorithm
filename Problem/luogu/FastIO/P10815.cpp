#include <bits/stdc++.h>
using namespace std;

long long n = 0, sum = 0;

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

    static int sta[40] = {};
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
    n = read<long long>();
    while (n--)
    {
        sum += read<long long>();
    }

    write<long long>(sum);
    putchar('\n');
}
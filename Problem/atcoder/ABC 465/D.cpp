#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

struct FastIO
{
    static constexpr int BUFFER_SIZE = 1 << 20;
    char buffer[BUFFER_SIZE];
    int len = 0;
    int prec = 6;

    char getchar()
    {
        static char input[BUFFER_SIZE], *start = input, *end = input;
        if (start == end)
        {
            start = input;
            end = start + std::fread(input, 1, BUFFER_SIZE, stdin);
        }

        return start == end ? EOF : *start++;
    }

    void putchar(char x)
    {
        if (len == BUFFER_SIZE)
        {
             flush();
        }

        buffer[len++] = x;
    }

    ~FastIO()
    {
        flush();
    }

    void flush()
    {
        if (len != 0)
        {
            std::fwrite(buffer, 1, len, stdout);
            len = 0;
        }
    }

    FastIO& setp(int p)
    {
        prec = p;
        return *this;
    }

    FastIO& operator>>(std::string& s)
    {
        s.clear();
        char ch = getchar();
        while (ch != EOF && !std::isgraph(ch))
        {
            ch = getchar();
        }

        if (ch == EOF)
        {
            return *this;
        }

        while (ch != EOF && std::isgraph(ch))
        {
            s += ch;
            ch = getchar();
        }

        return *this;
    }

    FastIO& operator<<(std::string_view s)
    {
        for (char c: s)
        {
            putchar(c);
        }

        return *this;
    }

    FastIO& operator>>(char& c)
    {
        c = getchar();
        while (c != EOF && !std::isgraph(c))
        {
            c = getchar();
        }

        return *this;
    }

    FastIO& operator<<(char c)
    {
        return putchar(c), *this;
    }

    FastIO& operator>>(std::integral auto& x)
    {
        char c = getchar();
        bool neg = false;
        while (c != EOF && !std::isdigit(c))
        {
            if (c == '-')
            {
                neg = true;
            }

            c = getchar();
        }

        if (c == EOF)
        {
            return *this;
        }

        x = 0;
        while (std::isdigit(c))
        {
            x = x * 10 + (c - '0');
            c = getchar();
        }

        if (neg)
        {
            x = -x;
        }

        return *this;
    }

    FastIO& operator<<(std::integral auto x)
    {
        using U = std::make_unsigned_t<decltype(x)>;
        U ux = x;

        if constexpr (std::is_signed_v<decltype(x)>)
        {
            if (x < 0)
            {
                putchar('-');
                ux = ~static_cast<U>(x) + 1;
            }
        }

        int sta[25], top = 0;
        do
        {
            sta[top++] = ux % 10;
            ux /= 10;
        } while (ux);

        while (top)
        {
            putchar(sta[--top] + '0');
        }

        return *this;
    }

    FastIO& operator>>(__int128_t& x)
    {
        char c = getchar();
        bool neg = false;
        while (c != EOF && !std::isdigit(c))
        {
            if (c == '-')
            {
                neg = true;
            }

            c = getchar();
        }

        if (c == EOF)
        {
            return *this;
        }

        x = 0;
        while (std::isdigit(c))
        {
            x = x * 10 + (c - '0');
            c = getchar();
        }

        if (neg)
        {
            x = -x;
        }

        return *this;
    }

    FastIO& operator<<(__int128_t x)
    {
        __int128_t ux = x;

        if constexpr (std::is_signed_v<decltype(x)>)
        {
            if (x < 0)
            {
                putchar('-');
                ux = ~static_cast<__int128_t>(x) + 1;
            }
        }

        int sta[45], top = 0;
        do
        {
            sta[top++] = ux % 10;
            ux /= 10;
        } while (ux);

        while (top)
        {
            putchar(sta[--top] + '0');
        }

        return *this;
    }

    FastIO& operator>>(std::floating_point auto& x)
    {
        char c = getchar();
        bool neg = false;

        while (c != EOF && !std::isdigit(c) && c != '.')
        {
            if (c == '-')
            {
                neg = true;
            }

            c = getchar();
        }

        if (c == EOF)
        {
            return *this;
        }

        x = 0;
        while (std::isdigit(c))
        {
            x = x * 10 + (c - '0');
            c = getchar();
        }
        
        if (c == '.')
        {
            c = getchar();

            std::decay_t<decltype(x)> base = 1.0;
            while (std::isdigit(c))
            {
                base *= 10.0;
                x += (c - '0') / base;
                c = getchar();
            }
        }
        
        if (neg)
        {
            x = -x;
        }

        return *this;
    }

    FastIO& operator<<(std::floating_point auto x)
    {
        using T = decltype(x);

        if (std::isnan(x))
        {
            return *this << "NaN";
        }

        if (std::isinf(x))
        {
            return *this << "Inf";
        }

        if (std::signbit(x))
        {
            putchar('-');
            x = -x;
        }

        T rounder = 0.5;
        for (int i = 0; i < prec; ++i)
        {
            rounder /= 10.0;
        }
        x += rounder;

        uint64_t int_part = static_cast<uint64_t>(x);
        *this << int_part;

        if (prec > 0)
        {
            putchar('.');

            T frac_part = x - int_part;
            for (int i = 0; i < prec; ++i)
            {
                frac_part *= 10.0;
                int digit = static_cast<int>(frac_part);
                putchar(digit + '0');
                frac_part -= digit;
            }
        }

        return *this;
    }
} fio;

void solve()
{
    using i128 = __int128_t;
    i128 x, y, k;
    fio >> x >> y >> k;

    i128 cnt = 0;
    while (x > y)
    {
        x /= k;
        ++cnt;
    }

    if (x == y)
    {
        fio << cnt << "\n";
        return;
    }

    for (i128 p = 1, base = 0;; x /= k, ++cnt)
    {
        while (p * (x + 1) <= y)
        {
            p *= k, ++base;
        }

        if (y >= p * x && p - 1 >= y - p * x)
        {
            cnt += base;

            fio << cnt << "\n";
            return;
        }
    }
}

int main()
{
    int t = 1;
    fio >> t;
    while (t--)
    {
        solve();
    }
}

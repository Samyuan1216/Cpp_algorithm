#include <bits/stdc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

// 基本类型别名
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = unsigned __int128;

using f32 = float;
using f64 = double;
using f128 = long double;

// 省略std::
using std::string, std::pair, std::tuple, std::queue, std::stack, std::deque;

// 容器类型 - 一维
using vi32 = std::vector<i32>;
using vu32 = std::vector<u32>;
using vi64 = std::vector<i64>;
using vu64 = std::vector<u64>;
using vf32 = std::vector<f32>;
using vf64 = std::vector<f64>;
using vf128 = std::vector<f128>;
using vb = std::vector<bool>;
using vc = std::vector<char>;
using vs = std::vector<string>;

// 容器类型 - 二维
using v2i32 = std::vector<vi32>;
using v2u32 = std::vector<vu32>;
using v2i64 = std::vector<vi64>;
using v2u64 = std::vector<vu64>;
using v2f32 = std::vector<vf32>;
using v2f64 = std::vector<vf64>;
using v2f128 = std::vector<vf128>;
using v2b = std::vector<vb>;
using v2c = std::vector<vc>;
using v2s = std::vector<vs>;

// 数组类型（固定大小）
template<size_t N>
using ai32 = std::array<i32, N>;
template<size_t N>
using ai64 = std::array<i64, N>;
template<size_t N>
using af32 = std::array<f32, N>;
template<size_t N>
using af64 = std::array<f64, N>;

// 映射类型
template<typename T>
using us = std::unordered_set<T>;
template<typename T1, typename T2>
using um = std::unordered_map<T1, T2>;

// 优先队列
template<typename T, typename F>
using pq = std::priority_queue<T, std::vector<T>, F>;

// 最大最小值
template<typename T>
using lim = std::numeric_limits<T>;

template<u32 N>
class Bigint
{
    static constexpr u32 BASE = 1000000000;
    static constexpr u32 WIDTH = 9;
    
    ai32<N> num{};
    i32 len{1};
    bool neg{};

    void normalize()
    {
        while (len > 1 && num[len - 1] == 0)
        {
            len--;
        }

        if (len == 1 && num[0] == 0)
        {
            neg = false;
        }

        ranges::fill(num.begin() + len, num.end(), 0);
    }

    bool abs_less(const Bigint& rhs) const
    {
        if (len != rhs.len)
        {
            return len < rhs.len;
        }

        for (i32 i = len - 1; i >= 0; i--)
        {
            if (num[i] != rhs.num[i])
            {
                return num[i] < rhs.num[i];
            }
        }

        return false;
    }
public:
    Bigint() = default;
    Bigint(const Bigint &x) = default;
    Bigint(Bigint&&) = default;

    template<std::integral T>
    Bigint(T x)
    {
        *this = x;
    }

    Bigint(const string &str)
    {
        *this = str;
    }

    Bigint& operator=(const Bigint &rhs) = default;
    Bigint& operator=(Bigint&&) = default;

    template<std::integral T>
    Bigint& operator=(T rhs)
    {
        ranges::fill(num, 0);

        neg = false;
        if constexpr (std::is_signed_v<T>)
        {
            if (rhs < 0)
            {
                neg = true;
                rhs = -rhs;
            }
        }

        if (rhs == 0)
        {
            len = 1;
            num[0] = 0;
            return *this;
        }

        len = 0;
        while (rhs > 0)
        {
            num[len++] = rhs % BASE;
            rhs /= BASE;
        }

        return *this;
    }

    Bigint& operator=(const string& rhs)
    {
        ranges::fill(num, 0);

        i32 start = 0;
        neg = false;
        
        if (rhs[0] == '-')
        {
            neg = true;
            start = 1;
        }
        else if (rhs[0] == '+')
        {
            start = 1;
        }

        i32 str_len = rhs.length() - start;
        len = (str_len + WIDTH - 1) / WIDTH;
        
        for (i32 i = 0; i < len; i++)
        {
            i32 end = rhs.length() - i * WIDTH;
            i32 begin = std::max(start, end - (i32)WIDTH);
            
            num[i] = 0;
            for (i32 j = begin; j < end; j++)
            {
                num[i] = num[i] * 10 + (rhs[j] - '0');
            }
        }

        normalize();
        return *this;
    }

    bool operator==(const Bigint& rhs) const
    {
        if (neg != rhs.neg || len != rhs.len)
        {
            return false;
        }

        for (i32 i: views::iota(0, len))
        {
            if (num[i] != rhs.num[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Bigint& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const Bigint& rhs) const
    {
        if (neg != rhs.neg)
        {
            return neg;
        }

        if (len != rhs.len)
        {
            return neg ? len > rhs.len : len < rhs.len;
        }

        for (i32 i = len - 1; i >= 0; i--)
        {
            if (num[i] != rhs.num[i])
            {
                return neg ? num[i] > rhs.num[i] : num[i] < rhs.num[i];
            }
        }

        return false;
    }

    bool operator<=(const Bigint& rhs) const
    {
        return *this < rhs || *this == rhs;
    }

    bool operator>(const Bigint& rhs) const
    {
        return !(*this <= rhs);
    }

    bool operator>=(const Bigint& rhs) const
    {
        return !(*this < rhs);
    }

    Bigint operator-() const
    {
        Bigint res(*this);
        res.neg = !res.neg;
        res.normalize();
        return res;
    }

    Bigint operator+(const Bigint& rhs) const
    {
        if (neg != rhs.neg)
        {
            return neg ? rhs - (-*this) : *this - (-rhs);
        }

        Bigint res;
        res.neg = neg;
        res.len = std::max(len, rhs.len);

        u64 carry = 0;
        for (i32 i = 0; i < res.len; i++)
        {
            u64 sum = (u64)num[i] + rhs.num[i] + carry;
            res.num[i] = sum % BASE;
            carry = sum / BASE;
        }

        if (carry > 0)
        {
            res.num[res.len++] = carry;
        }

        res.normalize();
        return res;
    }

    Bigint operator-(const Bigint& rhs) const
    {
        if (neg != rhs.neg)
        {
            return *this + (-rhs);
        }

        Bigint x(*this), y(rhs);
        bool result_neg = neg;
        
        if (x.abs_less(y))
        {
            std::swap(x, y);
            result_neg = !result_neg;
        }

        for (i32 i = 0; i < x.len; i++)
        {
            x.num[i] -= y.num[i];
            
            if (x.num[i] < 0)
            {
                x.num[i] += BASE;
                x.num[i + 1]--;
            }
        }

        x.neg = result_neg;
        x.normalize();
        return x;
    }

    Bigint operator*(const Bigint& rhs) const
    {
        Bigint res;
        res.len = len + rhs.len;
        res.neg = (neg != rhs.neg);

        for (i32 i = 0; i < len; i++)
        {
            u64 carry = 0;
            for (i32 j = 0; j < rhs.len; j++)
            {
                u64 prod = (u64)num[i] * rhs.num[j] + res.num[i + j] + carry;
                res.num[i + j] = prod % BASE;
                carry = prod / BASE;
            }
            if (carry > 0)
            {
                res.num[i + rhs.len] += carry;
            }
        }

        res.normalize();
        return res;
    }

    Bigint operator/(const Bigint& rhs) const
    {
        if (abs_less(rhs))
        {
            return Bigint(0);
        }

        Bigint res;
        res.neg = (neg != rhs.neg);
        res.len = len;
        
        Bigint current;
        current.len = 1;
        current.num[0] = 0;
        
        Bigint abs_rhs = rhs;
        abs_rhs.neg = false;
        
        for (i32 i = len - 1; i >= 0; i--)
        {
            for (i32 j = current.len; j > 0; j--)
            {
                current.num[j] = current.num[j - 1];
            }
            current.num[0] = num[i];
            current.len++;
            current.normalize();
            
            i32 left = 0, right = BASE - 1;
            while (left <= right)
            {
                i32 mid = left + (right - left) / 2;
                
                Bigint temp = abs_rhs;
                u64 carry = 0;
                for (i32 k = 0; k < temp.len; k++)
                {
                    u64 prod = (u64)temp.num[k] * mid + carry;
                    temp.num[k] = prod % BASE;
                    carry = prod / BASE;
                }

                if (carry > 0)
                {
                    temp.num[temp.len++] = carry;
                }

                temp.normalize();
                
                if (current.abs_less(temp))
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            
            res.num[i] = right;
            
            Bigint sub_val = abs_rhs;
            u64 carry = 0;
            for (i32 k = 0; k < sub_val.len; k++)
            {
                u64 prod = (u64)sub_val.num[k] * right + carry;
                sub_val.num[k] = prod % BASE;
                carry = prod / BASE;
            }
            if (carry > 0)
            {
                sub_val.num[sub_val.len++] = carry;
            }
            sub_val.normalize();
            
            current = current - sub_val;
        }

        res.normalize();
        return res;
    }

    Bigint operator%(const Bigint& rhs) const
    {
        return *this - (*this / rhs) * rhs;
    }

    string to_string() const
    {
        if (len == 1 && num[0] == 0)
        {
            return "0";
        }
        
        string res;
        if (neg)
        {
            res += '-';
        }
        
        res += std::to_string(num[len - 1]);
        
        for (i32 i = len - 2; i >= 0; i--)
        {
            string block = std::to_string(num[i]);
            res += string(WIDTH - block.length(), '0') + block;
        }
        
        return res;
    }

    friend std::istream& operator>>(std::istream &lhs, Bigint &rhs)
    {
        string str;
        lhs >> str;
        rhs = str;
        return lhs;
    }

    friend std::ostream& operator<<(std::ostream& lhs, const Bigint& rhs)
    {
        lhs << rhs.to_string();
        return lhs;
    }
};

void solve()
{
    i32 n;
    std::cin >> n;

    Bigint<10000> a(1), b(1), cur;
    for (i32 i: views::iota(1, 2 * n + 1))
    {
        cur = i;
        a = a * cur;

        if (i <= n)
        {
            b = b * cur;
        }
    }

    std::cout << a / (b * b) / (Bigint<10000>(n + 1)) << "\n";
}

i32 main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    i32 t = 1;
    while (t--)
    {
        solve();
    }
}
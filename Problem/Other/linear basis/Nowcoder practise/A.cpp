// https://ac.nowcoder.com/acm/contest/128450/A

#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

struct Basis
{
    using u64 = unsigned long long;

    std::array<u64, 64> p{};
    bool zero = false;
    int cnt = 0;

    void clear()
    {
        p.fill(0);
        zero = false;
        cnt = 0;
    }

    bool empty() const
    {
        return cnt == 0 && !zero;
    }

    // 返回线性基秩，若秩为 r，那么不同的可表示异或结果数量恰好为 2^r
    int rank() const
    {
        return cnt;
    }

    // 插入 x；如果 x 线性独立，返回 true
    bool insert(u64 x)
    {
        for (int i = 63; i >= 0; --i)
        {
            if (((x >> i) & 1) == 0) continue;

            if (p[i] == 0)
            {
                p[i] = x;
                ++cnt;
                return true;
            }

            x ^= p[i];
        }

        zero = true;
        return false;
    }

    // 判断 x 能否由已有数字异或得到
    bool contains(u64 x) const
    {
        for (int i = 63; i >= 0; --i)
        {
            if (((x >> i) & 1) == 0) continue;
            if (p[i] == 0) return false;
            x ^= p[i];
        }
        return true;
    }

    // x 与某个可表示值异或后的最大值
    u64 max_xor(u64 x = 0) const
    {
        for (int i = 63; i >= 0; --i)
        {
            x = std::max(x, x ^ p[i]);
        }
        return x;
    }

    // x 与某个可表示值异或后的最小值
    u64 min_xor(u64 x) const
    {
        for (int i = 63; i >= 0; --i)
        {
            x = std::min(x, x ^ p[i]);
        }
        return x;
    }

    // 转为简化线性基，方便求第 k 小和最小非零值
    void reduce()
    {
        for (int i = 0; i < 64; ++i)
        {
            if (p[i] == 0) continue;

            for (int j = i + 1; j < 64; ++j)
            {
                if ((p[j] >> i) & 1)
                {
                    p[j] ^= p[i];
                }
            }
        }
    }

    // 第 k 小的不同异或值，k 从 0 开始；越界返回 nullopt 需要先运行reduce
    std::optional<u64> kth(u64 k) const
    {
        if (cnt < 64)
        {
            const u64 total = 1ULL << cnt;

            // zero == true：
            // 非空子集结果数量为 2^cnt
            //
            // zero == false：
            // 非空子集结果排除 0，数量为 2^cnt - 1
            const u64 valid_count = zero ? total : total - 1;

            if (k >= valid_count)
            {
                return std::nullopt;
            }
        }
        else
        {
            // cnt == 64 时，完整线性空间有 2^64 个值。
            // zero == true：所有 u64 下标都合法。
            //
            // zero == false：排除 0 后有 2^64 - 1 个值，
            // 合法下标为 0 ... UINT64_MAX - 1。
            if (!zero && k == std::numeric_limits<u64>::max())
            {
                return std::nullopt;
            }
        }

        // 如果非空子集不能得到 0，
        // 就跳过完整线性空间中的第 0 个值：0。
        if (!zero)
        {
            ++k;
        }

        u64 ans = 0;
        int bit = 0;

        for (int i = 0; i < 64; ++i)
        {
            if (p[i] == 0) continue;
            if ((k >> bit) & 1) ans ^= p[i];
            ++bit;
        }

        return ans;
    }

    // 最小非零异或值；空线性基返回 nullopt 需要先运行reduce
    std::optional<u64> min_nonzero() const
    {
        if (cnt == 0) return std::nullopt;

        for (int i = 0; i < 64; ++i)
        {
            if (p[i] != 0) return p[i];
        }

        return std::nullopt;
    }

    // 最小不能表示的非负整数；满秩时数学答案为 2^64，返回 nullopt
    std::optional<u64> mex() const
    {
        for (int i = 0; i < 64; ++i)
        {
            if (p[i] == 0) return 1ULL << i;
        }
        return std::nullopt;
    }

    // 合并另一个线性基
    void merge(const Basis& other)
    {
        zero |= other.zero;
        for (u64 x: other.p)
        {
            if (x != 0) insert(x);
        }
    }
};

void solve()
{
    int n;
    std::cin >> n;

    Basis lb;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        lb.insert(x);
    }

    int q;
    std::cin >> q;

    while (q--)
    {
        int x, y;
        std::cin >> x >> y;
        std::cout << (lb.contains(x ^ y)? "YES\n": "NO\n");
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}
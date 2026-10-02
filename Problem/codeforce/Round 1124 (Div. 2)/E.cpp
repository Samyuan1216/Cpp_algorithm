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

void solve()
{
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<int> pre(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] ^ arr[i - 1];
    }

    auto build = [](const std::vector<int> &a, std::vector<int> &left, std::vector<int> &right) -> int
    {
        int n = a.size();
        left.assign(n, -1);
        right.assign(n, -1);
    
        std::vector<int> stk;
        for (int i = 0; i < n; i++)
        {
            int last = -1;
    
            while (!stk.empty() && a[stk.back()] < a[i])
            {
                last = stk.back();
                stk.pop_back();
            }
    
            if (!stk.empty())
            {
                right[stk.back()] = i;
            }
    
            if (last != -1)
            {
                left[i] = last;
            }
    
            stk.push_back(i);
        }
    
        return (stk.empty()? -1: stk.front());
    };

    std::vector<int> left(n), right(n);
    int root = build(arr, left, right);

    std::vector<int> l(n), r(n), size(n, 1);
    [&](this auto &&self, int u) -> void
    {
        l[u] = r[u] = u;
        if (left[u] != -1)
        {
            self(left[u]);

            l[u] = l[left[u]];
            size[u] += size[left[u]];
        }

        if (right[u] != -1)
        {
            self(right[u]);

            r[u] = r[right[u]];
            size[u] += size[right[u]];
        }
    } (root);

    std::vector<int> cnt((1 << 18) + 10);
    auto check = [&](int m) -> bool
    {
        std::vector<int> s(n + 1);
        for (int i = 0; i <= n; ++i)
        {
            s[i] = pre[i] & m;
        }

        bool find = false;
        auto compute =[&](int u) -> void
        {
            int lsize = (left[u] != -1? size[left[u]]: 0), rsize = (right[u] != -1? size[right[u]]: 0);
            if ((arr[u] & m) != m)
            {
                return;
            }

            if (lsize >= rsize)
            {
                ++cnt[s[l[u]]];
                --cnt[s[u]];

                if (cnt[s[u + 1] ^ m] > 0)
                {
                    find = true;
                }

                ++cnt[s[u]];

                for (int y = u + 1; y <= r[u] && !find; ++y)
                {
                    if (cnt[s[y + 1] ^ m] > 0)
                    {
                        find = true;
                    }
                }

                --cnt[s[l[u]]];
            }
            else
            {
                if (cnt[s[u] ^ m] > 0)
                {
                    find = true;
                }

                ++cnt[s[u + 1]];
                for (int x = l[u] - 1; x <= u - 2 && !find; ++x)
                {
                    if (cnt[s[x + 1] ^ m] > 0)
                    {
                        find = true;
                    }
                }

                --cnt[s[u + 1]];
            }
        };

        [&](this auto &&self, int u) -> void
        {
            if (find)
            {
                return;
            }

            int lsize = (left[u] != -1? size[left[u]]: 0), rsize = (right[u] != -1? size[right[u]]: 0);
            int small = (lsize >= rsize? right[u]: left[u]), big = (lsize >= rsize? left[u]: right[u]);

            if (small != -1)
            {
                self(small);

                for (int i = l[small]; i <= r[small]; ++i)
                {
                    --cnt[s[i + 1]];
                }
            }

            if (big != -1)
            {
                self(big);
            }

            compute(u);

            ++cnt[s[u + 1]];
            if (small != -1)
            {
                for (int i = l[small]; i <= r[small]; ++i)
                {
                    ++cnt[s[i + 1]];
                }
            }
        } (root);

        [&](this auto &&self, int u) -> void
        {
            if (u == -1)
            {
                return;
            }

            cnt[s[u + 1]] = cnt[s[u]] = 0;
            self(left[u]), self(right[u]);
        } (root);

        return find;
    };

    int ans = 0;
    for (int p = 17; p >= 0; --p)
    {
        int mask = ans | (1 << p);
        if (check(mask))
        {
            ans = mask;
        }
    }

    std::cout << ans << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}

#include <bits/stdc++.h>

int n, x, ans;

int gcd(int a, int b)
{
    return (b == 0? a: gcd(b, a % b));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n;
    while (n--)
    {
        std::cin >> x;
        ans = gcd(std::abs(x), ans);
    }
    
    std::cout << ans << "\n";
}
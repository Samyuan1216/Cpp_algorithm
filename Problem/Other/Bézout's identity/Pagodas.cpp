// https://acm.hdu.edu.cn/showproblem.php?pid=5512

#include <bits/stdc++.h>

int t, n, a, b;

int gcd(int a, int b)
{
    return (b == 0? a: gcd(b, a % b));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> t;
    for (int i = 1; i <= t; i++)
    {
        std::cin >> n >> a >> b;
        std::cout << "Case #" << i << ": " << ((n / gcd(a, b)) & 1? "Yuwgna\n": "Iaka\n");
    }
}
#include <bits/stdc++.h>

const int MAXN = 101;
const int BIT = 60;

std::vector<long long> arr(MAXN);
int n;

// 普通消元
std::vector<long long> basis1(BIT + 1);
bool zero1;

// 线性基里插入num，如果线性基增加了返回true，否则返回false
bool insert(long long num)
{
    for (int i = BIT; i >= 0; i--)
    {
        if ((num >> i) == 1)
        {
            if (basis1[i] == 0)
            {
                basis1[i] = num;
                return true;
            }
            num ^= basis1[i];
        }
    }
    return false;
}

void compute1()
{
    zero1 = false;
    for (int i = 1; i <= n; i++)
    {
        if (!insert(arr[i]))
        {
            zero1 = true;
        }
    }
}

// 高斯消元
std::vector<long long> basis2(MAXN);
int len;
bool zero2;

void compute2()
{
    len = 1;
    for (long long i = BIT; i >= 0; i--)
    {
        for (int j = len; j <= n; j++)
        {
            if ((basis2[j] & (1LL << i)) != 0)
            {
                std::swap(basis2[j], basis2[len]);
                break;
            }
        }
        if ((basis2[len] & (1LL << i)) != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j != len && (basis2[j] & (1LL << i)) != 0)
                {
                    basis2[j] ^= basis2[len];
                }
            }
            len++;
        }
    }
    len--;
    zero2 = len != n;
}

// 当前来到i位置
// 之前是否选择过数字用pick表示
// 之前做的决定形成的异或和是path
// 当前i位置的数字要或者不要全决策
// 收集所有可能的异或和
void dfs(const std::vector<long long>& nums, int cnt, int i, bool pick, long long path, std::unordered_set<long long>& st)
{
    if (i > cnt)
    {
        if (pick)
        {
            st.insert(path);
        }
    }
    else
    {
        dfs(nums, cnt, i + 1, pick, path, st);
        dfs(nums, cnt, i + 1, true, path ^ nums[i], st);
    }
}

// nums中1~cnt的范围
// 所有可能的异或和打印出来
// 要求去重并且至少选择一个数字
void printXor(const std::vector<long long>& nums, int cnt)
{
    std::unordered_set<long long> st;
    dfs(nums, cnt, 1, false, 0, st);
    std::cout << "至少选择一个数字所有可能的异或和:" << std::endl;
    for (long long s : st)
    {
        std::cout << s << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    // 课上讲的普通消元，例子1
    // 12, 9, 14, 11
    std::cout << "例子1" << std::endl;
    std::fill(basis1.begin(), basis1.end(), 0);
    arr[1] = 12;
    arr[2] = 9;
    arr[3] = 14;
    arr[4] = 11;
    n = 4;
    std::cout << "原始数组得到的异或结果如下" << std::endl;
    printXor(arr, n);

    std::cout << "===========================" << std::endl;
    std::cout << "普通消元得到的线性基 : " << std::endl;
    compute1();
    std::vector<long long> b1(MAXN);
    int s1 = 0;
    for (int i = BIT; i >= 0; i--)
    {
        if (basis1[i] != 0)
        {
            std::cout << basis1[i] << " ";
            b1[++s1] = basis1[i];
        }
    }
    std::cout << std::endl;
    std::cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << std::endl;
    std::cout << "普通消元得到的异或结果如下" << std::endl;
    printXor(b1, s1);
    std::cout << "===========================" << std::endl;

    std::cout << std::endl << std::endl;

    // 课上讲的普通消元，例子2
    // 2, 5, 11, 6
    std::cout << "例子2" << std::endl;
    std::fill(basis1.begin(), basis1.end(), 0);
    arr[1] = 2;
    arr[2] = 5;
    arr[3] = 11;
    arr[4] = 6;
    n = 4;
    std::cout << "原始数组得到的异或结果如下" << std::endl;
    printXor(arr, n);
    std::cout << "===========================" << std::endl;
    std::cout << "普通消元得到的线性基 : " << std::endl;
    compute1();
    std::vector<long long> b2(MAXN);
    int s2 = 0;
    for (int i = BIT; i >= 0; i--)
    {
        if (basis1[i] != 0)
        {
            std::cout << basis1[i] << " ";
            b2[++s2] = basis1[i];
        }
    }
    std::cout << std::endl;
    std::cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << std::endl;
    std::cout << "普通消元得到的异或结果如下" << std::endl;
    printXor(b2, s2);
    std::cout << "===========================" << std::endl;

    std::cout << std::endl << std::endl;

    // 课上讲的高斯消元的例子，例子3
    // 6, 37, 35, 33
    std::cout << "例子3" << std::endl;
    std::fill(basis2.begin(), basis2.end(), 0);
    arr[1] = basis2[1] = 6;
    arr[2] = basis2[2] = 37;
    arr[3] = basis2[3] = 35;
    arr[4] = basis2[4] = 33;
    n = 4;
    std::cout << "原始数组得到的异或结果如下" << std::endl;
    printXor(arr, n);
    std::cout << "===========================" << std::endl;
    std::cout << "高斯消元得到的线性基 : " << std::endl;
    compute2();
    for (int i = 1; i <= len; i++)
    {
        std::cout << basis2[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "是否能异或出0 : " << (zero2 ? "true" : "false") << std::endl;
    std::cout << "高斯消元得到的异或结果如下" << std::endl;
    printXor(basis2, len);
    std::cout << "===========================" << std::endl;

    std::cout << std::endl << std::endl;

    // 课上讲的高斯消元的例子，例子4
    std::cout << "例子4" << std::endl;
    std::fill(basis1.begin(), basis1.end(), 0);
    std::fill(basis2.begin(), basis2.end(), 0);
    arr[1] = basis2[1] = 7;
    arr[2] = basis2[2] = 10;
    arr[3] = basis2[3] = 4;
    n = 3;
    std::cout << "原始数组得到的异或结果如下" << std::endl;
    printXor(arr, n);
    std::cout << "===========================" << std::endl;
    std::cout << "普通消元" << std::endl;
    compute1();
    for (int i = BIT; i >= 0; i--)
    {
        if (basis1[i] != 0)
        {
            std::cout << basis1[i] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "是否能异或出0 : " << (zero1 ? "true" : "false") << std::endl;

    std::cout << "===========================" << std::endl;

    std::cout << "高斯消元" << std::endl;
    compute2();
    for (int i = 1; i <= len; i++)
    {
        std::cout << basis2[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "是否能异或出0 : " << (zero2 ? "true" : "false") << std::endl;

    return 0;
}
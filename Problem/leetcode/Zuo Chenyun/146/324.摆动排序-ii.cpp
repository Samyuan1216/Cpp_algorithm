/*
 * @lc app=leetcode.cn id=324 lang=cpp
 *
 * [324] 摆动排序 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void wiggleSort(vector<int>& nums)
    {
        int n = nums.size();
        
        randomizedSelect(nums, n, n / 2);
        
        if ((n & 1) == 0)
        {
            shuffle(nums, 0, n - 1);
            std::reverse(nums.begin(), nums.end());
        }
        else
        {
            shuffle(nums, 1, n - 1);
        }
    }

    int first, last;
    
    void partition(vector<int>& arr, int l, int r, int x)
    {
        first = l;
        last = r;
        int i = l;
        while (i <= last)
        {
            if (arr[i] == x)
            {
                i++;
            }
            else if (arr[i] < x)
            {
                swap(arr[first++], arr[i++]);
            }
            else
            {
                swap(arr[i], arr[last--]);
            }
        }
    }
    
    int randomizedSelect(vector<int>& arr, int n, int i)
    {
        int ans = 0;
        int l = 0, r = n - 1;
        random_device rd;
        mt19937 gen(rd());
        
        while (l <= r)
        {
            uniform_int_distribution<> dis(l, r);
            int pivot_idx = dis(gen);
            partition(arr, l, r, arr[pivot_idx]);
            
            if (i < first)
            {
                r = first - 1;
            }
            else if (i > last)
            {
                l = last + 1;
            }
            else
            {
                ans = arr[i];
                break;
            }
        }
        return ans;
    }
    
    int to(int i, int l, int r)
    {
        if (i <= (l + r) >> 1)
        {
            return i + (i - l + 1);
        }
        else
        {
            return i - (r - i + 1);
        }
    }
    
    void rotate(vector<int>& arr, int l, int m, int r)
    {
        std::reverse(arr.begin() + l, arr.begin() + m + 1);
        std::reverse(arr.begin() + m + 1, arr.begin() + r + 1);
        std::reverse(arr.begin() + l, arr.begin() + r + 1);
    }
    
    void circle(vector<int>& arr, int l, int r, int i, vector<int>& start)
    {
        for (int j = 1; j <= i; j++)
        {
            int init = l + start[j] - 1;
            int cur = init;
            int next = to(cur, l, r);
            int curv = arr[cur];
            while (next != init)
            {
                int nextv = arr[next];
                arr[next] = curv;
                curv = nextv;
                cur = next;
                next = to(cur, l, r);
            }
            arr[init] = curv;
        }
    }
    
    void build(int n, vector<int>& start, vector<int>& split, int& size)
    {
        size = 0;
        for (int s = 1, p = 2; p <= n; s *= 3, p = s * 3 - 1)
        {
            start[++size] = s;
            split[size] = p;
        }
    }
    
    void shuffle(vector<int>& arr, int l, int r)
    {
        constexpr int MAXN = 20;
        vector<int> start(MAXN);
        vector<int> split(MAXN);
        int size = 0;
        
        int n = r - l + 1;
        build(n, start, split, size);
        
        for (int i = size, m; n > 0;)
        {
            if (split[i] <= n)
            {
                m = (l + r) / 2;
                rotate(arr, l + split[i] / 2, m, m + split[i] / 2);
                circle(arr, l, l + split[i] - 1, i, start);
                l += split[i];
                n -= split[i];
            }
            else
            {
                i--;
            }
        }
    }
};
// @lc code=end


#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
vector<int> nums(MAXN), eds(MAXN), rights(MAXN);
int n = 0, k = 0, e = 0;

int main()
{
    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (e == 0 || nums[i] <= eds[e - 1])
        {
            eds[e++] = nums[i];
            rights[i] = e;
        }
        else
        {
            int cur = 0;
            for (int l = 0, r = e - 1, m = 0; l <= r;)
            {
                m = l + ((r - l) >> 1);
                if (nums[i] > eds[m])
                {
                    cur = m;
                    r = m - 1;
                }
                else
                {
                    l = m + 1;
                }
            }

            eds[cur] = nums[i];
            rights[i] = cur + 1;
        }
    }

    e = 0;
    int ans = 0;
    for (int i = 0, j = k, left = 0; j < n; i++, j++)
    {
        if (e == 0 || nums[j] >= eds[e - 1])
        {
            left = e;
        }
        else
        {
            int cur = 0;
            for (int l = 0, r = e - 1, m = 0; l <= r;)
            {
                m = l + ((r - l) >> 1);
                if (nums[j] < eds[m])
                {
                    cur = m;
                    r = m - 1;
                }
                else
                {
                    l = m + 1;
                }
            }

            left = cur;
        }

        ans = max(ans, left + k + rights[j]);

        if (e == 0 || nums[i] >= eds[e - 1])
        {
            eds[e++] = nums[i];
        }
        else
        {
            int cur = 0;
            for (int l = 0, r = e - 1, m = 0; l <= r;)
            {
                m = l + ((r - l) >> 1);
                if (nums[i] < eds[m])
                {
                    cur = m;
                    r = m - 1;
                }
                else
                {
                    l = m + 1;
                }
            }

            eds[cur] = nums[i];
        }
    }

    ans = max(ans, e + k);

    cout << ans << endl;
}
/*
 * 将高为 H，宽为 W 的棋盘分割成若干个宽和高分别为 1 和 2 的长方形，有多少种方案。
 */
#include <iostream>
#include <cstring>
#include <limits.h>
using namespace std;
typedef long long ll;
const int inf = INT_MAX;
int N, W;
ll f[15][3000];
bool check(ll x)
{
    int temp[12];
    memset(temp, 0, sizeof(temp));
    for (int i = 0; i < W; i++)
    {
        temp[i] = x & 1;
        x = x >> 1;
    }
    int num = 0;
    for (int i = 0; i < W; i++)
    {
        if (temp[i] == 0)
            num++;
        else
        {
            if (num % 2 == 1)
            {
                return false;
            }
            else
            {
                num = 0;
            }
        }
    }
    if (num & 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}
int main()
{
    cin >> N >> W;
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (size_t i = 1; i <= N; i++)
    {
        for (size_t S1 = 0; S1 < (1 << W); S1++)
        {
            for (size_t S2 = 0; S2 < (1 << W); S2++)
            {
                if ((S1 & S2) != 0)
                {
                    continue;
                }
                if (!check(S1 | S2))
                {
                    continue;
                }
                f[i][S1] += f[i - 1][S2];
            }
        }
    }
    cout << f[N][0] << endl;
}
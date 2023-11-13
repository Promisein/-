#include <iostream>
#include <vector>
#include <cstring>
typedef long long ll;
using namespace std;
const ll mod = 998244353;
const int maxn = 1e6 + 100;

ll sum[maxn], f[maxn]; // 前缀和， 每一个台阶的步数
ll n, m, k;            // n级台阶，最多迈出k级台阶

ll solution()
{
    for (int i = 1; i <= k; i++)
    {
        if (f[i] != -1)
        {
            f[i] = sum[i - 1] % mod;
            sum[i] = sum[i - 1] + f[i];
        }
        else
        {
            sum[i] = sum[i - 1];
        }
    }

    for (int i = k + 1; i <= n; i++)
    {
        if (f[i] == -1)
        {
            sum[i] = sum[i - 1];
        }
        else
        {
            f[i] = (sum[i - 1] - sum[i - 1 - k]) % mod;
            sum[i] = sum[i - 1] + f[i];
        }
    }
    return f[n];
}

int main()
{
    memset(sum, 0, sizeof(sum));
    memset(f, 0, sizeof(f));
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++)
    {
        ll temp;
        cin >> temp;
        f[temp] = -1; // 表示不可行走
    }
    f[0] = 1;
    sum[0] = 1;
    cout << solution() % mod << endl;
    return 0;
}
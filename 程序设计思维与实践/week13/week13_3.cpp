#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 100;
const int inf = 1e6 + 100;
typedef long long ll;

ll a[3][maxn];
ll dp[maxn][3];
ll mymin(ll a, ll b, ll c)
{
    return min(min(a, b), min(b, c));
}
int main()
{
    ll n;
    cin >> n;
    for (ll j = 0; j <= 2; j++)
    {
        for (ll i = 1; i <= n; i++)
        {
            cin >> a[j][i];
        }
    }

    for (ll j = 0; j <= 2; j++)
    {
        for (ll i = 0; i < n; i++)
        {
            dp[i][j] = inf;
        }
    }
    dp[1][0] = dp[1][1] = dp[1][2] = 0;
    for (ll i = 2; i <= n; i++)
    {
        dp[i][0] = mymin(dp[i - 1][0] + abs(a[0][i] - a[0][i - 1]),
                         dp[i - 1][1] + abs(a[0][i] - a[1][i - 1]),
                         dp[i - 1][2] + abs(a[0][i] - a[2][i - 1]));

        dp[i][1] = mymin(dp[i - 1][0] + abs(a[1][i] - a[0][i - 1]),
                         dp[i - 1][1] + abs(a[1][i] - a[1][i - 1]),
                         dp[i - 1][2] + abs(a[1][i] - a[2][i - 1]));

        dp[i][2] = mymin(dp[i - 1][0] + abs(a[2][i] - a[0][i - 1]),
                         dp[i - 1][1] + abs(a[2][i] - a[1][i - 1]),
                         dp[i - 1][2] + abs(a[2][i] - a[2][i - 1]));

        // dp[i][0] = min(min(dp[i - 1][0] + abs(a[0][i] - a[0][i - 1]),
        //                    dp[i - 1][1] + abs(a[0][i] - a[1][i - 1])),
        //                    dp[i - 1][2] + abs(a[0][i] - a[2][i - 1]));

        // dp[i][1] = min(min(dp[i - 1][0] + abs(a[1][i] - a[0][i - 1]),
        //                    dp[i - 1][1] + abs(a[1][i] - a[1][i - 1])),
        //                    dp[i - 1][2] + abs(a[1][i] - a[2][i - 1]));

        // dp[i][2] = min(min(dp[i - 1][0] + abs(a[2][i] - a[0][i - 1]),
        //                    dp[i - 1][1] + abs(a[2][i] - a[1][i - 1])),
        //                    dp[i - 1][2] + abs(a[2][i] - a[2][i - 1]));
    }
    cout << min(min(dp[n][0], dp[n][1]), min(dp[n][1], dp[n][2])) << endl;
    return 0;
}

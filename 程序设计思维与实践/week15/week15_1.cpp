#include <iostream>
#include <cstring>
#include <limits.h>
#define inf INT_MAX
using namespace std;
typedef long long ll;
const int maxn = 210;
int N;
ll arr[maxn];
ll MIN[maxn][maxn], MAX[maxn][maxn];
ll sum[maxn];
void getAns()
{
    ll minAns = inf, maxAns = 0;
    for (int i = 1; i <= N; i++)
    {
        minAns = min(minAns, MIN[i][i + N - 1]);
        maxAns = max(maxAns, MAX[i][i + N - 1]);
    }
    cout << minAns << endl;
    cout << maxAns << endl;
}
int main()
{

    cin >> N;
    memset(MIN, 0x3f, sizeof(MIN));
    memset(MAX, 0, sizeof(MAX));
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        arr[N + i] = arr[i];
    }
    for (int i = 0; i < maxn; i++)
    {
        MIN[i][i] = 0;
    }
    // 计算前缀和
    for (int i = 1; i <= 2 * N; i++)
    {
        sum[i] = sum[i - 1] + arr[i];
    }

    // DP
    for (int len = 2; len <= 2 * N; len++)
    {
        for (size_t i = 1; i < 2 * N - len + 1; i++)
        {
            int l = i, r = i + len - 1;
            for (int k = l; k < r; k++)
            {
                MIN[l][r] = min(MIN[l][r], sum[r] - sum[l - 1] + MIN[l][k] + MIN[k + 1][r]);
                MAX[l][r] = max(MAX[l][r], sum[r] - sum[l - 1] + MAX[l][k] + MAX[k + 1][r]);
            }
        }
    }

    getAns();

    return 0;
}
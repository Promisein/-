#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n;
typedef long long ll;
ll m;
const int maxn = 1e6 + 100;
ll arr[maxn], sum[maxn];
void solution()
{
    ll ans = 0;
    deque<ll> q;
    q.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        while (!q.empty() && sum[q.back()] > sum[i])
        {
            q.pop_back();
        }
        q.push_back(i);
        while (!q.empty() && i - m > q.front())
        {
            q.pop_front();
        }
        ans = max(ans, sum[i] - sum[q.front()]);
    }
    cout << ans << endl;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // 计算前缀和
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + arr[i];
    }
    solution();
    return 0;
}

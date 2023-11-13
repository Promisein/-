#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1010;
ll n, m;
ll w[N],v[N];
ll res;

// 深度优先搜索函数
void dfs(ll u, ll s, ll value)
{ 
    // 如果搜索到最后一层，更新最大值
    if (u == n)
    {
        res = max(res, value);
        return;
    }

    // 不选第u + 1个物品
    dfs(u + 1, s, value);
    // 选第u + 1个物品
    if (s + w[u + 1] <= m) dfs(u + 1, s + w[u + 1], value + v[u + 1]);
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++ ) cin >> w[i] >> v[i];

    // 搜索所有方案
    dfs(0, 0, 0);

    cout << res << endl;

    return 0;
}

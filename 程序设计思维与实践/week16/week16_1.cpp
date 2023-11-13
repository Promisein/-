/*
 * 求树的直径数量以及直径长度
 */
#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;
const int maxn = 1e5 + 10;
int res, num; // 记录长度和直径数量
vector<int> Edge[maxn];
int fa[maxn];
int dp[maxn], deep[maxn];
void DFS(int u, int p)
{
    bool ifleaf = true;
    dp[u] = 1;
    for (int j = 0; j < (int)Edge[u].size(); j++)
    {
        if (Edge[u][j] != p)
        {
            ifleaf = false;
            DFS(Edge[u][j], u);
            if (deep[u] + deep[Edge[u][j]] + 1 > res)
            {
                res = deep[u] + deep[Edge[u][j]] + 1;
                num = dp[u] * dp[Edge[u][j]];
            }
            else
            {
                if (deep[u] + deep[Edge[u][j]] + 1 == res)
                {

                    num += dp[u] * dp[Edge[u][j]];
                }
            }
            if (deep[Edge[u][j]] + 1 > deep[u])
            {
                deep[u] = deep[Edge[u][j]] + 1;
                dp[u] = dp[Edge[u][j]];
            }
            else
            {
                if (deep[Edge[u][j]] + 1 == deep[u])
                    dp[u] += dp[Edge[u][j]];
            }
        }
    }
}
void Solution()
{
    // cout << 666 << endl;
    DFS(1, -1);
    cout << res << " " << num << endl;
}
int main()
{
    int n;
    cin >> n;
    Sleep(10000);
    cout << "666" << endl;
    for (size_t u = 0; u < n - 1; u++)
    {
        int from, to;
        cin >> from >> to;
        Edge[from].push_back(to);
        Edge[to].push_back(from);
    }
    Solution();
    return 0;
}
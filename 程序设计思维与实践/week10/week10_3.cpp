#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
const int maxn = 1010;
const int inf = 10000000000;
vector<pair<int, int>> Edge[maxn];
int dis[maxn],
    vis[maxn],
    cnt[maxn]; // 表示从源点出发到结点i的最短路径上经过的边数
int n, m;
void add(int from, int to, int weight)
{
    // from + w >= to
    // to - from <= w
    Edge[from].push_back(make_pair(to, weight));
}
void output()
{
    for (int i = 1; i <= n; i++)
    {
        cout << i << " -> ";
        for (auto j : Edge[i])
        {
            cout << "(" << j.first << ", " << j.second << ") ->";
        }
        cout << endl;
    }
}
bool spfa(int s)
{
    queue<int> q;
    for (int i = 1; i <= n + 1; i++)
    {
        dis[i] = inf;
        vis[i] = 0;
    }
    dis[s] = 0;
    vis[s] = 1;
    q.push(s);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (auto i : Edge[x])
        {
            if (dis[i.first] > dis[x] + i.second)
            {
                dis[i.first] = dis[x] + i.second;
                cnt[i.first] = cnt[x] + 1;
                if (cnt[i.first] >= n + 1)
                {
                    return false;
                }
                if (!vis[i.first])
                {
                    vis[i.first] = 1;
                    q.push(i.first);
                }
            }
        }
        vis[x] = 0;
    }
    return true;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int k, a, b, c;
        cin >> k >> a >> b >> c;
        switch (k)
        {
        case 1:
            add(a, b + 1, c);
            break;
        case 2:
            add(b + 1, a, -c);
            break;
        case 3:
            add(a, b + 1, c - 1);
            break;
        case 4:
            add(b + 1, a, -c - 1);
            break;
        case 5:
            add(b + 1, a, -c);
            add(a, b + 1, c);
            break;
        default:
            break;
        }
    }

    // 因为要保证每相邻的和之差大于等于0小于等于1
    for (size_t i = 1; i <= n; i++)
    {
        add(i + 1, i, 0);
        add(i, i + 1, 1);
    }
    // output();
    if (spfa(1))
    {
        cout << dis[n + 1] << endl;
    }
    else
    {
        cout << "impossible" << endl;
    }
    return 0;
}
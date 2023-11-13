#include <iostream>
#include <queue>
#include <vector>
// #include <bits/stdc++.h>
#include <limits>
#include <memory.h>
using namespace std;
const int maxn = 2010;
const int inf = 1e8;
struct edge
{
    int to;
    double value; // 风趣味
    double cost; // 费用
    edge(int nto, double nvalue, double ncost)
    {
        to = nto;
        value = nvalue;
        cost = ncost;
    }
};
vector<edge> Edge[maxn];
int n, m;
double dis[maxn];
int cnt[maxn], vis[maxn];
bool spfa(int s, double ans)
{
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    for (size_t i = 0; i <= n; i++)
    {
        dis[i] = inf;
        vis[i] = 0;
    }

    dis[s] = 0;
    for(int i = 1; i <= n; i++)
    {
        vis[i] = 1;
        q.push(i);
    }
    // cnt[s]++;
    q.push(s);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (auto i : Edge[x])
        {
            if (dis[i.to] > dis[x] + (ans * i.cost - i.value))
            {
                dis[i.to] = dis[x] + (ans * i.cost - i.value);
                cnt[i.to] = cnt[x] + 1;
                if (cnt[i.to] >= n)
                {
                    return false;
                }
                if (!vis[i.to])
                {
                    vis[i.to] = 1;
                    q.push(i.to);
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
    for (size_t i = 1; i <= m; i++)
    {
        int from, to;
        double value, cost;
        cin >> from >> to >> value >> cost;
        edge temp(to, value, cost);
        Edge[from].push_back(temp);
    }
    // 建立超级源点
    // for (size_t i = 1; i <= n; i++)
    // {
    //     edge temp(i, 0, 0);
    //     Edge[0].push_back(temp);
    // }
    double left = 1, right = 200;
    double ans = 0;
    while (right - left >= 0.01)
    {
        //cout << "left:" << left << "  " << "right: " << right << endl;
        double mid = (left + right) / 2;
        //cout << mid << endl;
        if (spfa(1, mid)) // 说明没有负环
        {
            // cout << "没有负环！" << endl;

            ans = mid;
            right = mid;
        }
        else
        {
            // cout << "有负环！" << endl;
            // 说明有负环，说明mid取值太小
            left = mid;
        }
    }
    cout << ans << endl;
    return 0;
}
/*
5 6
1 2 1 1
4 1 6 2
5 4 8 1
2 3 2 2
5 2 4 1
3 5 6 4
*/
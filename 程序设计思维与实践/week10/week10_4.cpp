#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 100;
int n, m;
int dcnt, scnt; // 分别代表dfs序列计数，scc计数。
vector<int> Edge[maxn];
vector<int> Edge2[maxn];
int vis[maxn], c[maxn], dfn[maxn]; // c为 i 号点所在的scc的编号。
void output()
{
    for (int i = 1; i <= n; i++)
    {
        cout << i << " -> ";
        for (auto j : Edge[i])
        {
            cout << j << " -> ";
        }
        cout << endl;
    }
}
void dfs1(int x) // 第一遍dfs获得dfs的逆后序序列
{
    vis[x] = 1;
    for (auto i : Edge[x])
    {
        if (!vis[i])
        {
            dfs1(i);
        }
    }
    dfn[++dcnt] = x;
}

void dfs2(int x) // 第二遍dfs获得强连通分量的个数
{
    c[x] = scnt;
    for (auto i : Edge2[x])
    {
        if (!c[i])
        {
            dfs2(i);
        }
    }
}

void kosaraju()
{
    dcnt = 0, scnt = 0;
    memset(vis, 0, sizeof(vis));
    memset(c, 0, sizeof(c));
    // 第一遍dfs
    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
        {
            dfs1(i);
        }
    }

    // 第二遍dfs
    for (int i = n; i >= 1; i--)
    {
        if (!c[dfn[i]])
        {
            scnt++;
            dfs2(dfn[i]);
        }
    }
}

vector<int> new_Graph[maxn]; // 缩点后的新图
int in_degree[maxn];
int function()
{
    memset(in_degree, 0, sizeof(in_degree));
    for (int i = 1; i <= n; i++)
    {
        for (auto j : Edge[i])
        {
            if (c[i] != c[j]) // 这里防止出现自环
            {
                new_Graph[c[i]].push_back(c[j]);
            }
        }
    }

    // for (int i = 1; i <= scnt; i++)
    // {
    //     cout << i << " -> ";
    //     for (auto j : new_Graph[i])
    //     {
    //         cout << j << " -> ";
    //     }
    //     cout << endl;
    // }

    for (int i = 1; i <= scnt; i++) // 去掉重复的边
    {
        sort(new_Graph[i].begin(), new_Graph[i].end());
        vector<int>::iterator it;
        it = unique(new_Graph[i].begin(), new_Graph[i].end());
        new_Graph[i].erase(it, new_Graph[i].end());

        for (auto j : new_Graph[i])
        {
            in_degree[j]++;
        }
    }

    int sum = 0;
    for (int i = 1; i <= scnt; i++)
    {
        if (in_degree[i] == 0)
        {
            sum++;
        }
    }

    return sum;
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int from, to;
        cin >> from >> to;
        Edge[from].push_back(to);
        Edge2[to].push_back(from);
    }
    // output();
    kosaraju();
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << dfn[i] << " ";
    // }
    // cout << endl;
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << c[i] << " ";
    // }
    // cout << endl;
    // cout << scnt << endl;
    int ans = function();
    cout << ans << endl;
    return 0;
}
/*
8 11
1 2
2 3
3 1
3 8
4 1
4 7
5 4
6 5
7 6
7 3
7 8
*/
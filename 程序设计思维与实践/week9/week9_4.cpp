#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
const int maxn = 1000010;
const int inf = 1e8;
int n, m;
vector<pair<int, int>> Edge1[maxn];
vector<pair<int, int>> Edge2[maxn];
int dis1[maxn];
int vis1[maxn];
int dis2[maxn];
int vis2[maxn];
void Dijkstra_startToEnd(int source, vector<pair<int, int>> *Edge1)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    for (int i = 1; i <= n; i++)
    {
        dis1[i] = inf;
        vis1[i] = false;
    }                                // 把所有的距离设置·为无限远
    dis1[source] = 0;                // 起点设为0
    heap.push(make_pair(0, source)); // 到source的距离为0
    while (!heap.empty())
    {
        int x = heap.top().second; // 记录最小距离的点

        heap.pop();
        if (vis1[x])
        {

            continue;
        }
        else
        {
            vis1[x] = true;
            for (auto i : Edge1[x]) // 访问这条边的所有邻接边
            {
                int y = i.first;
                if (dis1[y] > dis1[x] + i.second)
                {
                    dis1[y] = dis1[x] + i.second;
                    heap.push(make_pair(dis1[y], y));
                }
            }
        }
    }
}
void Dijkstra_endToStart(int source, vector<pair<int, int>> *Edge2)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    for (int i = 1; i <= n; i++)
    {
        dis2[i] = inf;
        vis2[i] = false;
    }                                // 把所有的距离设置·为无限远
    dis2[source] = 0;                // 起点设为0
    heap.push(make_pair(0, source)); // 到source的距离为0

    while (!heap.empty())
    {
        int x = heap.top().second; // 记录最小距离的点
        // cout << "push " <<  heap.top().first << " " << x << endl;
        heap.pop();
        if (vis2[x])
        {
            continue;
        }
        else
        {
            vis2[x] = true;
            for (auto i : Edge2[x]) // 访问这条边的所有邻接边
            {
                // cout << x << " "<< i.first << " " << i.second << " " << endl;
                int y = i.first;
                if (dis2[y] > dis2[x] + i.second)
                {
                    dis2[y] = dis2[x] + i.second;
                    heap.push(make_pair(dis2[y], y));
                    // cout << "push " <<  dis2[y] << " " << y << endl;
                }
            }
        }
    }
}
int main()
{
    int T;
    cin >> T;
    while (T != 0)
    {
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            int from, to;
            long long value;
            cin >> from >> to >> value;
            Edge1[from].push_back(make_pair(to, value));
            Edge2[to].push_back(make_pair(from, value)); // 翻转路径，就能得到从终点到起始点的情况
        }
        Dijkstra_startToEnd(1, Edge1);
        Dijkstra_endToStart(1, Edge2);
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            sum += (dis1[i] + dis2[i]);
            // cout << dis1[i] + dis2[i] << " ";
        }
        cout << sum << endl;
        T--;
        for (int i = 1; i <= n; i++)
        {
            Edge1[i].clear();
            Edge2[i].clear();
        }
    }
    return 0;
}
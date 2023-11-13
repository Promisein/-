#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;
const int maxn = 10010;
const int inf = INT_MAX;
struct edge
{
    int end;
    long long C; // 承重量
    long long D; // 通行时间
};
vector<edge> Edge[maxn];
int dis[maxn];
bool vis[maxn];
int N, M, T;
void Dijkstra(int s, int __MAX__WEIGHT)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    for (int i = 1; i <= N; i++)
    {
        dis[i] = inf;
        vis[i] = false;
    }
    dis[s] = 0;
    heap.push(make_pair(dis[s], s));
    while (!heap.empty())
    {
        int x = heap.top().second;
        heap.pop();
        if (vis[x])
        {
            continue;
        }
        else
        {
            vis[x] = true;
            for (auto i : Edge[x])
            {
                int y = i.end;
                if (i.C >= __MAX__WEIGHT && dis[y] > dis[x] + i.D)
                {
                    dis[y] = dis[x] + i.D;
                    heap.push(make_pair(dis[y], y));
                }
            }
        }
    }
}
bool __IN__TINE(int now_weight)
{
    Dijkstra(1, now_weight);
    if (dis[N] > T)  //对应编号为N的一家矿场
    {
        return false;
    }
    else
    {
        return true;
    }
}
int main()
{
    int X;
    cin >> X;
    while (X != 0)
    {
        cin >> N >> M >> T;
        int left_weight = 0;
        int right_weight = INT_MAX, mid;
        for (int i = 0; i < M; i++)
        {
            int A, B;       // A,B之间有路
            long long C, D; // 最大承重量为C，通行时间为D
            cin >> A >> B >> C >> D;
            edge temp1;
            temp1.end = B;
            temp1.C = C;
            temp1.D = D;
            Edge[A].push_back(temp1);

            edge temp2;
            temp2.end = A;
            temp2.C = C;
            temp2.D = D;
            Edge[B].push_back(temp2);

            // 二分找最大值？
            if (left_weight > C)
            {
                left_weight = C;
            }
            if (right_weight < C)
            {
                right_weight = C;
            }
            // 找见最合适的的二分区间
        }

        mid = (left_weight + right_weight) / 2;
        while (mid != left_weight && mid != right_weight)
        {
            if (__IN__TINE(mid)) // 如果在mid的重量下没有超时，那么说明可以增加让mid = left ，增加重量继续二分
            {
                left_weight = mid;
            }
            else
            {
                right_weight = mid;
            }
            mid = (left_weight + right_weight) / 2;
        }
        if (__IN__TINE(right_weight))
        {
            cout << right_weight << endl;
        }
        else
        {
            cout << left_weight << endl;
        }

        // 善后工作
        for (int i = 1; i <= N; i++)
        {
            Edge[i].clear();
        }
        X--;
    }

    return 0;
}
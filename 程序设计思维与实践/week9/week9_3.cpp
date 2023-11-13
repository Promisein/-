#include <iostream>
#include <limits>
using namespace std;
const int maxn = 505;
const int inf = 1e8 + 10;
int dis[maxn][maxn];
int n, m, w;
void Floyd_Warshall()
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}
void output()
{
    cout << "-----------------" << endl;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << dis[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;
}
int main()
{
    int T;
    cin >> T;
    while (T != 0)
    {
        cin >> n >> m >> w; // 代表顶点数和双向路径，和负权路径的个数
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                {
                    dis[i][j] = 0;
                }
                else
                {
                    dis[i][j] = inf;
                }
            }
        }
        for (int i = 0; i < m; i++)
        {
            int from, to;
            int value;
            cin >> from >> to >> value;
            dis[from][to] = value;
            dis[to][from] = value;
        }
        for (int i = 0; i < w; i++)
        {
            int from, to;
            int value;
            cin >> from >> to >> value;
            dis[from][to] = -value;
        }
        // output();
        Floyd_Warshall();
        // output();
        bool judge = false;
        for (int i = 1; i <= n; i++)
        {
            if (dis[i][i] < 0)
            {
                judge = true;
                cout << "YES" << endl;
                break;
            }
        }
        if (!judge)
        {
            cout << "NO" << endl;
        }
        T--;
    }
    return 0;
}
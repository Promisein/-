#include <iostream>
#include <algorithm>
using namespace std;
#define MAXM 2000002
#define MAXN 1000001
// 链式前向星
struct edge
{
    long long u, v, weight, next;
    bool operator<(const edge &e)
    {
        return weight < e.weight;
    }
} Edges[2000002];
// edge *Edges = new edge[MAXM];
int tot = 0; // tot is index of Edges
int n, m;
int f[1000001];

int find(int x)
{
    if (f[x] == x)
    {
        return x;
    }
    else
    {
        return f[x] = find(f[x]);
    }
}

bool join(int x, int y)
{
    long long temp_x = find(x);
    long long temp_y = find(y);
    if (temp_x == temp_y)
    {
        return false;
    }
    else
    {
        f[temp_y] = f[temp_x];
        return true;
    }
}

void krusal()
{
    for (long long i = 0; i <= n; i++)
    {
        f[i] = i;
    }
    sort(Edges, Edges + tot);
    long long sum = 0;
    long long goose_goose_Duck = 0; // 记录已经灌溉的农田数量
    for (long long i = 0; i < tot; i++)
    {
        if (join(Edges[i].u, Edges[i].v))
        {
            sum += Edges[i].weight;
            goose_goose_Duck++;
            if (goose_goose_Duck == n)
            {
                cout << sum << endl;
            }
        }
    }
    // cout << "you are wrong!" << endl;
}
void addEdge(int u, int v, int w)
{
}
int main()
{

    int p;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++)
    {
        Edges[tot].u = 0;
        Edges[tot].v = i;
        Edges[tot].weight = p;
        tot++;
        Edges[tot].v = 0;
        Edges[tot].u = i;
        Edges[tot].weight = p;
        tot++;
    }
    // 保存给出点的连线
    int u, v, w;
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        Edges[tot].u = u;
        Edges[tot].v = v;
        Edges[tot].weight = w;
        tot++;
        Edges[tot].v = u;
        Edges[tot].u = v;
        Edges[tot].weight = w;
        tot++;
    }
    krusal();
    return 0;
}
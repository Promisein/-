#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int maxn = 10000000;

long long f[2][maxn];
int weight[maxn], value[maxn];
int myindex = 1;
void addItem(int w, int v)
{
    weight[myindex] = w;
    value[myindex] = v;
}

int main()
{
    int N, V;
    cin >> N >> V;

    for (int i = 1; i <= N; i++)
    {
        int w, c, k;
        cin >> w >> c >> k;
        for (int i = 1; k > 0; k -= i, i *= 2)
        {
            int sz = min(k, i);
            addItem(w * sz, c * sz);
            myindex++;
        }
    }

    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= V; j++)
        {
            f[i][j] = 0;
        }
    }


    for (int i = 1; i < myindex; i++)
    {
       for (int j = V; j >= 0; j--)
       {
            f[i & 1][j] = f[(i - 1) & 1][j];
            if (j >= weight[i])
            {
                f[i & 1][j] = max(f[(i - 1) & 1][j], f[(i - 1) & 1][j - weight[i]] + value[i]);
            }
        }
    }

    cout << f[(myindex - 1) & 1][V] << endl;
    return 0;
}
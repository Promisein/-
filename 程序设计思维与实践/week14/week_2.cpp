#include <iostream>
#include <vector>
using namespace std;
const int maxn = 5100;
int f[maxn][maxn];
int weight[maxn], value[maxn];

int main()
{
    int n, V;
    cin >> n >> V;
    for (size_t i = 1; i <= n; i++)
    {
        cin >> weight[i] >> value[i];
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= V; j++)
        {
            f[i][j] = 0;
        }
    }
    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= V; j++)
        {
            if(j < weight[i])
            {
                f[i][j] = f[i - 1][j];
            }
            else
            {
                f[i][j] = max(f[i - 1][j], f[i][j - weight[i]] + value[i]);
            }
        }
    }
    
    cout << f[n][V] << endl;
    return 0;
}
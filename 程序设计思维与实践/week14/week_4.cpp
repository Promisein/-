#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 1010;
int w[maxn], c[maxn];
vector<int> gruop[102];
long long f[maxn];
int main()
{
    memset(f, 0, sizeof(f));
    int N, V;
    cin >> N >> V;
    int numGroup = 0;
    for (int i = 1; i <= N; i++)
    {
        cin >> w[i] >> c[i];
        int k;
        cin >> k;
        gruop[k].push_back(i);
        numGroup = max(numGroup, k);
    }

    // for(int i = 1; i <= numGroup; i++)
    // {
    //      for (auto k : gruop[i])
    //      {
    //         cout << k << " ";
    //      }
    //      cout << endl;
    // }

    for (int i = 1; i <= numGroup; i++)
    {
        for (int j = V; j >= 0; j--)
        {
            for (auto k : gruop[i])
            {
                if (j - w[k] >= 0)
                {
                     f[j] = max(f[j], f[j - w[k]] + c[k]);
                }
                // f[i][j] = f[i - 1][j];
                // if (j - w[k] >= 0)
                // {
                //     f[i][j] = max(f[i][j], f[i - 1][j - w[k]] + c[k]);
                // }
            }
        }
    }
    cout << f[V] << endl;
    return 0;
}
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 5100;
int arr1[maxn], arr2[maxn];
int f[maxn][maxn];

int main()
{
    memset(f, 0, sizeof(f));
    memset(arr1, 0, sizeof(arr1));
    memset(arr2, 0, sizeof(arr2));

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr1[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> arr2[i];
    }

    // f[1][0] = f[0][1] = f[0][0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (arr1[i] == arr2[j])
            {
                f[i][j] = f[i - 1][j - 1] + 1;
            }
            else
            {
                // cout << f[i - 1][j] << f[i][j - 1] << endl;
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}
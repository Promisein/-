#include <iostream>
#include <cstring>
#include <limits.h>
using namespace std;
typedef long long ll;
const int inf = INT_MAX;
const int maxn = 4010;
int f[maxn][maxn];
int main()
{
    string s;
    cin >> s;
    int n = s.length();
    for (size_t i = 0; i < maxn; i++)
    {
        for (size_t j = 0; j < maxn; j++)
        {
            if (i == j)
            {
                f[i][j] = 1;
            }
            else
            {
                f[i][j] = 0;
            }
        }
    }

    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i <= n - len + 1; i++)
        {
            int l = i, r = i + len - 1;
            f[i][r] = max(f[i + 1][r], f[i][r - 1]);
            if (s[i - 1] == s[r - 1])
            {
                f[i][r] = f[i + 1][r - 1] + 2;
            }
        }
    }
    cout << f[1][n] << endl;
    return 0;
}
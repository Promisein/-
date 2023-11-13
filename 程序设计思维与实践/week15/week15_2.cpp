#include <iostream>
#include <cstring>
#include <limits.h>
using namespace std;
typedef long long ll;
const int inf = INT_MAX;
ll f[105][105];
void init(int len)
{
    // memset(f, 0x3f, sizeof(f));
    for (size_t i = 0; i < len; i++)
    {
        f[i][i] = 1;
    }
} 

int main()
{
    string str;
    cin >> str;
    init(str.size());

    // DP
    for (int len = 2; len <= str.size(); len++)
    {
        for (size_t i = 0; i < str.size() - len + 1; i++)
        {
            int l = i, r = i + len - 1;
            f[l][r] = inf;
            if ((str[l] == '(' && str[r] == ')') || (str[l] == '[' && str[r] == ']'))
            {
                f[l][r] = min(f[l][r], f[l + 1][r - 1]);
            }
            for (int k = l; k < r; k++)
            {
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
            }
        }
    }
    cout << f[0][str.length() - 1] << endl;
    return 0;
}
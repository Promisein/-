#include <iostream>
#include <cmath>
using namespace std;
// wo tm 完全不懂
bool prime(long long n)
{
    if (n == 1)
        return false;
    if (n == 2)
        return true;
    for (long long i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

// 快速的幂计算，而且取模
long long qpow(long long x, long long n, long long mod)
{
    long long res = 1;
    while (n)
    {
        if (n & 1) // 如果n为奇数
        {
            res = (res * x) % mod;
        }
        x = (x * x) % mod;
        n >>= 1;
    }
    return res;
}
int main()
{
    int n, m;       // 长度为n的数字，初始值都是1
    long long maxp = 0; // 最大公因数
    long long res = 1;
    long long **arr;
    cin >> n >> m;

    arr = new long long *[n + 1];
    for (long long i = 0; i < n + 1; i++)
    {
        arr[i] = new long long[100];
        for (long long j = 0; j < 100; j++)
        {
            arr[i][j] = 0;
        }
    }

    for (long long i = 1; i <= m; i++)
    {
        int left, right; // 左右区间，乘以c的b次
        int c;
        long long b;
        cin >> left >> right >> c >> b;
        if (prime(c))
        {                          // 如果c为质数
            arr[left - 1][c] += b; // 利用差分记录多次操作后的次方数？
            arr[right][c] -= b;
            if (maxp < c)
            {
                maxp = c;
            }
        }
        else
        {
            // 如果c不为质数，将c化为多个质数，而且找见最大的质因数
            for (long long j = 2; j <= c; j++)
            {
                if (prime(j))
                {
                    while (c % j == 0) // j为质数，而且是c为j的倍数
                    {
                        arr[left - 1][j] += b; // 利用差分记录多次操作后的次方数？
                        arr[right][j] -= b;
                        c = c / j;
                        if (maxp < j)
                        {
                            maxp = j;
                        }
                    }
                }
            }
        }
    }

    for (long long i = 2; i <= maxp; i++)
    {
        long long temp = 0;
        long long min = arr[0][i];
        for (long long j = 0; j < n; j++)
        {
            temp += arr[j][i];
            if (min > temp)
            {
                min = temp;
            }
        }
        res = res * qpow(i, min, 1000000007) % 1000000007;
    }

    cout << res << endl;
    return 0;
}
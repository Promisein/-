#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1e6 + 100;

typedef long long ll;
//
ll cnt[maxn], sum[maxn], arr[maxn];
int main()
{
    int n;
    cin >> n;

    for (int i = 0; i <= n; i++)
    {
        cnt[i] = 0;
        sum[i] = 0;
        arr[i] = 0;
    }
    ll max_number = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        if(max_number < arr[i])
        {
            max_number = arr[i];
        }
        cnt[arr[i]]++;
    }
    sum[0] = 0;
    sum[1] = cnt[1];
    for(int i = 2; i <= max_number; i++)
    {
        sum[i] = max(sum[i - 1], sum[i - 2] + cnt[i] * i);
    }
    cout << sum[max_number] << endl;
    return 0;
}
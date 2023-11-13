#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int countSubstring(const std::string &str, const std::string &sub)
{
    if (sub.length() == 0)
        return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
         offset = str.find(sub, offset + 1))
    {
        ++count;
    }
    return count;
}
typedef long long ll;
int main()
{
    int n;
    cin >> n;
    vector<ll> arr;
    for (size_t i = 0; i < n; i++)
    {
        ll temp;
        cin >> temp;
        arr.push_back(temp);
    }
    sort(arr.begin(), arr.end());

    ll max, min;

    max = arr[n - 1];
    min = arr[0];
    if (n % 2 == 0)
    {
        if ((arr[n / 2] + arr[n / 2 - 1]) % 2 == 0)
        {
            ll mid = (arr[n / 2] + arr[n / 2 - 1]) / 2;
            printf("%d %d %d", max, mid, min);
        }
        else
        {
            float mid = (arr[n / 2] + arr[n / 2 - 1]) / 2.0;
            printf("%d %.1f %d", max, mid, min);
        }
    }
    else
    {
        ll mid = (arr[n / 2]);
        printf("%d %d %d", max, mid, min);
    }

    return 0;
}
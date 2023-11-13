#include <iostream>
#include <string>
using namespace std;
// 红 绿 黄
typedef long long ll;
int main()
{
    ll r, y, g;
    cin >> r >> y >> g;
    int n;
    cin >> n;
    ll sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        int k, t;
        cin >> k >> t;
        switch (k)
        {
        case 0:
            sum += t;
            break;
        case 1:
            sum += t;
            break;
        case 2:
            sum += (t + r);
            break;
        case 3:
            break;
        default:
            break;
        }
    }
    cout << sum << "\n";

    return 0;
}
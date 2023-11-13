#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int *ans = new int[n];
    ans[0] = (arr[0] + arr[1]) / 2;
    for (int i = 1; i < n - 1; i++)
    {
        ans[i] = (arr[i] + arr[i - 1] + arr[i + 1]) / 3;
    }
    ans[n - 1] = (arr[n - 2] + arr[n - 1]) / 2;
    for (int i = 0; i < n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    delete [] arr;
    delete [] ans;
    return 0;
}
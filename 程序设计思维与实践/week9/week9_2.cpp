#include <iostream>
#include <vector>
using namespace std;
struct aera
{
    double left;
    double right;
};

int main()
{
    int n;
    cin >> n;
    vector<aera> arr1;
    vector<aera> arr2;
    for (int i = 0; i < n; i++)
    {
        aera temp;
        cin >> temp.left >> temp.right;
        arr1.push_back(temp);
    }
    for (int i = 0; i < n; i++)
    {
        aera temp;
        cin >> temp.left >> temp.right;
        arr2.push_back(temp);
    }
    double ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if(max(arr1[i].left, arr2[j].left) < min(arr1[i].right, arr2[j].right)) // 判断交集的好办法
            {
                ans += min(arr1[i].right, arr2[j].right) - max(arr1[i].left, arr2[j].left);
            }

        }
    }
    cout << ans << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
// 贪婪算法，依次选出最大的喷洒距离
struct blow_aera
{
    double left;  // 喷洒的左端
    double right; // 喷洒的右端
    bool operator<(blow_aera temp)
    {
        return this->left < temp.left;
    }
};

int main()
{
    int T;
    cin >> T;
    while (T != 0)
    {
        int n;
        double l, w; // 长为l， w为宽度，n为喷头数目
        // 喷头的为放在中心线上
        cin >> n;
        cin >> l >> w;
        vector<blow_aera> aera;
        for (int i = 0; i < n; i++)
        {
            double x, r;
            cin >> x >> r;
            if (2 * r < w)
            {
                continue;
            }
            blow_aera temp;
            temp.left = x - sqrt(r * r - w * w / 4.0);
            temp.right = x + sqrt(r * r - w * w / 4.0);
            aera.push_back(temp);
        }
        sort(aera.begin(), aera.end()); // 对喷头的能喷到的最左端排序

        // for(auto l : aera)
        // {
        //     cout << l.left << " " << l.right << endl;
        // }

        double __MAX__RIGHT__POSITION = 0; // 记录当前最远的右端点的位置
        int ans = 0;                       // 记录最少使用的喷头个数
        bool judge = true;                 // 判断是否可以被完全覆盖
        vector<blow_aera>::iterator it = aera.begin();
        while (__MAX__RIGHT__POSITION < l) // 最右端点小于矩阵长度
        {
            ans++;
            double __NOW__RIGTH__POSITON = __MAX__RIGHT__POSITION;        // 记录当前点的最右端点
            while (it != aera.end() && it->left <= __NOW__RIGTH__POSITON) // 当当前的喷头的左端点小于当前的右端点
            {
                if (it->right > __MAX__RIGHT__POSITION)
                {
                    __MAX__RIGHT__POSITION = it->right;
                }
                it++;
            }

            if(__MAX__RIGHT__POSITION == __NOW__RIGTH__POSITON && __NOW__RIGTH__POSITON < l)
            {
                //说明无法覆盖，喷头和喷头之间出现了间隙，或者喷头用完了但是还是没有覆盖
                cout << -1 << endl;
                judge = false;
                break;
            }
        }

        if(judge)
        {
            cout << ans << endl;
        }
        
        T--;
    }

    return 0;
}
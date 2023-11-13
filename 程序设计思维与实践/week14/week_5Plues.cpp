#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
int main()
{
    float weight[1000], value[1000], a[1000] = {0}, b[1000];
    float smallvalue = 0.0, bigvalue = 0.0, bigweight = 0.0, smallweight = 0.0;
    long long x, c, number;
    long long n, y, d, q, m;
    long long p = 0;
    long long i = 0;
    scanf("%d%d", &number, &c);
    for (x = 0; x < number; x++)
    {
        scanf("%f", &weight[x]); // 输入重量
        scanf("%f", &value[x]);  // 输入价值
    }

    y = pow(2, number);
    for (p = 0; p < y; p++)
    {
        d = p;
        i = 0;
        smallvalue = 0;
        smallweight = 0;
        while (d > 0)
        {
            a[i] = d % 2;
            i = i + 1;
            d = d / 2;
        } // 转化二进制
        for (i = number; i > 0; i--)
        {
            smallweight = smallweight + a[i - 1] * weight[i - 1];
            smallvalue = smallvalue + a[i - 1] * value[i - 1];
        }
        if (smallweight <= c)
        {
            if (smallvalue >= bigvalue)
            {
                bigvalue = smallvalue;
                bigweight = smallweight;
                for (q = 0; q < number; q++)
                {
                    b[q] = a[q];
                } // 清空背包
            }
        }
    }
    // for (q = 0; q < number; q++)
    // {
    //     if (b[q] == 1)
    //     {
    //         m = q + 1;
    //         printf("%d ", m); // 输出序号
    //     }
    // }
    // printf("%ld ", bigweight, bigvalue);

    cout << bigweight << endl;
    return 0;
}
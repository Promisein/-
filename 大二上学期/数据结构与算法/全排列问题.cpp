#include<iostream>
using namespace std;
int sum_value = 0;                   //λ�����ĺ�
void swap(int& a, int& b)    //��������
{
    int c = a;
    a = b;
    b = c;
}
int arragement(int* a, int index, int n)    //�ݹ�ȫ����
{
    if (index == n)
    {
        int value = 0;                       //valueΪȫ���еļ�ֵ
        for (int i = 0; i < n; i++)
        {
            value += (i + 1) ^ a[i];
        }
        sum_value |= value;
    }
    else
    {
        for (int i = index; i < n; i++)
        {
            swap(a[index], a[i]);
            arragement(a, index + 1, n);          //�ݹ鲿��
            swap(a[index], a[i]);
        }
    }
    return sum_value;
}
int main()
{
    int n;   // �����Ԫ�ظ���
    cin >> n;
    int a[10];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << arragement(a, 0, n) << endl;
    return 0;
}
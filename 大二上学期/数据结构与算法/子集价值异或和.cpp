#include<iostream>
using namespace std;
int XOR_sum = 0;   //����
int subset(int* binary, int* input, int index, int n)  //bΪ���������,aΪ�ݹ�Ķ���������nΪԪ�ظ���
{
	if (index == n)
	{
		int sum_value = 0;
		int count = 1;
		for (int i = 0; i < n; i++)
		{
			if (binary[i] == 1)
			{
				sum_value += count * input[i];          //ÿһ���Ӽ��ļ�ֵ
				count++;
			}
		}
		XOR_sum ^= sum_value;                  //����
	}
	else
	{
		binary[index] = 1;
		subset(binary, input, index + 1, n);
		binary[index] = 0;
		subset(binary, input, index + 1, n);
	}//�ݹ麯����������Ӽ�
	return XOR_sum;
}
int main()
{
	int n;
	cin >> n;
	int binary[100];    //����������ı�������
	int input[20];       // ���������
	for (int i = 0; i < n; i++)
	{
		cin >> input[i];
	}
	cout << subset(binary, input, 0, n) << endl;
	return 0;
}

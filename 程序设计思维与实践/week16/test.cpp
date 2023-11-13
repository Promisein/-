#include <iostream>;
#include <vector>;
#include <functional>;
#include <ctime>;
#include <random>;
#include <algorithm>;
 
using namespace std;
 
 
int r = 0;
 
void addRandom(vector<int>& v, int i = 0) {//随机添加值到容器里
	srand(unsigned(time(NULL)));
	int a;
	for (int l = 0; l < i; l++)
	{
		a = rand();
		v.push_back(a);
	}
}
 
 
 
 
void add(vector<int>& v)//这个是测试用的
{
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);
	v.push_back(10);
}
 
 
 
 
void printVector(vector<int>& v) {
	for (int i = 0; i < v.size(); i++)
	{
		cout << i << "  " << v[i] << endl;
	}
}
 
 
 
 
void randomVector(vector<int> &v)//随机打乱vector
{
	vector<int> v_index1 = v, v_index2 = v;
	int ran;
	for (int i = 0; i < v.size(); i++)
	{
		srand(time(0) + r);
		r++;
		ran = rand() % v_index2.size();
		v_index1[i] = v_index2[ran];
		v_index2.erase(v_index2.begin() + ran);
	}
	v = v_index1;
 
}
 
 
 
 
void monkeySort(vector<int>& v)//核心
{
	while (true)
	{
		//随机打乱vector
		randomVector(v);
 
 
		int index = 0;
		for (int i = 0; i < v.size() - 1; i++)
		{
			if (v[i] <= v[i + 1])
			{
				index++;
			}
			else
			{
				break;
			}
		}
		cout << index << endl;
		if (index == v.size() - 1)
		{
			return;
		}
	}
}
 
 
 
void test() {
	vector<int> v;
 
	addRandom(v, 7);//后面的值是vector添加随机数数量的大小，别太大
	//add(v);
 
	monkeySort(v);
 
	printVector(v);
 
}
 
 
 
 
 
int main() {
	test();
	system("pause");
	return 0;
}
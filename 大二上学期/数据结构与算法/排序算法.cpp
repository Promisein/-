#include<iostream>
using namespace std;
template<class T>
class mySort
{public:
	mySort(int n);              //���캯��
	~mySort() {};               //��������
	void swap(T& a, T& b);       //��������
	void ranking_sort(T* a, T* r, int n);           //��������
	void selection_sort(T* a, int n);               //ѡ������
	void insertion_sort(T* a, int n);               //��������
	void bubble_sort(T* a, int n);                  //ð�ݽ�������
private:
	int n;                      //��Ҫ��������ĸ���
};
template<class T>
mySort<T>::mySort(int n)
{
	if (n >= 0)
	{
		this->n = n;
	}
	else
	{
		this->n = 0;
	}
}
template<class T>
void mySort<T>::swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}
template<class T>
//�������� 
void mySort<T>::ranking_sort(T* a, T*r, int n)
{
	for (int i = 0; i < n; i++)
	{
		r[i] = 0;           
	}//��ʼ����������
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[i] >= a[j])
			{
				r[i]++;
			}
			else
			{
				r[j]++;
			}
		}
	}//�������Σ������δ�����������
	T* mid = new T[n];             
	for (int i = 0; i < n; i++)
	{
		mid[r[i]] = a[i];          //���ø������飬���ն�Ӧr�����е�������ʱ�洢��mid����������
	}
	for (int i = 0; i < n; i++)
	{
		a[i] = mid[i];            //���ø��������ֵ��a�����ֵ�滻��
	}
	delete[] mid;
}
template<class T>
//��ʱֹͣ��ѡ������
void mySort<T>::selection_sort(T* a, int n)
{
	bool judge = false;    //�ж��Ƿ���������
	for (int i = n; i > 1 && !judge; i--)
	{
		int max = 0;       //��������ڵ�����
		judge = true;
		for (int j = 1; j < i; j++)
		{
			if (a[j] >= a[max])
			{
				max = j;
			}
			else
			{
				judge = false;     //ֻҪ��һ��ִ�У�˵�����򲻶�
			}
		}
		mySort<T>::swap(a[max], a[i - 1]);
	}
}
template<class T>
//��������
void mySort<T>::insertion_sort(T* a, int n)
{
	//���±�Ϊ1��n-1Ԫ��������뵽�Ѿ��������е��е�λ��
	for (int i = 1; i < n; i++)          
	{
		//������a��ĩβ��a[0]Ѱ�ұȽ�Ԫ�أ��ҵ����ʵ�λ�ò���a[i]
		int j = i;
		T temp = a[i];
		while (j > 0 && temp < a[j - 1])
		{
			a[j] = a[j - 1];              //Ԫ��������ƣ��ҵ�����λ�ü��ɲ����Ӧ��Ԫ��
			j--;
		}
		//λ���ҵ�������Ԫ��
		a[j] = temp;
	}
}
template<class T>
//ð�ݽ�������
void mySort<T>::bubble_sort(T* a, int n)
{
	bool judge = false;            //�����Ƿ���������������������ʱֹͣ����
	for (int i = 0; i < n - 1; i++)
	{
		if (judge)
		{
			break;
		}
		judge = true;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j] < a[j + 1])
			{
				mySort<T>::swap(a[j], a[j + 1]);
				judge = false;
			}
		}
	}
}
int main()
{
	int n;
	cin >> n;
	mySort<int> s(n);           //����mySort<int>��Ķ��󣬲��ҳ�ʼ�������С
	int* array = new int[n] ();
	//int* rank = new int[n]();   //���������е���������
	for (int i = 0; i < n; i++)
	{
		cin >> array[i];
	}
	//s.ranking_sort(array, rank, n);      //��������
	//s.selection_sort(array, n);          //ѡ������
	//s.insertion_sort(array, n);          //��������
	s.bubble_sort(array, n);               // ð������
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	delete [] array;
	//delete [] rank;
	return 0;
}
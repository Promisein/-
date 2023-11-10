#include<iostream>
#include<utility>
using namespace std;
template<class K,class E>
class hashTable
{
public:
	hashTable(int theDivisor);         //���캯��
	~hashTable() { delete[]table; }    //��������
	void erase(const K& theKey);       //ɾ������
	pair<const K, E>* find(const K& theKey);  //���Һ���
	void insert(const pair<const K, E>& thePair);  //���뺯��
	int get_dSize() { return dSize; }  //����ɢ�д�С
 	int search(const K& theKey)const;  //��ѯ����
	void output();   //���Ժ���
private:
	pair<const K, E>** table;//ɢ�б�  
	//����ΪʲôҪ��ָ�룬��Ϊָ��ָ���ֵ���ܹ���ʾͰΪ�գ����������棬���Ĭ��������Ϊ0λ��Ͱ�Ļ�����ôtheKeyΪ0�ľʹ治��ȥ��
	int divisor;             //���к����ĳ���
	int dSize;               //�ֵ�����ĸ���
};
//���캯��
template<class K,class E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	//��ʼ��ɢ�б����ҷ���ָ������ռ�
	table = new pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++)
	{
		table[i] = NULL;
	}
}
//���Һ������Ҽ���Ӧ��Ͱ
template<class K, class E>
int hashTable<K, E>::search(const K& theKey)const
{//
	int i = (int)theKey % divisor;      //��ʼ��Ͱ
	int j = i;                          //����ʼͰ��ʼ
	//cout << j << i << endl;
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)
		{
			return j;
		}
		else
		{
			j = (j + 1) % divisor;
			
		}
	} while (j!=i);                      //�ص���ʼͰ
	return j;                     //��ʾͰ����
}
template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey)
{
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
	{
		cout << -1 << endl;
		return NULL;
	}
	else
	{
		cout << b << endl;
	}
	return 0;
}
template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
	int b = search(thePair.first);
	if (table[b] == NULL)
	{
		table[b] = new pair<const K, E>(thePair);
		dSize++;
		cout << b << endl;
	}
	else
	{
		if (table[b]->first == thePair.first)
		{
			table[b]->second = thePair.second;
			cout << b << endl;
		}
		else
		{
			cout << "Existed" << endl;
		}
	}
}
template<class K, class E>
void hashTable<K, E>::erase(const K& theKey)
{//�и��򵥱����ط������ǰѺ���λ�ò��Ե�ɾ������Ȼ�����²���
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
	{
		cout << "Not Found" << endl;
	}
	else
	{
		table[b] = NULL;    //ɾ����Ӧ��Ͱ
		int initial_b = b;        //��¼��ʼͰ��λ��, ��Ϊѭ��������
		int exchange_b = b;  // ��������ԭ����Ͱ
		int move_number = 0;      //��¼�ƶ��Ĳ���

		b = (b + 1) % divisor;    //����һ��Ͱ��ʼ����
		while (table[b] != NULL && b != initial_b)      //û��������Ͱ����û�лص���ʼͰ
		{
			int temp_initial_b= (int)table[b]->first % divisor;    //��¼��ǰ����Ͱ��Ӧ����ʼͰ
			if ((temp_initial_b <= exchange_b && temp_initial_b < b && b > exchange_b) ||          //��ǰͰ��ɢ�б�ĩβ֮��ķ�Χ�ڵ��ƶ�
				(temp_initial_b <= exchange_b && temp_initial_b > b && exchange_b > b) ||      //��ǰͰ��ɢ�б�ĩβ -> �ٴ�ɢ�б��ͷ��ʼ�ƶ�
				(temp_initial_b > b && b > exchange_b)                                                //��˳����ǰ�ƶ�    
				)
			{
				table[exchange_b] = table[b];     //����ʼͰ����
				exchange_b = b;
				move_number++;
			}
			
			b = (b + 1) % divisor;    //��ǰ��ʼ����
		}
		cout << move_number << endl;
		table[exchange_b] = NULL;
	}
}
template<class K, class E>
void hashTable<K, E>::output()
{
	/*
	for (int i = 0; i < this->divisor; i++)
	{
		if (table[i] == NULL)
		{
			cout << "theKey: NUll" << " " << "value: NUll" << endl;
		}
		else
		{
			cout << "theKey: " << table[i]->first 
				<< " value: " << table[i]->second 
				<< endl;
		}
	}
	*/
	cout << "bucket:\t";
	for (int i = 0; i < this->divisor; i++)
	{
		
		cout << i << "\t";
	}
	cout << endl;
	cout << "thekey:\t";
	for (int i = 0; i < this->divisor; i++)
	{
		
		if (table[i] == NULL)
		{
			cout << "*" << "\t";
		}
		else
		{
			cout << table[i]->first << "\t";
		}
	}
	cout << endl;
	cout << "themod:\t";
	for (int i = 0; i < this->divisor; i++)
	{
		
		if (table[i] == NULL)
		{
			cout << "*" << "\t";
		}
		else
		{
			cout << table[i]->first % divisor << "\t";
		}
	}
	cout << endl;
}
int main()
{
	int D, m;
	cin >> D >> m;
	hashTable<int, int> dic(D);
	int opt, x;          //����ģʽ,�Ͷ�ӦԪ�ز���
	for (int i = 0; i < m; i++)
	{
		cin >> opt;
		if (opt == 0)
		{
			cin >> x;
			pair<int, int>mypair(x, 520);
			dic.insert(mypair);
		}
		else
		{
			if (opt == 1)
			{
				cin >> x;
				pair<const int, int>* p = dic.find(x);
			}
			else
			{
				if (opt == 2)
				{
					cin >> x;
					dic.erase(x);
					//dic.output();
				}
				if (opt == 3)
				{
					dic.output();
				}
			}
		}
	}
	return 0;
}
/*
7 15
1 21
0 1
0 13
0 5
0 23
0 26
0 33
*/
/*
  1
  6
  5
  1->2
  5->6->0
  5->6->0->1->2->3
*/
/*
11 100
0 0
0 1
0 21
0 18
0 17
0 28
0 39
0 12
0 62
0 51
0 50
*/
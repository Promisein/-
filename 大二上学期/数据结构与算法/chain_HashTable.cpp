#include<iostream>
using namespace std;
template<class T>
struct chainNode
{
	//���ݳ�Ա
	T element;
	chainNode<T>* next;

	//solutions
	chainNode() {}     //Ĭ�Ϲ��캯��
	chainNode(const T& element)
	{
		this->element = element;
	}//���캯��
	chainNode<T>(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};
template<class T>
class chain
{
public:
	chain(int initialCapacity = 10)
	{
		firstNode = NULL;
		listSize = 0;
	}         //���캯��
	~chain()
	{
		//�ظ����������׽�㣬ֱ������Ϊ��
		while (firstNode != NULL)
		{
			chainNode<T>* nextNode = firstNode->next;
			delete firstNode;
			firstNode = nextNode;
		}
	}                              //��������
	void erase(const T& theElement);                     //ɾ��ָ��Ԫ��
	void insert(const T& theElement);  //ָ��λ�ò���Ԫ��
	void find(const T& theElement);              //�����������Ƿ���ָ��Ԫ��
private:
	chainNode<T>* firstNode;   //�����ͷָ��
	int listSize;              //�����Ԫ�ظ���
};
template<class T>
void chain<T>::insert(const T& theElement)
{
	if (firstNode == NULL || firstNode->element > theElement)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
		listSize++;
		return;
	}
	chainNode<T>* currentNode = firstNode;
	while (currentNode->next != NULL
		&& currentNode->element < theElement
		&& currentNode->next->element < theElement)
	{
		currentNode = currentNode->next;
	}
	if (currentNode->element == theElement || (currentNode->next != NULL && currentNode->next->element == theElement))
	{
		cout << "Existed" << endl;
	}
	else
	{
		chainNode<T>* newNode = new chainNode<T>(theElement, currentNode->next);
		currentNode->next = newNode;
		listSize++;
	}
}
template<class T>
void chain<T>::erase(const T& theElement)
{
	if (firstNode == NULL)
	{
		cout << "Delete Failed" << endl;
		return;
	}
	chainNode<T>* deleteNode;
	if (theElement == firstNode->element)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		chainNode<T>* currentNode = firstNode;
		while (currentNode->next != NULL && currentNode->next->element != theElement)
		{
			currentNode = currentNode->next;
		}
		if (currentNode->next == NULL)             //�����������
		{
			cout << "Delete Failed" << endl;
			return;
		}
		deleteNode = currentNode->next;
		currentNode->next = currentNode->next->next;
	}
	listSize--;
	delete deleteNode;
	cout << listSize << endl;
}
template<class T>
void chain<T>::find(const T& theElement)
{
	chainNode<T>* currentNode = firstNode;
	while (currentNode != NULL && currentNode->element < theElement)
	{
		currentNode = currentNode->next;
	}
	if (currentNode != NULL && currentNode->element == theElement)
	{
		cout << listSize << endl;
	}
	else
	{
		cout << "Not Found" << endl;
	}

}
template<class K,class E>
class chain_HashTable
{
public:
	chain_HashTable(int theDivisor = 11);
	~chain_HashTable()
	{
		//error!!!!delete table;
		delete []table;
	}
	void insert(const K& theKey);    //���뺯��
	void erase(const K& theKey);                     //ɾ������
	void find(const K& theKey);
private:
	int divisor;    //����
	chain<K>* table;     //��������
};
template<class K, class E>
chain_HashTable<K, E>::chain_HashTable(int theDivisor)
{
	divisor = theDivisor;
	table = new chain<K>[divisor];
}
template<class K, class E>
void chain_HashTable<K, E>::find(const K& theKey)
{
	int homeBucket = (int)theKey % divisor;
	table[homeBucket].find(theKey);
}
template<class K, class E>
void chain_HashTable<K, E>::insert(const K& theKey)
{
	int homeBucket = (int)theKey % divisor;
	table[homeBucket].insert(theKey);
}
template<class K, class E>
void chain_HashTable<K, E>::erase(const K& theKey)
{
	int homeBucket = (int)theKey % divisor;
	table[homeBucket].erase(theKey);
}
int main()
{
	int D, m;
	cin >> D >> m;
	chain_HashTable<int, int> t(D);
	for (int i = 0; i < m; i++)
	{
		int opt, x;
		cin >> opt >> x;
		switch (opt)
		{
		case 0:
			t.insert(x);
			break;
		case 1:
			t.find(x);
			break;
		case 2:
			t.erase(x);
			break;
		default:
			break;
		}
	}
	return 0;
}
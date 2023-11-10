#include<iostream>
using namespace std;
template<class T>
//��������
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
//����������
class chain
{
public:
	chain(int initialCapacity = 10);
	chain(const chain<T>& theList);
	~chain();

	void erase(int theIndex);                     //ɾ��ָ��Ԫ��
	void insert(int theIndex, const T& element);  //ָ��λ�ò���Ԫ��
	int search(const T& theElement);              //�����������Ƿ���ָ��Ԫ��
	void reserve();                               //ԭ����������
	int mysum();                                  //����
	void output();                                //�������
	chainNode<T>* get_firstNode() { return this->firstNode; }    //��������ͷ���
	void mysort(chainNode<T>* firstNode);         //����������(ͷ����Ԫ�ظ���)
	void chain_join(chain<T>& Node1, chain<T>& Node2);       //Ҫ���ӵ����������ͷ���
	class iterator        //����������ࣨǰ����������
	{
	public:
		//���캯��
		iterator(chainNode<T>* theNode = NULL)
		{
			node = theNode;
		}
		//�������ӷ�����
		iterator& operator ++()     //ǰ��
		{
			node = node->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			node = node->next;
			return old;
		}
		//�����ò�����
		T& operator *()const { return node->element; }
		T* operator ->()const { return &node->element; }
		//��ȼ���
		bool operator !=(const iterator right) const { return node != right.node; }
		bool operator ==(const iterator right) const { return node == right.node; }
	protected:
		chainNode<T>* node;
	};
	iterator begin() { return iterator(this->firstNode); }      //���������ͺ���begin()
	iterator end() { return iterator(NULL); }  //���������ͺ���end()
private:
	chainNode<T>* firstNode;   //�����ͷָ��
	int listSize;              //�����Ԫ�ظ���
	//void checkIndex(int theIndex) const;

};
template<class T>
chain<T>::chain(int initialCapacity)      //���캯��
{
	firstNode = NULL;
	listSize = 0;
}
template<class T>
chain<T>::chain(const chain<T>& theList)       //���ƹ��캯��(ԭ����Ķ���Ҫ���� theList ����)
{
	//����Ϊ��
	if (listSize == 0)
	{
		firstNode = NULL;
		return;
	}
	//����Ϊ��
	this->firstNode = new chainNode<T>((theList.firstNode)->element);        //ͷ���new��һ����theList.firstNode->element��ʼ��
	chainNode<T>* sourceNode = (theList.firstNode)->next;
	chainNode <T>* targetNode = firstNode;                                    //��������theList��ͷ���
	//for(; sourceNode != NULL; sourceNode = sourceNode->next)
	while (sourceNode != NULL)
	{
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
}
template<class T>
chain<T>::~chain()   //����������ɾ����������н��
{
	//�ظ����������׽�㣬ֱ������Ϊ��
	while (firstNode != NULL)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}
template<class T>
void chain<T>::erase(int theIndex)   //ɾ��ָ��������Ԫ��
{
	chainNode<T>* deleteNode;    //deleteNodeָҪɾ���Ľ��
	//ɾ���׽��
	if (theIndex == 0)
	{
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{
		//��ָ��pָ��Ҫɾ���Ľ���ǰ���
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		deleteNode = p->next;
		p->next = deleteNode->next;  //p->next=p->next->next;
	}
	listSize--;
	delete deleteNode;
}
template<class T>
void chain<T>::insert(int theIndex, const T& theElement)    //����Ԫ��theElement����������ΪtheIndex
{
	if (theIndex == 0)
	{
		firstNode = new chainNode<T>(theElement, firstNode);
	}
	else
	{
		//��ָ��pָ��Ҫ�½���ǰ���
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
		{
			p = p->next;
		}
		p->next = new chainNode<T>(theElement, p->next);     //�½���nextָ��ָ��ԭ��ǰ������һ�����
	}
	listSize++;
}
template<class T>
int chain<T>::search(const T& theElement)   //��ѯԪ�أ���������״��������������򷵻�-1
{
	//��currentNode��¼��ǰ���
	chainNode<T>* currentNode = firstNode;   //��ʼ���
	int currentIndex = 0;      //��ǰ��������
	while (currentNode != NULL && currentNode->element != theElement)
	{
		currentNode = currentNode->next;
		currentIndex++;
	}
	if (currentNode == NULL)
	{
		return -1;
	}
	else
	{
		return currentIndex;
	}
}
template<class T>
void chain<T>::reserve()            //��ת����
{
	if (firstNode->next == NULL || firstNode == NULL)
	{
		//ͷ���Ϊ�ջ���ֻ��һ����㣬��firstNode->next = NUll
		return;
	}
	chainNode<T>* frontNode = firstNode;   //ǰ�ؽ��,��ʼָ���һ�����
	chainNode<T>* lastNode = NULL;               //ĩβ���
	chainNode<T>* midNode = firstNode;     //�м��㣬��ʼָ���һ�����
	/*
	chainNode<T>* endNode = firstNode;           //�����
	while (endNode != NULL)
	{
		endNode = endNode->next;
	}
	firstNode->next = endNode;
	*/
	//�׽�㵽ĩβ
	/*
	for (int i = 0; i < listSize; i++)
	{
		frontNode = frontNode->next;
		midNode->next = lastNode;
		lastNode = midNode;
		midNode = frontNode;
	}
	firstNode->next = lastNode;
	*/   //������bug��������Ϊ�ٽ�������ѭ�����쳣�˳�
	//��������frontNode = NULL;   midNode = NULL; lastNodeֵ��ԭ��������һλ;
	//���Ż����룩
	while (midNode != NULL)
	{
		frontNode = frontNode->next;
		midNode->next = lastNode;
		lastNode = midNode;
		midNode = frontNode;
	}
	firstNode = lastNode;
}
template<class T>
int chain<T>::mysum()
{
	int sum = 0;
	int index = 0;
	for (iterator beginning = begin(); beginning != end(); beginning++)
	{
		//cout << index << "\t" << *beginning << "\t" << a << endl;
		sum = sum + (index ^ (*beginning));             //һ��һ��Ҫ�������ţ�������
		index++;
	}
	return sum;
}
template<class T>
void chain<T>::output()     //�������Ԫ��
{
	for (iterator iter = begin(); iter != end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}
template<class T>
void chain<T>::mysort(chainNode<T>* firstNode)          //����������(ͷ���)
{
	//bool judge = false;                              //�ж������Ƿ�����
	for (iterator iter1 = begin(); iter1 != end(); iter1++)
	{
		//if (judge) { break; }
		//judge = true;
		for (iterator iter2 = begin(); iter2 != end(); iter2++)
		{
			if (*iter2 > *iter1)
			{
				T temp = *iter1;
				*iter1 = *iter2;
				*iter2 = temp;
				//judge = false;
			}
		}
	}
}
template<class T>
void chain<T>::chain_join(chain<T>& List1, chain<T>& List2)
{
	iterator iter1 = List1.begin();
	for (iter1; iter1 != List1.end(); iter1++)
	{
		List2.insert(0, *iter1);
	}
	//List2.output();
	List2.mysort(List2.get_firstNode());
	//List2.output();
	cout << List2.mysum();
}

int main()
{
	int N, M;
	cin >> N >> M;
	chain<int> list1, list2;
	int input_element;
	for (int i = 0; i < N; i++)
	{
		cin >> input_element;
		list1.insert(i, input_element);
	}//��������1
	for (int i = 0; i < M; i++)
	{
		cin >> input_element;
		list2.insert(i, input_element);
	}//��������2

	//list1.output();
	//list2.output();
	list1.mysort(list1.get_firstNode());
	list2.mysort(list1.get_firstNode());
	//list1.output();
	//list2.output();
	cout << list1.mysum() << endl;
	cout << list2.mysum() << endl;
	if (N == 0)    // ����1Ϊ��
	{
		cout << list2.mysum() << endl;
	}
	if (M == 0)   //����2Ϊ��
	{
		cout << list1.mysum() << endl;
	}
	if ((M != 0) && (N != 0))   //������Ϊ��
	{
		list2.chain_join(list1, list2);
	}
	return 0;
}
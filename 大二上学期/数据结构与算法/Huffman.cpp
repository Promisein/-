#include <iostream>
using namespace std;
template <class T>
struct HoffmanTree_Node
{
    //���ݳ�Ա
    T weight = 0; //Ȩ��
    HoffmanTree_Node* left = NULL;
    HoffmanTree_Node* right = NULL;

    //���캯��
    HoffmanTree_Node(){}
    HoffmanTree_Node(T w)
    {
        weight = w;
        left = right = NULL;
    }
    HoffmanTree_Node(T w, HoffmanTree_Node* l, HoffmanTree_Node* r)
    {
        weight = w;
        left = l;
        right = r;
    }
};

template <class T>
class Hoffman_Tree
{
private:
    HoffmanTree_Node<T>** Heap; //С����(Ѱ�ҳ�Ȩ������С������ֵ)
    int heapSize;

public:
    Hoffman_Tree(T* weight_character, int n);
    ~Hoffman_Tree() { delete[] Heap; };
    void initial();                                //��heap���жѻ�
    void construct_Tree();                         //�����������
    HoffmanTree_Node<T>* top() { return Heap[1]; } //��öѶ���Ԫ��
    void pop();
    void push(HoffmanTree_Node<T>* TreeNode);
    void output();
    void sum_Length(HoffmanTree_Node<T>* t, int n);
};

template <class T>
Hoffman_Tree<T>::Hoffman_Tree(T* weight_character, int n)
{
    heapSize = n;
    Heap = new HoffmanTree_Node<T> *[27];
    /*
    HoffmanTree_Node<T>* temp;
    for (int i = 1; i <= n; i++)
    {
        temp = new HoffmanTree_Node<T>(weight_character[i - 1]);
        push(temp);
    }
    */
    for (int i = 1; i <= n; i++)
    {
        Heap[i] = new HoffmanTree_Node<T>(weight_character[i - 1]);
    }
    
    for (int i = n + 1; i < 27; i++)
    {
        Heap[i] = new HoffmanTree_Node<T>;
    }
    
    //output();
} //��Ȩ�ص�ֵ¼�뵽heap��
//asdfghjklzxcvbnmqwertyuiopaaaaa
template <class T>
void Hoffman_Tree<T>::initial()
{
   
    //cout << heapSize << endl;
    for (int root = heapSize / 2; root >= 1; root--)
        //�����һ���к��ӵĽ�㿪ʼ���жѻ�
    {
        //cout << "debug!" << endl;
        HoffmanTree_Node<T>* rootElement = Heap[root];
        //ΪrootElementѰ�Һ��ʵ�λ��
        int child = root * 2;
        while (child <= heapSize)
        {
            
            //Ѱ�ҽ�С���ֵܽ��
            //if ((Heap[child]->weight > Heap[child + 1]->weight) && (child < heapSize))
            if ((child < heapSize) &&(Heap[child]->weight > Heap[child + 1]->weight))
            {
                child++;
            }
            /*
            if (child < heapSize)
            {
                if (Heap[child]->weight > Heap[child + 1]->weight)
                {
                    child++;
                }
            }
            */
            if (rootElement->weight <= Heap[child]->weight)
            {
                
                break;
            }
            /*
            else
            {
                cout << "here3" << endl;
                Heap[child / 2] = Heap[child]; //�����ӽ���븸�׽����н���
                child *= 2;
            }
            */
            
            Heap[child / 2] = Heap[child]; //�����ӽ���븸�׽����н���
            child *= 2;
        }
        Heap[child / 2] = rootElement;
    }
    //output();
}
template <class T>
void Hoffman_Tree<T>::push(HoffmanTree_Node<T>* TreeNode)
{
    int currentNode = ++heapSize;
    while (currentNode != 1 && Heap[currentNode / 2]->weight > TreeNode->weight)
    {
        Heap[currentNode] = Heap[currentNode / 2];
        currentNode /= 2;
    }
    Heap[currentNode] = TreeNode;
    // output();
}
template <class T>
void Hoffman_Tree<T>::pop()
{
    HoffmanTree_Node<T>* lastElement = Heap[heapSize--];
    int currentNode = 1, child = 2;
    while (child <= heapSize)
    {
        if (child < heapSize && Heap[child]->weight > Heap[child + 1]->weight)
        {
            child++;
        }
        if (lastElement->weight <= Heap[child]->weight)
        {
            break;
        }
        else
        {
            Heap[currentNode] = Heap[child];
            currentNode = child;
            child *= 2;
        }
    }
    Heap[currentNode] = lastElement;
    // output();
}
//������С�ѽ���������ѡ����С����������㣬Ȼ������ǵ�Ȩ�غ���Ϊ���ǵĸ��׽��
template <class T>
void Hoffman_Tree<T>::construct_Tree()
{
    //cout << heapSize << endl;
    HoffmanTree_Node<T>* x, * y, * z;
    if (heapSize == 1)
    {
        x = top();
        pop();
        z = new HoffmanTree_Node<T>(x->weight, x, NULL);
        push(z);
    }
    while (heapSize != 1)
        //��heap��ֻʣһ��Ԫ��ʱֹͣѭ��
    {
        x = top();
        pop();
        y = top();
        pop();
        //ȡ���������������
        z = new HoffmanTree_Node<T>(x->weight + y->weight, x, y);
        //��x,y��Ϊz����������,������������
        push(z);
    }
}
template <class T>
void Hoffman_Tree<T>::output()
{
    for (int i = 1; i <= heapSize; i++)
    {
        cout << Heap[i]->weight << " ";
    }
    cout << endl;
}
int sum = 0; //����Ȩ��
template <class T>
void Hoffman_Tree<T>::sum_Length(HoffmanTree_Node<T>* t, int n)
{
    if (t != NULL)
    {
        if (t->left == NULL && t->right == NULL)
        {
            sum += n * t->weight;
        }
        sum_Length(t->left, n + 1);
        sum_Length(t->right, n + 1);
    }
}
int main()
{
    // cout << " Hoffman_Tree is constructing!" << endl;
    string str;
    cin >> str;

    //�����ÿ��Ӣ����ĸ��Ȩ��
    int* character = new int[26]; //������ʾ26��Ӣ����ĸ
    for (int i = 0; i < 26; i++)
    {
        character[i] = 0;
    } //��ʼ��
    for (int i = 0; i < str.length(); i++)
    {
        character[(int)str[i] - 97]++;
    }
    //�������ַ���Ƶ��
    int not_null_number = 0; //����¼�ж��ٸ��ַ���������
    for (int i = 0; i < 26; i++)
    {
        if (character[i] != 0)
        {
            not_null_number++;
        }
    }
    //Ӣ����ĸ���չ��ϵ�Ĭ��˳��������������
    int* weight_character = new int[not_null_number];
    int j = 0;
    for (int i = 0; i < 26; i++)
    {
        if (character[i] != 0)
        {
            weight_character[j] = character[i];
            j++;
        }
    }
    /*
    for (int i = 0; i < not_null_number; i++)
    {
        cout << weight_character[i] << " ";
    }
    cout << endl;
    */
    //������������
    Hoffman_Tree<int> h(weight_character, not_null_number);
    //h.output();
    h.initial(); //��ʼ��Ϊ��С��
    //h.output();
    h.construct_Tree();
    //h.sum_Length(h.top(), 0);
    h.sum_Length(h.top(), 0);
    cout << sum << endl;
    delete[] weight_character;
    delete[] character;
    return 0;
}
// aaaaaabbcccdddeeeefffffffff
//asdfghjklzxcvbnmqwertyuiopaaaaa

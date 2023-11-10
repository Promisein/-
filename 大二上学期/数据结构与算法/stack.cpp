#include<iostream>
#include<iomanip>
using namespace std;
template<class T>
class arraystack
{
public:
	arraystack(int initialCapocity = 10);   //���캯������ʼջ�Ĵ�СΪ10
	~arraystack() { delete [] element; }       //��������
	void push(const T& theElement);               //��ջ��ѹ��Ԫ��
	void pop();                             //ջ��ɾ������
	bool if_empty()
	{
		if (stackTop == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	T& top()
	{
		if (stackTop == -1)
		{
			exit(2);
		}
		return element[stackTop];
	}
private:
	int stackTop;       //��ǰջ��
	int size = 10;     //ջ�Ĵ�С
	T* element;   // Ԫ������
};
template<class T>
arraystack<T>::arraystack(int initialCapocity)
{
	size = initialCapocity;
	element = new T[size];
	stackTop = -1;
}
template<class T>
void arraystack<T>::push(const T& theElement)                 //��ջ��ѹ��Ԫ��
{
	
	if (stackTop == size - 1)              //ջԪ������
	{
		
		T* newElement = new T[size*2];
		for (int i = 0; i < size; i++)
		{
			newElement[i] = element[i];
		}
		size = size * 2;
		delete element;
		element = newElement;
		
	}
	
	element[++stackTop] = theElement;
	//cout << "pushing! " << stackTop << " " <<element[stackTop] << endl;
}
template<class T>
void arraystack<T>::pop()
{
	if (stackTop == -1)
	{
		exit(1);	
	}
	element[stackTop--].~T();    //T����������a
}
void calculate(arraystack<double>& array, arraystack<char>& c)
{
	if (c.top() == '(')
	{
		return;
	}
	double a, b;
	a = array.top();
	array.pop();
	b = array.top();
	array.pop();
	//������ջ���������ֵ����������������ջ���׸��ַ����������м��㣬���ҽ�����Ľ������ѹ������ջ��
	switch (c.top())     
	{
	case '+':
	{
		double sum = a + b;
		array.push((a+b));
		break;
	}
	case'-':
	{
		double subtraction = b - a;
		array.push(subtraction);
		break;
	}
	case'*':
	{
		double mul = a * b;
		array.push(mul);
		break;
	}
	case'/':
	{
		double division = b / a;
		array.push(division);
		break;
	}
	default:
		break;
	}
	c.pop();                              //����������������ջ
}
void compute(char* operate, int Length)      //���ַ����������ֺͼ����ַ�      
{
	//cout << "the equation is calculating!" << endl;
	bool minus = false;                        //�ж��Ƿ�Ϊ����
	arraystack<double> a(Length);
	arraystack<char> c(Length);
	//cout << "here" << endl;
	for (int i = 0; i < Length; i++)
	{
		//cout << "index_here" << endl;
		if (operate[i] >= '0' && operate[i] <= '9')          //������Ϊ����
		{
			double value = operate[i] - '0';
			while (operate[i + 1] >= '0' && operate[i + 1] <= '9')
			{
				value = 10 * value + (operate[i + 1] - '0');
				i++;
			}
			if (minus)
			{
				value = -value;
				minus = false;
			}
			a.push(value);
		}
		else              //������Ϊ�ַ�
		{
			if ((i == 0 || operate[i - 1] == '(') && operate[i] == '-')  //������ͷ���������ڵĸ���������
			{
				minus = true;
				continue;
			}
			if (operate[i] == '-' || operate[i] == '+')
			{
				//cout << "char_here" << endl;
				if (c.if_empty() || c.top() == '(')
				{
					c.push(operate[i]);
				}
				else
				{
					calculate(a, c);            //�����������ȥ����
					if (!c.if_empty() && c.top() != '(')
					{
						calculate(a, c);        //����������û��������
					}
					c.push(operate[i]);
				}
			}
			if (operate[i] == '/' || operate[i] == '*')
			{
				if (c.if_empty() || c.top() == '(')
				{
					c.push(operate[i]);
				}
				else
				{
					if (c.top()=='+'||c.top()=='-')
					{
						c.push(operate[i]);                    //��Ϊ�˷����㼶����ڼӷ����Ȱѳ˳�ѹ��ջ
					}
					else
					{
						if (c.top() == '*' || c.top() == '/')
						{
							calculate(a, c);                      //�����ͬ�����㣬�������ѹ��
							c.push(operate[i]);
						}
					}
				}
			}
			if (operate[i] == '(')
			{
				c.push(operate[i]);           //������ֱ����ջ
			}
			if (operate[i] == ')')                       //���������ţ��������ڽ�������ֱ�����㵽������
			{
				while (c.top() != '(')
				{
					calculate(a, c);
				}
				c.pop();                    //�����ų�ջ
			}
		}
		if (operate[i] == NULL)
		{
			break;
		}
	}
	for (; !c.if_empty();)
	{
		calculate(a, c);                            //����ʣ����
	}
	cout << setprecision(2) <<fixed<< a.top() << endl;
}
int main()
{
	//cout << "Stack is constucting!" << endl;
	int n;
    cin >> n;
	/*
	string operate;
	for (int i = 0; i < n; i++)
	{
		cin >> operate;
		int size = operate.size();
		//cout << size << endl;
		compute(operate, size);
	}
	*/
	for (int i = 0; i < n; i++)
	{
		char a[2000];
		cin >> a;
		compute(a, 2000);
	}
	
	return 0;
}
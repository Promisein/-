#include<iostream>
using namespace std;
class Student
{
public:
	~Student() {};
	void input_name(string &newname) { name = newname; }
	void input_phone(string &nphone) { telephone = nphone; }
	void input_grade(int &ngrade) { grade = ngrade; }
	void input_dorm(int &ndrom) { dorm = ndrom; }
	string get_name() { return name; }
	string get_phone() { return telephone; }
	int get_grade() { return grade; }
	int get_dorm() { return dorm; }
private:
	string name;        // ѧ������
	string telephone;   //�绰����
	int grade = 0;          //�༶
	int dorm = 0;           //�����
};
template<class T>
void change_size(T*& a, int oldsize, int newsize)     //�ı�һ������ĳ���
{
	if (newsize < 0)
	{
		throw "new size must be >=0";
	}
	T* temp = new T[newsize];          //������
	int number = min(oldsize, newsize);       //��Ҫ���Ƶ�Ԫ�ظ���
	copy(a, a + number, temp);            //copy(������㣬�����յ㣬�µ����)
	delete[] a;                          //�ͷžɵĿռ�
	a = temp;
}
class Linearlist:public Student
{
public:
	Linearlist(int n = 10);             //���캯��
	~Linearlist() { delete[] stu; }     //   ����������ɾ����̬����
	void insert(string& name, string& telephone, int& grade, int& dorm);      //���뺯��
	void erase(string &name);           //ɾ������
	void edit(string& name,int item);      //�༭������nameΪ��������,itemΪ�༭��Ŀ
	bool search(string& name);           //���Һ��������ڷ���1�����򷵻�0
	int output(int& grade);               //���һ��������ŵ����ֵ
private:
	Student* stu;
	int size;          //�����С
	int index;         //����
};
Linearlist::Linearlist(int n)
{
	stu = new Student[n];         //��ʼ������Ĵ�СΪ10
	size = n;               
	index = 0;
}
void Linearlist::insert(string& name, string& telephone, int& grade, int& dorm)
{
	if (index == size)
	{
		change_size(this->stu, this->size, size * 2);           //���鳤������ԭ��������
		this->size = this->size * 2;
	}
	stu[index].input_name(name);
	stu[index].input_phone(telephone);
	stu[index].input_grade(grade);
	stu[index].input_dorm(dorm);
	index++;
}
void Linearlist::erase(string& name)
{
	int i = 0;
	for (i = 0; i < this->index && this->stu[i].get_name() != name; i++)
	{
		//������Ҫɾ����Ԫ�ض�Ӧ��������i"
	}
	/*while (stu[i].get_name() != name && i < size)
	{
		i++;
	}*/
	copy(stu + i + 1, stu + index, stu + i); //copy(������㣬�����յ㣬�µ����)
	stu[--index].~Student();       //������������
}
void Linearlist::edit(string& name, int item)
{
	int i = 0;
	for (i = 0; i < this->index && this->stu[i].get_name() != name; i++)
	{
		//������Ҫ��������Ӧ��������i"
	}
	//1.telephone
	//2.grade
	//3.drom
	if (item == 1)
	{
		string new_telephone;
		cin >> new_telephone;
		stu[i].input_phone(new_telephone);
	}
	if (item == 2)
	{
		int new_grade;
		cin >> new_grade;
		stu[i].input_grade(new_grade);
	}
	if (item == 3)
	{
		int new_drom;
		cin >> new_drom;
		stu[i].input_dorm(new_drom);
	}
}
bool Linearlist::search(string& name)
{
	int i = 0;
	for (i = 0; i < this->index && this->stu[i].get_name() != name; i++)
	{
		//������Ҫɾ����Ԫ�ض�Ӧ��������i"
	}
	if (i >= index)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
int Linearlist::output(int& grade)
{
	int sum = 0;
	for (int i = 0; i < index; i++)
	{
		if (stu[i].get_grade() == grade)
		{
			sum ^= stu[i].get_dorm();
		}
	}
	return sum;
}
int main()
{
	//0.����    1.ɾ��     2.�༭     3.����    4.����༶��Ϣ
	int n, mode;    // nΪ����������modeΪ����ģʽ
	cin >> n;
	string name, telephone;
	int grade, dorm;
	Linearlist l;
	int* a = new int[n];     //�����ʽ��������������ֵ�����
	int index = 0;           //������������
	for (int i = 0; i < n; i++)
	{
		cin >> mode;
		switch (mode)
		{
		case 0:
			cin >> name;
			cin >> telephone;
			cin >> grade;
			cin >> dorm;
			l.insert(name, telephone, grade, dorm);
			break;
		case 1:
			cin >> name;
			l.erase(name);
			break;
		case 2:
			int item;          //�༭��Ŀ�� 1.telephone    2.grade     3.drom
			cin >> name;
			cin >> item;
			l.edit(name, item);
			break;
		case 3:
			cin >> name;
			a[index] = l.search(name);
			index++;
			break;
		case 4:
			cin >> grade;
			a[index] = l.output(grade);
			index++;
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < index; i++)
	{
		cout << a[i] << endl;
	}
	delete[] a;
	return 0;
}
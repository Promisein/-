#include<iostream>
using namespace std;
/*
  （1）定义一个抽象类Animal，该类中可以存放动物的名字，并有一个纯虚函数Identify用于显示动物的种类和名字。将析构函数声明为虚函数。
  （2）定义两个类Cat、Dog，都继承自Animal，并重载Identify函数，显示动物的种类及名字。
  （3）定义一个Tiger类，继承自Cat，重载Identify函数，显示动物的种类和名字。
  （4）定义一个动物园类Zoo，管理动物。类Zoo的定义和实现可以参照下面的代码。注意指针虚函数的用法。
*/
class Animal
{
public:
	string name;
	virtual void Identify() = 0;//纯虚函数
	virtual ~Animal();
};

class Cat :public Animal
{
protected:
	string kind;
public:
	Cat() {}
	Cat(string name)
	{
		this->name = name;
	}
	void Identify()
	{
		cout << "名字：" << name << "种类：" << kind << endl;
	}
};

class Dog :public Animal
{
protected:
	string kind;
public:
	Dog(string name)
	{
		this->name = name;
	}
	void Identify()
	{
		cout << "名字：" << name << "种类：" << kind << endl;
	}
};
class Tiger :public Cat
{
private:
	string kind;
public:
	Tiger(string name)
	{
		this->name = name;
	}
	void Identify()
	{
		cout << "名字：" << name << "种类：" << kind << endl;
	}
};
class Zoo
{
public:
	Zoo(unsigned int max);		//构造函数，max为最多能圈养的动物数
	~Zoo() { delete residents; }  	//析构函数
	unsigned int Accept(Animal* d);  //接收动物
	void ListAnimals();   		//显示动物园所有的动物
private:
	unsigned int maxanimals;   //动物园最多能圈养的动物数
	unsigned int numanimals;   //动物园当前圈养的动物数
	Animal** residents;       //指向动物园圈养的动物对象的指针数组
};
Zoo::Zoo(unsigned int max)
{
	residents = new Animal * [max];
	maxanimals = max;
	numanimals = 0;
}
unsigned int Zoo::Accept(Animal* d)
{
	if (numanimals == maxanimals)
	{
		cout << "动物园已满" << endl;
	}
	else
	{
		residents[numanimals] = d;
		numanimals++;
	}
	return numanimals;
}
void Zoo::ListAnimals()
{
	for (int i = 0;i < numanimals;i++)
		residents[i]->Identify();
}
int main()
{
	Cat cat("cc");
	Dog dog("dd");
	Tiger tiger("tt");
	Tiger mtiger("mtt");
	Zoo zoo(5);
	zoo.Accept(&cat);
	zoo.Accept(&dog);
	zoo.Accept(&tiger);
	zoo.Accept(&mtiger);
	zoo.ListAnimals();
	return 0;
}
#include<iostream>
#include<vector>
using namespace std;
struct matrixTerm    // ���������
{
	int row = 0;        //�������
	int col = 0;         //�������
	int value = 0;       //����Ԫ��
	matrixTerm& operator = (matrixTerm& a)
	{
		row = a.row;
		col = a.col;
		value = a.value;
		return* this;
	}    // ���غ���������渳ֵ���򻯴���
};
class sparse_matrix          //ϡ�������
{
public:
	sparse_matrix& operator = (sparse_matrix &a);  //���� = �������ĸ�ֵ����
	void addElements(int &n);      //���Ԫ�صĺ���  // nΪԪ�ظ���
	void inputElements(int r, int c, int v);
	sparse_matrix(int r, int c);             //���캯��
	~sparse_matrix() { delete[] element; }   //��������
	void reset(int r, int c);                //���ú���
	void multiply(sparse_matrix& a);         //����˷�
	void add(sparse_matrix& Q);              //����ӷ�
	void transpose();                        //ת�ú���
	void output();                           //�������
private:
	int rows = 0,
		cols = 0,
		Terms = 0;                            //�������Ԫ�ظ���
	matrixTerm* element;                       //  ��0���
};
sparse_matrix& sparse_matrix::operator=(sparse_matrix& a)                     //���� = �������ĸ�ֵ����
{
	rows = a.rows;
	cols = a.cols;
	Terms = a.Terms;
	for (int i = 0; i < a.Terms; i++)
	{
		element[i].value = a.element[i].value;
		element[i].col = a.element[i].col;
		element[i].row = a.element[i].row;

	}
	return *this;
}
void sparse_matrix::addElements(int &n)
{
	int theCol, theRow, theValue;
	for (int i = 0; i < n; i++)
	{
		cin >> theCol >> theRow >> theValue;
		element[i].col = theCol;
		element[i].row = theRow;
		element[i].value = theValue;
	}
	this->Terms = n;
}
void sparse_matrix::inputElements(int r, int c, int v)
{
	element[Terms].col = c;
	element[Terms].row = r;
	element[Terms].value = v;
	Terms++;
}
sparse_matrix::sparse_matrix(int r, int c)
{
	rows = r;
	cols = c;
	element = new matrixTerm[240000];
	//element = new matrixTerm[rows * cols];
}
void sparse_matrix::reset(int r, int c)
{
	rows = r;
	cols = c;
	Terms = 0;
	int index = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			int input_element;
			cin >> input_element;
			if (input_element != 0)
			{
				element[index].row = i + 1;
				element[index].col = j + 1;
				element[index].value = input_element;
				index++;
				Terms++;
			}
		}
	}
}
void sparse_matrix::multiply(sparse_matrix& a)
{
	
	if (cols != a.rows)
	{
		*this = a;
		cout << -1 << endl;
		return;
	}
	else
	{
		sparse_matrix result(rows, a.cols);    ///����˷�����ľ���
		result.Terms = 0;                         //���ó�ʼ�������ĳ�ʼ��С
		int result_index = 0;                     //������ǽ�����������

		//������ת����ͬ���죬��þ����ÿ���С���Ԫ�ظ������Լ�ÿ�е�һ����0Ԫ����element�е�����
		int* row_number = new int[rows + 1];  //������з���Ԫ�صĸ���
		int* row_first = new int[rows + 1];   //ÿ�е�һ����0Ԫ����element�е�����

		//��ʼ����������
		for (int i = 0; i <= rows; i++)
		{
			row_number[i] = 0;
		}
		for (int i = 0; i <= rows; i++)
		{
			row_first[i] = -1;          //�����i��û��Ԫ��Ĭ��Ϊ-1��
		}
		
		//��ֵ��������
		for (int i = 0; i < Terms; i++)
		{
			row_number[element[i].row]++;
		}
		row_first[1] = 0;        //��һ�еĵ�һ��Ԫ������Ӧ�ĵ�һ����0Ԫ�ص�������Ϊ0��
		for (int i = 2; i <= rows; i++)
		{
			row_first[i] = row_first[i - 1] + row_number[i - 1];
		}

		//�����ۼӽ�������飬�����СΪ a.cols + 1 ,ӦΪ��������Ϊ0
		int* sum = new int[a.cols + 1];
		for (int i = 0; i <= a.cols; i++)
		{
			sum[i] = 0;                      //��ʼ���ۼӽ��
		}
		
		//�Ż����룬����ÿ�α����ұ�����Ĵ���
		// ��¼�ұ߾���ÿ�е�ֵ
		int* right_colNumber = new int[a.cols + 1];        //����a���ұ߾��󣩵�ÿһ�з���Ԫ�ص�ֵ�ĸ���
		for (int i = 0; i <= a.cols; i++)
		{
			right_colNumber[i] = 0;                         //��ʼ��
		}
		for (int i = 0; i < a.Terms; i++)
		{
			right_colNumber[a.element[i].col]++;
		}

		int* right_colFirst = new int[a.cols + 1];          //����a���ұ߾��󣩵�ÿһ�ж�Ӧ������
		for (int i = 0; i <= a.cols; i++)
		{
			right_colFirst[i] = 0;                         //��ʼ��
		}
		right_colFirst[1] = 0;
		for (int i = 2; i <= a.cols; i++)
		{
			right_colFirst[i] = right_colFirst[i - 1] + right_colNumber[i - 1];
		}

		//��ʼ�˷�����
		for (int i = 1; i <= rows; i++)          //����ǰ�����ÿһ��
		{  
			if (row_first[i] != -1)             //����һ�в�Ϊ0�ǽ��г˷�
			{
				for (int k = 1; k <= row_number[i]; k++)    //����ÿһ�в�Ϊ0��Ԫ��
				{
					matrixTerm& rowElement = element[row_first[i]++];

					for (int j = right_colFirst[rowElement.col]; j < right_colFirst[rowElement.col] + right_colNumber[rowElement.col]; j++)              
					{//ѭ���ľ�׼��λ������׼��λ��������Ҫ���Ԫ�أ��� right_colFirst[rowElement.col] �� right_colFirst[rowElement.col] + right_colNumber[rowElement.col];֮���Ԫ�ص��е���������rowElement.col
						matrixTerm& colElement = a.element[j];
						sum[colElement.col] += rowElement.value * colElement.value;
					}
					/*
					for (int j =0; j < a.Terms; j++)                              //������߾����ÿһ�е�Ԫ�أ�����һ���ұߵľ��� (���ﵼ�����㳬ʱ��)��ÿ�α���һ�ξ���̫��ʱ��
					{
						int mutiplyed_number = 0;
						matrixTerm& colElement = a.element[j];
						if (rowElement.row == i && rowElement.col == colElement.row)           //ȷ��Ҫ���˷���λ�ã�ȷ���ڵ�i�У��������Ԫ�ص������������ұߵ�������
						{
							sum[colElement.col] += rowElement.value * colElement.value;
							mutiplyed_number++; 
						}
						if (mutiplyed_number == right_colNumber[i])
						{
							break;
						}
					}
					*/
				}
				//�õ���ÿһ���ۼӵĽ��������������result��
				for (int k = 1; k <= a.cols; k++)
				{
					if (sum[k] != 0)          //�ۼӵĽ��������0����������
					{
						result.element[result_index].row = i;            //��߾���ĵ�i��
						result.element[result_index].col = k;             //�ұ߾�������Ӧ�ĵ�k��
						result.element[result_index].value = sum[k];
						result.Terms++;
						result_index++;
					}
				}
				//��ʼ���ۼ�����
				for (int k = 1; k <= a.cols; k++)
				{
					sum[k] = 0;
				}
			}
		}
		*this = result;
	}
}
void sparse_matrix::add(sparse_matrix& Q)   //����ӷ�
{
	//����Ϸ���
	if (rows != Q.rows || cols != Q.cols)
	{
		*this = Q;                 //P + Q, P���Ϸ�����Q��ֵ��P
		cout << -1 << endl;
		return;
	}
	//���ý�����������
	sparse_matrix result(rows, cols);
	int result_size = 0;

	//���������(���������������򵥵ĵ�����)   //���ڴ������Ƶ�ʱ����Գ��������� : vector
	int it = 0;
	int iQ = 0;
	int itEnd = Terms;
	int iQEnd = Q.Terms;

	//����*this��Q������ص������
	while (it != itEnd && iQ != iQEnd)
	{ 
		//����������������
		int tIndex = element[it].row * cols + element[it].col;
		int QIndex = Q.element[iQ].row * cols + Q.element[iQ].col;
		if (tIndex < QIndex)
		{
			//cout << "tIndex < QIndex" << endl;
			result.element[result_size++] = element[it];
			//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
			it++;
		}
		else
		{
			if (tIndex == QIndex)
			{//��ͬһλ��
				if (element[it].value + Q.element[iQ].value != 0)
				{//���ҽ����Ͳ�Ϊ0�ǲ���
					//cout << "tIndex == QIndex" << endl;
					//cout << element[it].row << " " << element[it].row << " " << element[it].value << endl;
					matrixTerm myTerm;
					myTerm.col = element[it].col;
					myTerm.row = element[it].row;
					myTerm.value = element[it].value + Q.element[iQ].value;
					result.element[result_size++] = myTerm;
					//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
					/*
					result.element[result_size].col = element[it].col;
					result.element[result_size].row = element[it].row;
					result.element[result_size].value = element[it].value + Q.element[iQ].value;
					result_size++;
					*/
				}
				it++;
				iQ++;
			}
			else
			{
				//cout << "tIndex > QIndex" << endl;
				result.element[result_size++] = Q.element[iQ];
				//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
				iQ++;
			}
		}
	}
	//����ʣ����
	for (; it != itEnd; it++)
	{
		result.element[result_size++] = element[it];
		//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
	}
	for (; iQ != iQEnd; iQ++)
	{
		result.element[result_size++] = Q.element[iQ];
		//cout << result.element[result_size - 1].row << " " << result.element[result_size - 1].col << " " << result.element[result_size - 1].value << endl;
	}
	result.Terms = result_size;
	*this = result;
}
void sparse_matrix::transpose()
{
	sparse_matrix b(cols, rows);
	b.Terms = Terms;
	b.cols = rows;
	b.rows = cols;
	int* colSize = new int[cols + 1]; // ��i�еķ�0Ԫ�ظ���
	int* rowNext = new int[cols + 1]; // ��i���׸���0Ԫ����b�е�����
	// ��ʼ��
	for (int i = 1; i <= cols; i++)
	{
		colSize[i] = 0;
	}
	for (int i = 0; i < Terms; i++)
	{
		colSize[element[i].col]++;
	}
	/*
	for (int i = 1; i <= cols; i++)
	{
		cout << colSize[i] << " ";
	}
	cout << endl;
	*/
	// Ѱ��b��ÿһ�е���ʼ��
	rowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
	{
		rowNext[i] = rowNext[i - 1] + colSize[i - 1];
	}
	/*
	for (int i = 1; i <= cols; i++)
	{
		cout << rowNext[i] << " ";
	}
	cout << endl;
	*/
	// ʵʩ��*this��b��ת�ø���
	for (int i = 0; i < Terms; i++)
	{
		int j = rowNext[element[i].col];
		rowNext[element[i].col]++;
		b.element[j].row = element[i].col;
		b.element[j].col = element[i].row;
		b.element[j].value = element[i].value;
	}
	//b.output();
	*this = b;                  //��Ϊ��û�����ء� = �����ţ����Ƶ�ʱ�����
}
void sparse_matrix::output()       // �������
{
	int number = 0;
	cout << rows << " " << cols << endl;   //�������������
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (number < Terms  && element[number].row == i + 1 && element[number].col == j + 1)
			{
				cout << element[number].value << " ";
				number++;
			}
			else
			{
				cout << 0 << " ";
			}
		}
		cout << endl;
	}
}
int main()
{
	sparse_matrix x(0, 0);    //����ϡ��������
	int w;             //������
	cin >> w;
	int decision;       //����ģʽ
	int row, col, t;   //���У��;����з�0Ԫ�صĸ���
	for (int i = 0; i < w; i++)
	{
		cin >> decision;
		switch (decision)
		{
		case 1:
		{
			//reset matrix
			cin >> row >> col;
			x.reset(row, col);
			break;
		}
		case 2:
		{
			//multiply
			cin >> row >> col >> t;
			sparse_matrix mul(row, col);
			for (int i = 0; i < t; i++)
			{
				int r, c, v;
				cin >> r >> c >> v;
				mul.inputElements(r, c, v);
			}
			x.multiply(mul);
			//cout << " multiply matrix " << endl;
			break;
		}
		case 3:
		{
			//add
			cin >> row >> col >> t;
			//����ͨ����������Ԫ�ش�С��ֵ���޷�ͨ���������˽�г�Ա�����Ի�����һ������
			sparse_matrix add_matrix(row, col);   
			//add_matrix.addElements(t);
			for (int i = 0; i < t; i++)
			{
				int r, c, v;
				cin >> r >> c >> v;
				add_matrix.inputElements(r, c, v);
			}
			//add_matrix.output();
			x.add(add_matrix);
			break;
		}
		case 4:
		{
			x.output();
			break;
		}
		case 5:
			//transpose matrix
			x.transpose();
		default:
			break;
		}
	}
	return 0;
}
/*
7
1
3 4
1 0 0 2
0 3 0 4
5 0 0 6

3
3 4 6
1 2 1
1 4 2
2 1 3
2 3 4
3 1 5
3 3 6
*/
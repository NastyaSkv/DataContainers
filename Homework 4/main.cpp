//cop. BinaryTree
//1. � ����� Tree �������� ��������� ������ : minValue(); maxValue(); count(); sum(); avg(); depth(); erase();
//2. ���������� ����� ���� ������� ��� ������������� �������� ����� ������ :

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------\n"

class Tree
{
	class Element
	{
		int Data;                    //����. ��������
		Element* pLeft, * pRight;    //������ ��������
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;
	unsigned int size, summa, dep;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		//size = 0;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void minValue(Element* Root)             //MIN ��������
	{
		if (Root == nullptr)return;
		minValue(Root->pLeft);
		if (Root->pLeft == nullptr)cout << Root->Data << tab;
	}

	void maxValue(Element* Root)             //MAX ��������
	{
		if (Root == nullptr)return;
		maxValue(Root->pRight);
		if (Root->pRight == nullptr)cout << Root->Data << tab;
	}

	int count(Element* Root)                 //���������� ���������
	{
		if (Root == nullptr)return size;
		count(Root->pLeft);
		size++;
		count(Root->pRight);
	}

	int sum(Element* Root)                 //����� ���������
	{
		if (Root == nullptr)return summa;
		sum(Root->pLeft);
		summa += Root->Data;
		sum(Root->pRight);
	}

	double avg(Element* Root)                 //������� �������������� ���������
	{
		return ((double)summa / size);
	}

	int depth(Element* Root)
	{
		if (Root == nullptr)return dep;
		dep++;
		depth(Root->pLeft);
	}

	void erase(Element* Root, int element)
	{
		/*if (this->Root == nullptr)this->Root = Root->pRight;
		if (Root == nullptr)return;*/
		if (element < Root->Data)
		{
			if (Root->Data != element)
			{
				erase(Root->pLeft, element);
			}
			else if (Root->Data == element)
			{
				if (Root->pLeft = nullptr)
				{
					Root->Data = 0;return;
				}
				else
				{
					Root->Data = Root->pLeft;
				}
			}
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n, element;
	cout << "������� ���������� ���������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;

	cout << "����������� ��������: ";
	tree.minValue(tree.getRoot());
	cout << endl << "������������ ��������: ";
	tree.maxValue(tree.getRoot());
	cout << endl << "���������� ���������: ";
	cout << tree.count(tree.getRoot()) << endl;
	cout << "����� ���������: ";
	cout << tree.sum(tree.getRoot()) << endl;
	cout << "������� �������������� ���������: ";
	cout << tree.avg(tree.getRoot()) << endl;
	cout << "������� ������: ";
	cout << tree.depth(tree.getRoot()) << endl;
	cout << "������� �������� ���������� ��������: "; cin >> element;
	tree.erase(tree.getRoot(), element);
	tree.print(tree.getRoot());
	cout << endl;
	/*Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();*/
}
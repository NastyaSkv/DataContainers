//cop. BinaryTree
//1. В класс Tree добавить следующие методы : minValue(); maxValue(); count(); sum(); avg(); depth(); erase();
//2. Обеспечить вызов всех методов без необходимости передачи корня дерева :

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
		int Data;                    //знач. элемента
		Element* pLeft, * pRight;    //адреса потомков
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
	void minValue(Element* Root)             //MIN значение
	{
		if (Root == nullptr)return;
		minValue(Root->pLeft);
		if (Root->pLeft == nullptr)cout << Root->Data << tab;
	}

	void maxValue(Element* Root)             //MAX значение
	{
		if (Root == nullptr)return;
		maxValue(Root->pRight);
		if (Root->pRight == nullptr)cout << Root->Data << tab;
	}

	int count(Element* Root)                 //количество элементов
	{
		if (Root == nullptr)return size;
		count(Root->pLeft);
		size++;
		count(Root->pRight);
	}

	int sum(Element* Root)                 //сумма элементов
	{
		if (Root == nullptr)return summa;
		sum(Root->pLeft);
		summa += Root->Data;
		sum(Root->pRight);
	}

	double avg(Element* Root)                 //среднее арифметическое элементов
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
		if (element <= Root->Data)
		{
			if (Root->Data != element)
			{
				erase(Root->pLeft, element);
			}
			else if (Root->Data == element)
			{
				if (Root->pLeft = nullptr)
				{
					Root->Data = 0;
					delete Root; 
					return;
				}
				else
				{
					this->Root = Root->pLeft;
					delete Root;
					return;
				}
			}
		}
		else
		{
			if (Root->Data != element)
			{
				erase(Root->pRight, element);
			}
			else if (Root->Data == element)
			{
				if (Root->pRight = nullptr)
				{
					Root->Data = 0; 
					delete Root; 
					return;
				}
				else
				{
					this->Root = Root->pRight; 
					delete Root;
					return;
				}
			}
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
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;

	cout << "Минимальное значение: ";
	tree.minValue(tree.getRoot());
	cout << endl << "Максимальное значение: ";
	tree.maxValue(tree.getRoot());
	cout << endl << "Количество элементов: ";
	cout << tree.count(tree.getRoot()) << endl;
	cout << "Сумма элементов: ";
	cout << tree.sum(tree.getRoot()) << endl;
	cout << "Среднее арифметическое элементов: ";
	cout << tree.avg(tree.getRoot()) << endl;
	cout << "Глубина дерева: ";
	cout << tree.depth(tree.getRoot()) << endl;
	cout << "Введите значение удаляемого элемента: "; cin >> element;
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
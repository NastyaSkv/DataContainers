//1. В класс List добавить метод ? ? ? erase(? ? ? );
//2. Написать operator+ и MoveMethods;
//3. Проверочный код должен заработать :
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
		friend class Iterator;
		friend List operator+(const List& left, const List& right);
	}*Head, * Tail;

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
			cout  << "ItConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};

	unsigned int size;

public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		//return nullptr;
		return Tail->pNext;
	}
	//                    Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	List(List& other) :List()
	{
		*this = std::move(other);
		cout << "MoveConstructor:" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//                    Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "MoveAssignment" << this << endl;
		return *this;
	}
	//                    Adding Elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr) //частный случай
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	//                    Removing Elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
		}
		if (Index == 0)return pop_front();
		if (Index == size)return pop_back();
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index; i++)Temp = Temp->pPrev;
		}
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
		size--;
	}
	//                    Methods:
	void print()const
	{
		cout << "Голова списка:" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Хвост списка:" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Хвост списка:" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Голова списка:" << Head << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	friend class Element;
	friend List operator+(const List& left, const List& right);
};

List operator+(const List& left, const List& right)
{
	List cat = left;  //CopyConstructor
	for (List::Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}
//#define BASE_CHECK
//#define TASK_2
#define TASK_3

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите разммер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	int znach;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();
	cout << delimiter << endl;
	cout << "Введите индекс удаляемого элемента: "; cin >> znach;
	list.erase(znach);
	list.print();
#endif // BASE_CHECK

#ifdef TASK_2
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	//list.reverse_print();
	cout << delimiter << endl;

	//	List list2 = list;       //нужен CopyConstructor
	List list2;
	list2 = list;            //CopyAssignment
	list2.print();
	//list2.reverse_print();
	cout << delimiter << endl;

	List list3 = list + list2;
	list3.print();
#endif // TASK_2

#ifdef TASK_3
	List list = { 3, 5, 8, 13, 21 };
	list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
#endif // TASK_3
}
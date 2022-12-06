#include<iostream>
using namespace std;
#include<ctime>

#define tab "\t"
#define delimiter "------------------------------------------------"

class Element
{
	int Data;        //значение элемента
	Element* pNext;  //Адрес следующего элемента
	Element* pPrev;  //Адрес предыдущего элемента
	static unsigned int count; //количество элементов
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
	{
		cout << "Econstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList_2;
};

class ForwardList_2
{
	Element* Head;  //указ. на нач. эл.списка
	Element* Tail;  //указ. на посл. эл.списка
public:
	ForwardList_2() :Head(nullptr), Tail(nullptr)
	{
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList_2()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//           Adding Elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		Element* Temp_2 = Tail;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = New;
		Temp = New->pPrev;
	}

	//                  Removing elements
	void pop_front()
	{
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		Element* Temp_2 = Tail;
		
		while (Temp->pNext)Temp = Temp->pNext;
		Tail = Temp->pPrev;
		delete Temp;
		/*Element* Temp = Head;
		Element* Temp_2 = Tail;
		while (Head)
		{
			Tail = Head->pNext;
			delete Head;
			Head = Tail;
		}
		Head = Head->pNext;
		delete Head;*/
	}

	//			 Methods:
	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Ввежите размер списка: "; cin >> n;
	ForwardList_2 list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_back(1233);
	list.print();
	cout << delimiter << endl;
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
}
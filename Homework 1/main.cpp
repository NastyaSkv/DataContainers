//1. В класс ForwardList добавить метод ? ? ? erase(? ? ? ), который удаляем элемент по указанному индексу;
//2. В классе ForwardList написать деструктор таким образом, чтобы он удалял все элементы списка;
//3. Проверочный код должен заработать :
//https://github.com/okovtun/PV_224/blob/96b5d54766ae6d15e4b92493129c7af371a2bcea/DataContainers/ForwardList/main.cpp#L184
#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;        //значение элемента
	Element* pNext;  //Адрес следующего элемента
	static unsigned int count; //количество элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;   //счетчик элементов
		cout << "Econstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;   //счетчик элементов
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

unsigned int Element::count = 0;

class ForwardList
{
	Element* Head; //указатель на начальный элемент списка
	//голова явл. точкой входа в список
	unsigned int size;
public:

	ForwardList() :Head(nullptr), size(0)
	{
		//констр-р по умолчанию создает пустой список
		//Если голова указывает на 0, то список пуст
		cout << "LContructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//             Adding Elements:

	void push_front(int Data)
	{
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Пристыковываем новый элемент к началу списка:
		New->pNext = Head;
		//3) Переводим Голову на новый элемент:
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1)Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Доходим до последнего элемента списка: 
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//теперь итератор указывает на последний элемент списка,
		//и к нему можно пристыковать новый элемент
		Temp->pNext = New;
		size++;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data); //частный случай
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}
		// 1) Создаем новый элемент:
		Element* New = new Element(Data);
		// 2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
			if (Temp->pNext)Temp = Temp->pNext;
		// 3)Включаем новый элемент в список:
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//                  Removing elements
	void pop_front()
	{
		// 1) сохраняем адрес удаляемого элемента:
		Element* erased = Head;
		// 2) Исключаем элемент из списка:
		Head = Head->pNext;
		// 3) удаляем элемент из памяти:
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		// 1) Доходим до предпоследнего элемента списка:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		// 2) Удаляем последний элемент из памяти:
		delete Temp->pNext;
		// 3) Зануляем указатель на следующий элемент:
		Temp->pNext = nullptr;
		size--;
	}
	void erase (int Index)
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		if (Index == 0)return pop_front(); 
		if (Index > size)
		{
			cout << "Error: Out of range" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
			if (Temp->pNext)Temp = Temp->pNext;
		;
		Element* erased = Temp->pNext;
		Temp->pNext = erased->pNext;
		delete erased;
		size--;
	}

	void remove()
	{
		while (size)pop_front();
	}

		//		            Methods:
		void print()const
	{
		Element* Temp = Head;     //Temp - это итератор
		//итератор - указатель при помощи которого можно получить доступ
		//к элементам структуры данных
		cout << "Head:\t" << Head << endl;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //переходим на следующий элемент
		}
		cout << "Количество элементов списка:\t" << size << endl;
		cout << "Общее кол-во элементов списка:  " << Element::count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	list.push_back(1024);
	list.print();
	list.pop_back();
	list.print();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	/*list.push_back(123);
	list.print();*/
	//list.pop_back();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значения добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.remove();
}
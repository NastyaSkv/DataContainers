#include<iostream>
using namespace std;
#include<ctime>
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
#ifdef DEBUG
		cout << "Econstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;   //счетчик элементов
#ifdef DEBUG

		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);

};

unsigned int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItConstructor:\t" << endl;
	}

	Iterator operator++()
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

class ForwardList
{
	Element* Head; //указатель на начальный элемент списка
	//голова явл. точкой входа в список
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	// Constructors
	ForwardList() :Head(nullptr), size(0)
	{
		//констр-р по умолчанию создает пустой список
		//Если голова указывает на 0, то список пуст
		cout << "LContructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;//из констр-ра копир-я вызываем оператор присваивания
#ifdef DEBUG

		cout << "CopyConstructor:\t" << this << endl;
#endif // DEBUG
	}
	ForwardList(const ForwardList&& other) :ForwardList()
	{
		*this = std::move(other); //ф-я std::move() вызывает MoveAssignment
#ifdef DEBUG
		cout << "MoveCOnstructor:\t" << this << endl;
#endif // DEBUG
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//             Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		reverse();
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other) //MOVE
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Shallow copy:
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	//             Adding Elements:

	void push_front(int Data)
	{
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Пристыковываем новый элемент к началу списка:
		//New->pNext = Head;
		//3) Переводим Голову на новый элемент:
		//Head = New;
		Head = new Element(Data, Head);   //сокращенная версия
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1)Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до последнего элемента списка: 
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//теперь итератор указывает на последний элемент списка,
		//и к нему можно пристыковать новый элемент
		//Temp->pNext = New;
		Temp->pNext = new Element(Data);
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
		//Element* New = new Element(Data);
		// 2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
			/*if (Temp->pNext)*/Temp = Temp->pNext;
		// 3)Включаем новый элемент в список:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
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

	//		            Methods:
	void reverse()
	{
		ForwardList reverse;
		while(Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
		}
		this->Head = reverse.Head;
		this->size = reverse.size;
		reverse.Head = nullptr;
	}
	void print()const
	{
		//Element* Temp = Head;     //Temp - это итератор
		//итератор - указатель при помощи которого можно получить доступ
		//к элементам структуры данных
		//cout << "Head:\t" << Head << endl;
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //переходим на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка:\t" << size << endl;
		cout << "Общее кол-во элементов списка:  " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;  //CopyConstructor
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
//#define PREFORMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
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
#endif
#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();

	/*ForwardList list3 = list1 + list2;
	list3.print();*/
	ForwardList list3;
	list3 = list1 + list2;
	list3.print();
#endif
#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 }
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;

	//range-based FOR(for для диапазона, т е для контейнера)
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif
#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();
	/*for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;*/

#endif
#ifdef PREFORMANCE_CHECK



	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	cout << "List created, loading data..." << endl;
	time_t start = time(NULL);
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	time_t end = time(NULL);
	cout << "Data load complete" << endl;
	cout << "Spent time: " << end - start << endl;
	//list.print();
	cout << "Start copying" << endl;
	start = time(NULL);
	ForwardList list2 = list;
	end = time(NULL);
	cout << "End copying" << endl;
	cout << "Spent time: " << end-start << endl;
#endif // DEBUG
}
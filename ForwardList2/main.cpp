﻿#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define delimeter "\n--------------------------------------\n"
#define tab "\t"

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
	} *Head, * Tail;
	size_t size;	//size_t - это unsigned int
	//Директива typedef дает существующему типу данных новое имя:
	//typedef существующий_тип_данных новое_имя_этого_типа;
public:
	
	class Iterator {
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) : Temp(Temp) {}
		~Iterator() {}

		Iterator& operator++() {
			Temp = Temp->pNext;
			return *this;
		}

		Iterator operator++(int) {
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		Iterator operator--() {
			Temp = Temp->pPrev;
			return *this;
		}

		Iterator operator--(int) {
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		bool operator==(const Iterator& other)const {
			return this->Temp == other.Temp;
		}
		
		bool operator!=(const Iterator& other)const {
			return this->Temp != other.Temp;
		}

		int operator*() {
			return Temp->Data;
		}
	};
	
	class ReverseIterator {
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) : Temp(Temp) {}
		~ReverseIterator() {}

		ReverseIterator& operator++() {
			Temp->pPrev;
			return *this;
		}

		ReverseIterator operator++(int) {
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		ReverseIterator& operator--() {
			Temp = Temp->pNext;
			return *this;
		}
		
		ReverseIterator& operator--(int) {
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		bool operator==(const ReverseIterator& other)const {
			return this->Temp == other.Temp;
		}

		bool operator!=(const ReverseIterator& other)const {
			return this->Temp != other.Temp;
		}

		int operator*() {
			return Temp->Data;
		}
	};

	Iterator begin()const  {
		return Head;
	}

	Iterator end()const {
		return nullptr;
	}

	ReverseIterator rbegin() {
		return Tail;
	}

	
	ReverseIterator rend() {
		return nullptr;
	}


//                           Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}

	List(const std::initializer_list<int>& il) : List() {
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}

	List(const List& other) : List() {
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		*this = other;
		cout << "LCopyConstructor: " << this << endl;
	}

	~List()
	{
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

//                      Operators:

	List& operator=(const List& other) {
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyAssignment: " << this << endl;

	}

	//					Addign elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;*/
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;*/
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	
	void insert(int Data, int Index) {
		if (Index == 0)return push_front(Data);
		if (Index >= size)return push_back(Data);
		Element* Temp;
		if (Index < size / 2) {
		    Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}



	//						Removing elements:

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;

		size--;
	}

	void pop_back() {
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;

		size--;
	}

	void erase(int Index) {
		if (Index == 0)return pop_front();
		if (Index == size - 1)return pop_back();
		if (Index >= size)return;
		Element* Temp;
		if (Index < size/2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < Index; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}
	



	//						Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
};

List operator+(const List& left, const List& right) {
	List cat = left;
	for(List::Iterator it = right.begin(); it != right.end(); ++it) 
		cat.push_back(*it);
	return cat;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK


void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.reverse_print();
    //list.pop_back();

	int Data, Index;
	cout << "Enter element for add: "; cin >> Data;
	cout << "Enter index for add: "; cin >> Index;
	list.insert(Data, Index);
	list.print();
	list.reverse_print();
	int Index;
	cout << "Enter index for delete: "; cin >> Index;
	list.erase(Index);
	list.print();
	list.reverse_print();


#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)cout << i << tab; cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); --it) {
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	List list1 = { 3,5,8,13,21 };
	List list2 = { 34,55,89 };
	List list3 = list1 + list2;

	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

}
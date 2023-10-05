#include <iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define delimeter "\n--------------------------------------\n"
#define tab "\t"


class Element {
	int Data;
	Element* pNext;
	Element* pPrev;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		: Data(Data), pNext(pNext), pPrev(pPrev) {
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element() {
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class List;

} *Head, * Tail;

size_t size; // size_t - это unsigned int // Директива typedef дает существующему типу данных новое имя:
//typedef существующий_тип_данных новое_имя_этого_типа;



int Element::count = 0;

class List {
	Element* Head;
	Element* Tail;
	unsigned int size;
public:

	List() {
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List() {
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//                     Adding elements

	void push_front(int Data) {
		if (Head==nullptr && Tail == nullptr)
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

	void push_back(int Data) {
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
	}
	//                         Removing elements:

	void pop_front() {
		if (Head == nullptr && Tail== nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}

	//                         Methods:
	
	void print()const {
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Колличество элементов списка: " << this->size << endl;
		cout << "Общее колличество элементов списка: " << Element::count << endl;
	}

	void reverse_print()const {
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) {
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
	}
};

void main() {
	setlocale(LC_ALL, "");

	int n;
	cout << "Enter list size: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);

	}
	list.print();
	list.reverse_print();

}
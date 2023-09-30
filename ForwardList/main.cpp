#include <iostream>
using namespace	std;
using std::cout;
using std::cin;
using std::endl;

#define delimeter "\n--------------------------------------\n"
#define tab "\t"
//#define DEBUG

class Element {
	int Data;
	Element* pNext;
	static int count; // Объявление статической переменной
public:


	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) {
		count++;

#ifdef DEBUG
         cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		
	}

	~Element() {
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}

	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0; //определение статической переменной 

class Iterator {
	Element* Temp;
public:


	Iterator(Element* Temp = nullptr) : Temp(Temp) {
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

	}

	~Iterator() {
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

	}

	Iterator& operator++() { // Prefix increment
		Temp = Temp->pNext;
		return *this;
	}
	
	Iterator operator++(int) { // Postfix increment
		Iterator old = *this;
		Temp = Temp->pNext;
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

class ForwardList {
	//Forward - односвязный, однонаправленный 
	Element* Head;
	unsigned int size;
public:
	
	Iterator begin() {
		return Head;
	}

	Iterator end() {
		return nullptr;
	}

	ForwardList() {
		//Кнструктор по умолчанию создает пустой список.
		this->Head = nullptr; // Если список пуст, его "Голова" указывает на 0.
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}

	ForwardList(const initializer_list<int> il) : ForwardList() {

		//initializer_list - это контейнер
		//контейнер - это объект, который организует хранение других объектов в памяти
		//Как и у любого другого контейнера, у initializer_list есть методы begin() и еnd()
		//begin() - возвращает итератор на начало контейнера
		//end() - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	ForwardList(const ForwardList& other) : ForwardList() {
		/*this->Head = other.Head;*/
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		{
			push_back(Temp->Data);
		}
		cout << "LCopyConstructor\t" << this << endl;
	}

	ForwardList(ForwardList&& other) {
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "MoveConstructor\t:" << this << endl;
	}

	~ForwardList() {
		cout << "LDestructor:\t" << this << endl;
	}

	//                     Adding elements:

	void push_front(int Data) {
		//// 1) Создаем элемент для добавляемого значения:
		//Element* New = new Element(Data);

		////2) Пристыковываем элемент к списку:
		//New->pNext = Head;

		////3) Теперь новый элемент является начальным элементом списка:
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data) {

		if (Head == nullptr)return push_front(Data);

		////1) Создаем новый элемент:
		//Element* New = new Element(Data);

		//2) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		// Сейчас 'Temp' указывает на последний элемент.

		//3) Добавляем новый элемент в конец списка:
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int Data, int Index) {
		if (Index == 0)return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)return push_back(Data);
			Temp = Temp->pNext;
		}
		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}


	//                                        Removing elements:

	void pop_front() {
		Element* Erased = Head; // 1) Запоминаем адрес удаляемого элемента
		Head = Head->pNext; //2) Исключаем удаляемый элемент
		delete Erased;
		size--;
	}

	void pop_back() {
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	
	void erase(int Index) {
		if (Index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)return pop_back();
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;

	}


	//                       Methods:

	void print()const {
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Колличество элементов списка: " << this->size << endl;
		cout << "Общее колличество элементов списка: " << Element::count << endl;
		// к статическим полям принято обращаться через имя класса 
	}

	void clear() {
		while (Head)pop_front();
	}
};

#define BASE_CHECK
//#define INSERT_CHECK
//#define ERASE_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define COPY_METHODS_CHECK
//#define FORWARD_LIST_PREFORMANCE_TEST

void main() {
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Enter list size: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	//list.push_back(123);
	list.print();
	cout << delimeter << endl;
	/*list.pop_front();
	list.print();
	cout << delimeter << endl;
	list.pop_back();
	list.print();*/
	//list.clear();

#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	ForwardList list = { 3,5,8,13,21 };
	list.print();

#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST

	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << delimeter;
	for (int i : arr) {
		cout << i << tab;
	}
	cout << endl;

	for (Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}

#endif // RANGE_BASED_FOR_LIST

#ifdef INSERT_CHECK
	int index, value;
	cout << "Enter index element: "; cin >> index;
	cout << "Enter add element: "; cin >> value;
	list.insert(value, index);
	list.print();
	
#endif // INSERT_CHECK

#ifdef ERASE_CHECK
	int index;
	cout << "Enter index for delete element: "; cin >> index;
	list.erase(index);
	list.print();
	list.clear();
#endif // ERASE_CHECK

	ForwardList list1 = { 3,5,8,13,21 };
	for (int i : list1)cout << i << tab; cout << endl;
	
	ForwardList list2 = list1;  //Copy Constructor
	for (int i : list2)cout << i << tab; cout << endl;

	list1.print();
	list2.print();
}
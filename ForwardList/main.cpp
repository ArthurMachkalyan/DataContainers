#include <iostream>
using namespace	std;

#define delimeter "\n--------------------------------------\n"
#define tab "\t"

class Element {
	int Data;
	Element* pNext;
	static int count; // Объявление статической переменной
public:

	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) {
		count++;
		cout << "EConstructor:\t" << this << endl;
	}

	~Element() {
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;
};
int Element::count = 0; //определение статической переменной 

class ForwardList {
	//Forward - односвязный, однонаправленный 
	Element* Head;
public:
	ForwardList() {
		//Кнструктор по умолчанию создает пустой список.
		this->Head = nullptr; // Если список пуст, его "Голова" указывает на 0.
		cout << "LConstructor:\t" << this << endl;
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
	}

	//                                        Removing elements:

	void pop_front() {
		Element* Erased = Head; // 1) Запоминаем адрес удаляемого элемента
		Head = Head->pNext; //2) Исключаем удаляемый элемент
		delete Erased;
	}

	void pop_back() {
		/*Element* LastElement = Head;
		while (LastElement->pNext)
		{
			LastElement = LastElement->pNext;
		}
		Element* Temp = Head;
		while (Temp->pNext != LastElement)
		{
			Temp = Temp->pNext;
		}
		delete LastElement;
		Temp->pNext = NULL;*/
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;

	}
	


	//                       Methods:

	void print()const {
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		//cout << "Колличество элементов списка: " << Head->count << endl;
		cout << "Колличество элементов списка: " << Element::count << endl;
		// к статическим полям принято обращаться через имя класса 
	}

	void clear() {
		while (Head)pop_front();
	}
};

//#define BASE_CHECK
//#define INSERT_CHECK

void main() {
	setlocale(LC_ALL, "");

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
	list.clear();

#endif // BASE_CHECK

#ifdef INSERT_CHECK
	int index, value;
	cout << "Enter index add element: "; cin >> index;
	cout << "Enter adding element: "; cin >> value;
	list.insert(value, index);
	list.print();
#endif // INSERT_CHECK

}
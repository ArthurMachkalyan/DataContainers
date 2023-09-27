#include <iostream>
using namespace	std;

#define delimeter "\n--------------------------------------\n"
#define tab "\t"

class Element {
	int Data;
	Element* pNext;
public:

	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) {
		cout << "EConstructor:\t" << this << endl;
	}

	~Element() {
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;
};

class ForwardList {
	//Forward - �����������, ���������������� 
	Element* Head;
public:
	ForwardList() {
		//���������� �� ��������� ������� ������ ������.
		this->Head = nullptr; // ���� ������ ����, ��� "������" ��������� �� 0.
		cout << "LConstructor:\t" << this << endl;
	}

	~ForwardList() {
		cout << "LDestructor:\t" << this << endl;
	}

	//                     Adding elements:

	void push_front(int Data) {
		// 1) ������� ������� ��� ������������ ��������:
		Element* New = new Element(Data);

		//2) �������������� ������� � ������:
		New->pNext = Head;

		//3) ������ ����� ������� �������� ��������� ��������� ������:
		Head = New;
	}

	void push_back(int Data) {

		if (Head == nullptr)return push_front(Data);

		//1) ������� ����� �������:
		Element* New = new Element(Data);

		//2) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		// ������ 'Temp' ��������� �� ��������� �������.

		//3) ��������� ����� ������� � ����� ������:
		Temp->pNext = New;
	}

	void pop_front() {
		Element* Temp = Head->pNext;
		Head = Temp;
	}

	void pop_back() {
		Element* LastElement = Head;
		while (LastElement->pNext)
		{
			LastElement = LastElement->pNext;
		}
		Element* Temp = Head;
		while (Temp->pNext != LastElement)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = NULL;
	}
	


	//                       Methods:

	void print()const {
		Element* Temp = Head; //Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // ������� �� ��������� �������
		}
	}
};

void main() {
	setlocale(LC_ALL, "");
	
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
	list.pop_front();
	list.print();
	cout << delimeter << endl;
	list.pop_back();
	list.print();

}
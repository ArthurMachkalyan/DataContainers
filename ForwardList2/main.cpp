#include <iostream>
using namespace std;


class Element {
	int Data;
	Element* pNext;
	Element* pPrev;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev) {
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element() {
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;

};

int Element::count = 0;

class ForwardList {
	Element* Head;
	Element* Tail;
	unsigned int size;
public:

	ForwardList() {
		this->Head = nullptr;
		this->Tail = nullptr;
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList() {
		cout << "LDestructor:\t" << this << endl;
	}

	//                     Adding elements

	void push_front(int Data) {
		Element* New = new Element(Data);
		New->pPrev = nullptr;
		New->pNext = Head;
		Head = New;
		
		size++;

	}
};

void main() {
	setlocale(LC_ALL, "");


}
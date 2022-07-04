#include <iostream>
using namespace std;

template<class T>
class SmartPointer {
	T* Ptr;
	size_t* Count;

	void Detach() { //убрать сущетсвующий умный указатель у объекта
		if (!Count)
			return;
		size_t val = *Count;
		val--;
		if (!val) {
			delete Ptr;
			delete Count;
		}
		else {
			*Count = val;
		}
		Ptr = nullptr;
		Count = nullptr;
	}

	void AddRef(const SmartPointer& Other) { //копирование указателя
		Ptr = Other.Ptr;
		Count = Other.Count;
		if (*Count) {
			*Count += 1;
		}
	}

public:
	SmartPointer() { //конструктор
		Ptr = nullptr;
		Count = 0;
	}

	~SmartPointer() { //деструктор
		Release();
	}

	// ключевое слово explicit делает этот конструктор
	// непригодным для неявных преобразований
	explicit SmartPointer(T* usualPtr) {
		Ptr = usualPtr;
		Count = new size_t;
		*Count = 1;
	}

	SmartPointer(const SmartPointer& Other) { //конструктор копирования
		AddRef(Other);
	}

	void Release() { //уменьшает количество ссылок
		Detach();
	}

	T* operator->() { //Получить обычный указатель типа T
		return Ptr;
	}

	
	T* Get() //Аналогично получить обычный указатель
	{
		return Ptr;
	}

	T& operator*() { //возваращает значение, на которое указывает указатель
		return *Ptr;
	}

	SmartPointer& operator=(const SmartPointer& Other) {//переопределяем оператор присваивания
		if (this == &Other) {
			return *this;
		}
		Detach(); //уменьшаем кол-во ссылок
		AddRef(Other); //копируем
		return *this;
	}

	void Log() {
		if (Ptr) {
			cout << "Object: " << *Ptr << endl;
			cout << "Smart pointer: " << &Ptr << endl;
			cout << "Number of references: " << *Count << endl;
		}
		else {
			cout << "Object: not assigned" << endl;
			cout << "Smart pointer: " << &Ptr << endl;
			cout << "Number of references: 0" << endl;
		}
		cout << "----------------------------------------------------" << endl;
	}
};

int main()
{
	SmartPointer<int> ptr1 = SmartPointer<int>();
	ptr1.Log();
	ptr1 = SmartPointer<int>(new int(7));
	ptr1.Log();
	ptr1.Release();
	ptr1.Log();
	ptr1 = SmartPointer<int>(new int(21));
	ptr1.Log();

	int* usualPtr = ptr1.Get();

	SmartPointer<int> ptr2 = SmartPointer<int>();
	ptr2 = ptr1;
	ptr2.Log();
	ptr1.Release();
	ptr1.Log();
	ptr2.Log();
}
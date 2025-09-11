// Стандартные заголовки
#include <iostream>
using namespace std;

/*
 Описание класса стек
Выделяется память под указатель на начало массива (mem)
size - число элементов в стеке, maxsize - длина массива и максимальное число элементов.

Функции

Конструктор Stek()
выделяет память под массив из 10 элементов (по умолчанию)
вызывается по умолчаню, например при инициализации 
Stek ob;

Конструктор Stek(int kol_vo)
выделяет память под массив из заданного числа элементов
пример вызова 
Stek ob(3);
Целое число в круглых скобках определяет величину стека

Конструктор копирования
Stek(const Stek &y);

Конструкторы имеют одно и то же имя, совпадающее с именем класса, отличаются формальными параметрами

Деструктор всегда только один и не имеет параметров
~Stek()

Оператор присвоения.

int push(int x); // Функция - добавить в стек.
void show(); // Функция - показать все
int pop(int *x); // Функция взять элемент из стека

Часть функций описана прямо на месте, часть более длинных - отдельно
*/


class Stek{
private:
  int *mem;
  int size,maxsize;
public:
  Stek(){mem=new int[10]; maxsize=10;size=0;}
// в этом конструкторе мы не отследили выделение памяти и положительность величины maxsize
  Stek(int kol_vo){maxsize=kol_vo; mem=new int[maxsize]; size=0;}
  Stek(const Stek &y);
//  Stek(const Stek &y) = default;  
//  ~Stek(){ if(mem) delete [] mem; size=maxsize=0;}
  ~Stek() = default; 
  Stek& operator=(const Stek &a);                    
//  Stek& operator=(const Stek &a) = default;                    
  int push(int x){if(size<maxsize){ mem[size]=x; size++; return 0; } else{return -1;}}
  void show();
  int pop(int *x){if(size>0){ size--; *x=mem[size]; mem[size]=0; return 0;} else return -1;}
};

void Stek::show()
{   
	int i;
	for (i=0;i<size;i++) {cout  << mem[i]  << "  ";}
}

// Это конструктор копирования
// Комментарии см. Шилдт около 150 страницы
// Надо рассказать что означает (const Stek &y) в вызове функции
Stek::Stek(const Stek &y)
{
	// Это строка в реальном конструкторе НЕ НУЖНА:
	cout<<"Конструктор копирования\n";
	// Начало работы конструктора
	maxsize=y.maxsize; // определили нужную длину
	mem=new int[maxsize]; // оптимистично выделили память
	for(size=0;size<y.size;size++) mem[size]=y.mem[size]; // поэлементно скопировали и величина size получила нужное значение
}


Stek& Stek::operator =(const Stek &y)
{
	// Это строка в реальном операторе присвоения НЕ НУЖНА:
	cout<<"Оператор присвоения\n";

	if( maxsize!=y.maxsize )
	{
		if(mem) delete [] mem;
		maxsize=y.maxsize;
		mem=new int[maxsize];
	}
	for(size=0;size<y.size;size++) mem[size]=y.mem[size]; 
    return *this;
}


int main(void)
{
Stek ob(3); // Создали стек на 3 элемента (конструктор с параметром)
int i,j,x;

// Кладем в стек несколько элементов:
if(ob.push(1)!=0) cout << "стек полон\n";
ob.show();
cout << "\n-------------------------------\n";
if(ob.push(2)!=0) cout << "стек полон\n";
ob.show();
cout << "\n-------------------------------\n";
if(ob.push(3)!=0) cout << "стек полон\n";
ob.show();
cout << "\n-------------------------------\n";
if(ob.push(4)!=0) cout << "стек полон\n";
ob.show();
cout << "\n-------------------------------\n";


// Создание другого стека и его инициализация с использованием конструктора копирования
// Надо отметить, что переменная описывается (создается) где угодно, а не только в начале блока
cout << "Использование конструктора копирования:\n";
cout << "------------------------------- qw:\n";

Stek qw=ob;

qw.show();
cout << "\n-------------------------------\n";

cout << "Создание стека по умолчанию и использование оператора присвоения\n";
cout << "------------------------------- pr:\n";
Stek pr;
pr=ob;
pr.show();
cout << "\n-------------------------------\n";

if(ob.pop(&x)==0) cout << "взяли элемент x=" << x << "\n";
else cout << "стек пуст";
ob.show();
cout << "\n-------------------------------\n";
if(ob.pop(&x)==0) cout << "взяли элемент x=" << x << "\n";
else cout << "стек пуст";
ob.show();
cout << "\n-------------------------------\n";
if(ob.pop(&x)==0) cout << "взяли элемент x=" << x << "\n";
else cout << "стек пуст";
ob.show();
cout << "\n-------------------------------\n";
if(ob.pop(&x)==0) cout << "взяли элемент x=" << x << "\n";
else cout << "стек пуст";
ob.show();

cout << "\n------------------------------- qw:\n";
qw.show();
cout << "\n------------------------------- pr:\n";
pr.show();
cout<<endl;

cout << "Тест на утечку памяти\n";
cout << "(Многократное создание и удаление):\n";

Stek *ut;
ut = new Stek(15);
for(i=0;i<10;i++)ut->push(i+2);
ut->show();
cout<<endl;

for(j=0;j<1005000;j++){
	delete ut;
	ut = new Stek(1005000);
//	cout<<j<<": "<<&ut<<endl;
	for(i=1;i<10;i++)ut->push(i+j);
	}
//  cout<<&ut<<endl;
ut->show();
cout<<endl;

return 0;
}
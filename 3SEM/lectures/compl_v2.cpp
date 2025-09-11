#include <iostream>
//using namespace std;
#include "compl.h"

void f1(Complex a){double p,q; p=a.Re(); q=a.Im(); a.set(q,p);}
void f2(Complex &a){double p,q; p=a.Re(); q=a.Im(); a.set(q,p);}
void f3(Complex *a){double p,q; p=a->Re(); q=a->Im(); a->set(q,p);}

int main()
{
Complex ob1(5,6),ob2(13,-1),ob3;
std::cout<<"Адрес объекта ob1="<<&ob1<<std::endl; 
std::cout<<"Адрес объекта ob2="<<&ob2<<std::endl;
std::cout<<"Адрес объекта ob3="<<&ob3<<std::endl;
std::cout <<ob1.Re()<<std::endl;
std::cout <<ob1.Im()<<std::endl;
ob1.Re(7);
ob1.Im(-2);
std::cout <<ob1<<std::endl;
std::cout <<ob2<<std::endl;

std::cout<<"Оператор + :\n";
ob3=ob1+ob2;
std::cout <<ob3<<std::endl;

std::cout<<"Работа с дружественной функцией и методом abs\n";
std::cout <<"Это метод: "<<ob1.abs()<<std::endl;
std::cout <<"Это функция: "<<abs(ob1)<<std::endl;

std::cout<<"Работа с функциями\n";
f1(ob1);
std::cout <<ob1<<std::endl;
f2(ob2);
std::cout <<ob2<<std::endl;
f3(&ob3);
std::cout <<ob3<<std::endl;
std::cout<<"Конец работы программы\n";

return 0;
}
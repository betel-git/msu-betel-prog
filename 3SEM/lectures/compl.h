#pragma once
#include <cmath>
#include <iostream> // используется в деструкторе

class Complex{
  double re, im;
public:
  Complex(double a=0, double b=0) {re=a; im=b;}
// внимание: пример деструктора только для изучения
// в реальных задачах так писать НЕ НАДО
  ~Complex() {std::cout<<"Деструктор объекта\t"<<(void*)this<<" "<<re<<" "<<im<<"\n";}
  double Re() const { return re; }
  double Im() const { return im; }
  void Re(double a) { re=a; }
  void Im(double a) { im=a; }
  void set(double a, double b){ re=a; im=b; }
  Complex operator +(const Complex &a);
  friend std::ostream &operator<< (std::ostream &stream, const Complex &number);
  double abs() const { return std::sqrt(re*re+im*im); }
  friend double abs(const Complex &a);
};

double abs(const Complex &a)
{
	return std::sqrt(a.re*a.re+a.im*a.im);
}

Complex Complex::operator +(const Complex &a)
{
	Complex tmp;
	tmp.re=re+a.re;
	tmp.im=im+a.im;
	return tmp;
}

std::ostream& operator<< (std::ostream &stream, const Complex &number)
{
stream << "(" << number.re <<","<<number.im<<")";
return stream; 
}


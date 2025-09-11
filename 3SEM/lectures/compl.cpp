#include <iostream>
using namespace std;

class Complex{
double re, im;
public:
Complex(double a=0, double b=0) {re=a; im=b;}
Complex operator +(const Complex &a);
friend ostream &operator<< (ostream &stream, const Complex &number);
};

Complex Complex::operator +(const Complex &a)
{
	Complex tmp;
	tmp.re=re+a.re;
	tmp.im=im+a.im;
	return tmp;
}

ostream &operator<< (ostream &stream, const Complex &number)
{
stream << "(" << number.re <<","<<number.im<<")";
return stream; 
}

int main()
{
Complex ob1(5,6),ob2(13,-1),ob3;
cout <<ob1<<endl;
cout <<ob2<<endl;
ob3=ob1+ob2;
cout <<ob3<<endl;
return 0;
}
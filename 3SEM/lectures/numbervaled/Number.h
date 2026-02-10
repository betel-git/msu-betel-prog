#include <cmath>
#include <cfloat>   //  DBL_EPSILON - погрешность double около 1
//#define DBL_EPSILON   0.0001 


// число с абсолютной погрешностью
class NumberA
{
    double value, error;

public:
    // конструкторы
    NumberA(double v = 0, double e = DBL_EPSILON) : value(v), error(fabs(v)*e) {}                     
    NumberA(const NumberA &) = default;

    // деструктор
    ~NumberA() = default;                     

    // присваивание
    const NumberA & operator=(const NumberA & v) { value = v.value; error = v.error; return *this; }
    const NumberA & operator=(double v) { return *this = NumberA(v); }

    // преобразование типа
    // опасный оператор !!!! лучше его исключить
    // operator double() const { return value; }

    // получение значений
    double Value() const { return value; }
    double Error() const { return error; }

    // изменение значения
    const NumberA & operator+=(const NumberA & v);
    const NumberA & operator-=(const NumberA & v);
    const NumberA & operator*=(const NumberA & v);
    const NumberA & operator/=(const NumberA & v);
    const NumberA & operator+=(double v);
    const NumberA & operator-=(double v);
    const NumberA & operator*=(double v);
    const NumberA & operator/=(double v);
    const NumberA & operator++();
    const NumberA & operator--();
    NumberA operator++(int);
    NumberA operator--(int);

    // сравнения  // сомнительные операторы !!!!
    bool operator< (const NumberA & a) const; 
    bool operator<=(const NumberA & a) const; 
    // и т.п.

   // арифметические операции для всевозможных сочетаний аргументов
   friend NumberA  operator+(const NumberA & a, const NumberA & b);
   friend NumberA  operator-(const NumberA & a, const NumberA & b);
   friend NumberA  operator*(const NumberA & a, const NumberA & b);
   friend NumberA  operator/(const NumberA & a, const NumberA & b);
   friend NumberA  operator+(const NumberA & a, double d);
   friend NumberA  operator-(const NumberA & a, double d);
   friend NumberA  operator*(const NumberA & a, double d);
   friend NumberA  operator/(const NumberA & a, double d);
   friend NumberA  operator+(double d, const NumberA & b);
   friend NumberA  operator-(double d, const NumberA & b);
   friend NumberA  operator*(double d, const NumberA & b);
   friend NumberA  operator/(double d, const NumberA & b);
   friend NumberA  operator*(int d, const NumberA & b);
   friend NumberA  operator/(const NumberA & a, int d);

   // элементарные функции
   friend NumberA sinA(NumberA x);

};




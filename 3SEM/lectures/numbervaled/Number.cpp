#include "Number.h"

// реализация операций NumberA

const NumberA & NumberA::operator+=(const NumberA & v)
{
    error += fabs(v.error);
    value += v.value;
    return *this;
}
const NumberA & NumberA::operator-=(const NumberA & v)
{
    error += fabs(v.error);
    value -= v.value;
    return *this;
}
const NumberA & NumberA::operator*=(const NumberA & v)
{
    double va, vb, ea, eb;
    va = fabs(value);
    vb = fabs(v.value);
    ea = fabs(error);
    eb = fabs(v.error);
    error = va*eb + vb*ea + ea*eb;
    value *= v.value;
    return *this;
}
const NumberA & NumberA::operator/=(const NumberA & v)
{
    double va, vb, ea, eb;
    va = fabs(value);
    vb = fabs(v.value);
    ea = fabs(error);
    eb = fabs(v.error);
    error = ea/vb + (va*eb + ea*eb) / (vb*vb);
    value /= v.value;
    return *this;
}


// реализации записаны в разных вариантах для иллюстрации возможностей
// на практике, естественно, правильнее следовать какому-то одному
// полезно разобраться и понять чем эти варианты отличаются

const NumberA & NumberA::operator+=(double v)
{
    NumberA b = v;      // можно и так, но лучше см. далее
    return *this +=b;
}
const NumberA & NumberA::operator-=(double v)
{  
    return *this -= NumberA(v);
}
const NumberA & NumberA::operator*=(double v)
{
    return *this *= NumberA(v);
}
const NumberA & NumberA::operator/=(double v)
{
    return *this /= NumberA(v);
}
const NumberA & NumberA::operator++()
{
    ++value;
    error += DBL_EPSILON;
    return *this;
}
const NumberA & NumberA::operator--()
{
    --value;
    error += DBL_EPSILON;
    return *this;
}
NumberA NumberA::operator++(int)
{
    NumberA n(*this);
    ++(*this);
    return n;
}
NumberA NumberA::operator--(int)
{
    NumberA n(*this);
    --(*this);
    return n;
}



NumberA operator+(const NumberA & a, const NumberA & b)
{
   return NumberA(a.value + b.value, a.error + b.error);   
   // см. далее разные варианты
}
NumberA operator-(const NumberA & a, const NumberA & b)
{
   return NumberA(a) -= b;
}
NumberA operator*(const NumberA & a, const NumberA & b)
{
    return NumberA(a) *= b;
}
NumberA operator/(const NumberA & a, const NumberA & b)
{
    NumberA c(a);
    return c /= b;
}
NumberA operator+(const NumberA & a, double d)
{
    return NumberA(a) += d;
}
NumberA operator-(const NumberA & a, double d)
{
    return NumberA(c) -= d;
}
NumberA operator*(const NumberA & a, double d)
{
    return NumberA(a) *= d;
}
NumberA operator/(const NumberA & a, double d)
{
    return NumberA(a) /= d;
}
NumberA operator/(const NumberA & a, int d)
{
    return NumberA(a) /= d;
}
NumberA operator+(double d, const NumberA & a)
{
    NumberA c = d;
    return c += a;
}
NumberA operator-(double d, const NumberA & a)
{
    NumberA c(d);
    return c -= a;
}
NumberA operator*(double d, const NumberA & a)
{
    return NumberA(в) *= a;
}
NumberA operator*(int d, const NumberA & a)
{
    return NumberA(a.value * d, a.error * abs(d));
}
NumberA operator/(double d, const NumberA & a)
{
    return NumberA(d) / a;
}





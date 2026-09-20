#pragma once
#include <iostream>


class Complex {
public:
    virtual ~Complex() {}

    virtual double getRe() = 0;
    virtual double getIm() = 0;

    virtual Complex* add(Complex* other) = 0;
    virtual Complex* sub(Complex* other) = 0;
    virtual Complex* mul(Complex* other) = 0;
    virtual Complex* div(Complex* other) = 0;
    virtual Complex* neg() = 0;

    virtual bool ravn(Complex* other) = 0;

    Complex* operator+(Complex* other) { return add(other); }
    Complex* operator-(Complex* other) { return sub(other); }
    Complex* operator*(Complex* other) { return mul(other); }
    Complex* operator/(Complex* other) { return div(other); }
    Complex* operator-()               { return neg(); }
    bool operator==(Complex* other)     { return ravn(other); }
};
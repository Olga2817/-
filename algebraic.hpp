#pragma once
#include "complex.hpp"

class AlgebraicComplex : public Complex {
private:
    double re, im;

public:
    AlgebraicComplex(double r = 0, double i = 0) {
        re = r;
        im = i;
    }

    double getRe() { return re; }
    double getIm() { return im; }

    Complex* add(Complex* other) {
        return new AlgebraicComplex(re + other->getRe(), im + other->getIm());
    }

    Complex* sub(Complex* other) {
        return new AlgebraicComplex(re - other->getRe(), im - other->getIm());
    }

    Complex* mul(Complex* other) {
        double a = re, b = im;
        double c = other->getRe(), d = other->getIm();
        return new AlgebraicComplex(a*c - b*d, a*d + b*c);
    }

    Complex* div(Complex* other) {
        double a = re, b = im;
        double c = other->getRe(), d = other->getIm();
        double denom = c*c + d*d;
        return new AlgebraicComplex((a*c + b*d)/denom, (b*c - a*d)/denom);
    }

    Complex* neg() {
        return new AlgebraicComplex(-re, -im);
    }

    bool ravn(Complex* other) {
        return re == other->getRe() && im == other->getIm();
    }
};
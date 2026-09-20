#pragma once
#include "complex.hpp"
#include "algebraic.hpp"
#include <cmath>

class TrigonometricComplex : public Complex {
private:
    double r;
    double phi;

public:
    TrigonometricComplex(double r_ = 0, double phi_ = 0) {
        r = r_;
        phi = phi_;
    }

    double getRe() { return r * std::cos(phi); }
    double getIm() { return r * std::sin(phi); }

    Complex* add(Complex* other) {
        return new AlgebraicComplex(getRe() + other->getRe(),
                                    getIm() + other->getIm());
    }

    Complex* sub(Complex* other) {
        return new AlgebraicComplex(getRe() - other->getRe(),
                                    getIm() - other->getIm());
    }

    Complex* mul(Complex* other) {
        double r2 = std::sqrt(other->getRe()*other->getRe() +
                              other->getIm()*other->getIm());
        double phi2 = std::atan2(other->getIm(), other->getRe());
        return new TrigonometricComplex(r * r2, phi + phi2);
    }

    Complex* div(Complex* other) {
        double r2 = std::sqrt(other->getRe()*other->getRe() +
                              other->getIm()*other->getIm());
        double phi2 = std::atan2(other->getIm(), other->getRe());
        return new TrigonometricComplex(r / r2, phi - phi2);
    }

    Complex* neg() {
        return new TrigonometricComplex(r, phi + 3.14159265358979);
    }

    bool ravn(Complex* other) {
        return getRe() == other->getRe() && getIm() == other->getIm();
    }
};
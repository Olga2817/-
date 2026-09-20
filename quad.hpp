#pragma once
#include "complex.hpp"
#include "algebraic.hpp"
#include "trigonometric.hpp"
#include <cmath>


Complex* solveQuadratic(Complex* a, Complex* b, Complex* c, int root) {
    Complex* b2 = b->mul(b);
    Complex* f  = new AlgebraicComplex(4, 0);
    Complex* ac = a->mul(c);
    Complex* fc = f->mul(ac);
    Complex* D  = b2->sub(fc);

    double dr = D->getRe();
    double di = D->getIm();
    double r  = std::sqrt(std::sqrt(dr*dr + di*di));
    double p  = std::atan2(di, dr) / 2.0;
    Complex* s = new TrigonometricComplex(r, p);

    Complex* t  = new AlgebraicComplex(2, 0);
    Complex* ta = t->mul(a);

    Complex* mb = b->neg();

    Complex* z1 = mb->add(s)->div(ta);

    Complex* z2 = mb->sub(s)->div(ta);

    delete b2; delete f; delete ac; delete fc; delete D;
    delete s; delete t; delete ta; delete mb;

    if (root == 1) { delete z2; return z1; }
    else        { delete z1; return z2; }
}

Complex* evalTrinomial(Complex* a, Complex* b, Complex* c, Complex* z) {
    Complex* z2 = z->mul(z);
    Complex* az = a->mul(z2);
    Complex* bz = b->mul(z);
    Complex* s  = az->add(bz);
    Complex* r  = s->add(c);

    delete z2; delete az; delete bz; delete s;
    return r;
}
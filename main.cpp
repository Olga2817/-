#include "algebraic.hpp"
#include "trigonometric.hpp"
#include "quad.hpp"
#include <iostream>
#include <clocale>

int main() {
    std::setlocale(LC_ALL, "");

    double re1, im1, r2, phi2;
    std::cout << "Введите первое число:\n";
    std::cout << "  Re: "; std::cin >> re1;
    std::cout << "  Im: "; std::cin >> im1;
    std::cout << "Введите второе число (тригонометрическое):\n";
    std::cout << "  r   (модуль):  "; std::cin >> r2;
    std::cout << "  phi (аргумент): "; std::cin >> phi2;

    Complex* a = new AlgebraicComplex(re1, im1);
    Complex* b = new TrigonometricComplex(r2, phi2);

    std::cout << "\na = " << a->getRe() << " + " << a->getIm() << "i\n";
    std::cout << "b = " << b->getRe() << " + " << b->getIm() << "i\n";

    Complex* sum  = *a + b;
    Complex* diff = *a - b;
    Complex* prod = *a * b;
    Complex* quot = *a / b;
    Complex* negA = -(*a);

    std::cout << "\na + b = " << sum->getRe()  << " + " << sum->getIm()  << "i\n";
    std::cout << "a - b = " << diff->getRe() << " + " << diff->getIm() << "i\n";
    std::cout << "a * b = " << prod->getRe() << " + " << prod->getIm() << "i\n";
    std::cout << "a / b = " << quot->getRe() << " + " << quot->getIm() << "i\n";
    std::cout << "-a    = " << negA->getRe() << " + " << negA->getIm() << "i\n";

    if (*a == b) std::cout << "\na и b равны\n";
    else         std::cout << "\na и b не равны\n";

    double ar, ai, br, bi, cr, ci;
    std::cout << "A (старший, при z^2):\n";
    std::cout << "  Re: "; std::cin >> ar;
    std::cout << "  Im: "; std::cin >> ai;
    std::cout << "B (средний, при z):\n";
    std::cout << "  Re: "; std::cin >> br;
    std::cout << "  Im: "; std::cin >> bi;
    std::cout << "C (свободный член):\n";
    std::cout << "  Re: "; std::cin >> cr;
    std::cout << "  Im: "; std::cin >> ci;

    Complex* A = new AlgebraicComplex(ar, ai);
    Complex* B = new AlgebraicComplex(br, bi);
    Complex* C = new AlgebraicComplex(cr, ci);

    Complex* z1 = solveQuadratic(A, B, C, 1);
    Complex* z2 = solveQuadratic(A, B, C, 2);

    std::cout << "\nКорень 1: " << z1->getRe() << " + " << z1->getIm() << "i\n";
    std::cout << "Корень 2: " << z2->getRe() << " + " << z2->getIm() << "i\n";

    double zr, zi;
    std::cout << "Введите z для вычисления трёхчлена:\n";
    std::cout << "  Re: "; std::cin >> zr;
    std::cout << "  Im: "; std::cin >> zi;
    Complex* z = new AlgebraicComplex(zr, zi);

    Complex* val = evalTrinomial(A, B, C, z);
    std::cout << "Значение a*z^2 + b*z + c = "
              << val->getRe() << " + " << val->getIm() << "i\n";

    delete a; delete b;
    delete sum; delete diff; delete prod; delete quot; delete negA;
    delete A; delete B; delete C;
    delete z1; delete z2;
    delete z; delete val;

    return 0;
}
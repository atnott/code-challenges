#include"parabola.hpp"
#include<iostream>

Parabola::Parabola(double a_coef, double b_coef, double c_coef) : a(a_coef), b(b_coef), c(c_coef) {}

double Parabola::evaluate(double x) const {
    return a * x * x + b * x + c;
}

void Parabola::print() const {
    std::cout << "Парабола: f(x) = " << a << "x^2";
    if (b >= 0) std::cout << " + " << b << "x";
    else std::cout << " - " << std::abs(b) << "x";

    if (c >= 0) std::cout << " + " << c;
    else std::cout << " - " << std::abs(c);
    std::cout << std::endl;
}
#include "exponenta.hpp"

Exponenta::Exponenta(double coef_a, double coef_b, double coef_c) : a(coef_a), b(coef_b), c(coef_c) {}

double Exponenta::evaluate(double x) const {
    return a * std::exp(b * x) + c;
}

void Exponenta::print() const {
    std::cout << "Экспонента: f(x) = " << a << " * e^(" << b << "x)";
    if (c >= 0) std::cout << " + " << c;
    else std::cout << " - " << std::abs(c);
    std::cout << std::endl;
}
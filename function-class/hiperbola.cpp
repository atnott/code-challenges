#include"hiperbola.hpp"
#include<iostream>

Hiperbola::Hiperbola(double coef_k, double coef_c) : k(coef_k), c(coef_c) {}

double Hiperbola::evaluate(double x) const {
    if (x == 0) {
        throw std::invalid_argument("x must be positive");
    }
    return k / x + c;
}

void Hiperbola::print() const {
    std::cout << "Гипербола: f(x) = " << k << "/x";
    if (c >= 0) std::cout << " + " << c;
    else std::cout << " - " << std::abs(c);
    std::cout << std::endl;
}

#pragma once
#include"function.hpp"

class Parabola : public Function {
    double a, b, c;
public:
    Parabola(double a_coef, double b_coef, double c_coef);
    double evaluate(double x) const;
    void print() const;
};

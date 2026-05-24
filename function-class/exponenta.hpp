#pragma once
#include "function.hpp"

class Exponenta : public Function {
private:
    double a, b, c;

public:
    Exponenta(double coef_a, double coef_b, double coef_c);

    double evaluate(double x) const;
    void print() const;
};
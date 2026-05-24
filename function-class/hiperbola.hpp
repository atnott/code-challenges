#pragma once
#include "function.hpp"

class Hiperbola : public Function {
private:
    double k, c;

public:
    Hiperbola(double coef_k, double coef_c);

    double evaluate(double x) const;
    void print() const;
};

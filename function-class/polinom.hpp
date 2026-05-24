#pragma once
#include"function.hpp"
#include<vector>

class Polinom : public Function {
private:
    std::vector<double> coefficients;

public:
    Polinom(const std::vector<double>& coeffs);

    double evaluate(double x) const;
    void print() const;
};
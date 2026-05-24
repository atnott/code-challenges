#pragma once

class Function {
public:
    virtual ~Function();
    virtual double evaluate(double x) const = 0;
    virtual void print() const = 0;

    double derivative(double x, double h = 1e-6) const;
    double integrate(double a, double b, int steps = 1000) const;
    double find_min(double a, double b, double step = 1e-4) const;
    double find_max(double a, double b, double step = 1e-4) const;
};
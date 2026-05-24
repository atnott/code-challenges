#include "function.hpp"

Function::~Function() {}

double Function::derivative(double x, double h) const {
    return (evaluate(x + h) - evaluate(x - h)) / (2.0 * h);
}

double Function::integrate(double a, double b, int steps) const {
    double h = (b - a) / steps;
    double sum = 0.5 * (evaluate(a) + evaluate(b));
    for (int i = 1; i < steps; i++) {
        sum += evaluate(a + i * h);
    }
    return sum * h;
}

double Function::find_min(double a, double b, int steps) const {
    double h = (b - a) / steps;
    double min_val = evaluate(a);

    for (int i = 1; i <= steps; ++i) {
        double current = evaluate(a + i * h);
        if (current < min_val) {
            min_val = current;
        }
    }
    return min_val;
}

double Function::find_max(double a, double b, int steps) const {
    double h = (b - a) / steps;
    double max_val = evaluate(a);

    for (int i = 1; i <= steps; ++i) {
        double current = evaluate(a + i * h);
        if (current > max_val) {
            max_val = current;
        }
    }
    return max_val;
}
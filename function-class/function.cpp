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

double Function::find_min(double a, double b, double step) const {
    double min_value = evaluate(a);
    for (double x = a + step; x <= b; x += step) {
        double curr = evaluate(x);
        if (curr < min_value) {
            min_value = curr;
        }
    }
    return min_value;
}

double Function::find_max(double a, double b, double step) const {
    double max_value = evaluate(a);
    for (double x = a + step; x <= b; x += step) {
        double curr = evaluate(x);
        if (curr > max_value) {
            max_value = curr;
        }
    }
    return max_value;
}
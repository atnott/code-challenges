#include "polinom.hpp"

Polinom::Polinom(const std::vector<double>& coeffs) : coefficients(coeffs) {}

double Polinom::evaluate(double x) const {
    if (coefficients.empty()) return 0.0;

    double result = 0.0;
    for (auto it = coefficients.rbegin(); it != coefficients.rend(); ++it) {
        result = result * x + (*it);
    }
    return result;
}

void Polinom::print() const {
    if (coefficients.empty()) {
        std::cout << "Полином: f(x) = 0" << std::endl;
        return;
    }

    std::cout << "Полином " << coefficients.size() - 1 << "-й степени: f(x) = ";
    bool first = true;

    for (int i = coefficients.size() - 1; i >= 0; --i) {
        double coeff = coefficients[i];
        if (std::abs(coeff) < 1e-9) continue;

        if (!first && coeff > 0) std::cout << " + ";
        if (coeff < 0) std::cout << " - ";
        if (first && coeff < 0) {}

        if (std::abs(coeff) != 1.0 || i == 0) {
            std::cout << std::abs(coeff);
        }

        if (i > 0) {
            std::cout << "x";
            if (i > 1) std::cout << "^" << i;
        }
        first = false;
    }
    std::cout << std::endl;
}
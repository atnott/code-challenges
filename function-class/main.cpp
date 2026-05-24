#include<iostream>
#include"function.hpp"

using std::cout;
using std::endl;

class TestParabola : public Function {
public:
    double evaluate(double x) const {
        return x * x - 4.0 * x + 3.0;
    }

    void print() const {
        cout << "f(x) = x^2 - 4x + 3" << endl;
    }
};

int main() {
    Function* func = new TestParabola();

    func->print();

    // вычисление значения в точке
    double x = 3.0;
    cout << func->evaluate(x) << endl;

    // производная
    cout << func->derivative(x) << endl;

    // макс и мин на отрезке
    double left = 0.0, right = 4.0;
    cout << func->find_min(left, right) << endl;
    cout << func->find_max(left, right) << endl;

    // интегрирование на отрезке
    cout << func->integrate(left, right) << endl;

    delete func;
    return 0;
}
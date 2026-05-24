#include"function.hpp"
#include"parabola.hpp"
#include<iostream>

using std::cout;
using std::endl;

int main() {

    Function* func = new Parabola(1.0, -4.0, 3.0);
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
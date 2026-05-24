#include"function.hpp"
#include"parabola.hpp"
#include"hiperbola.hpp"
#include"polinom.hpp"
#include"exponenta.hpp"

#include<iostream>
#include <vector>

using std::cout;
using std::endl;

int main() {

    std::vector<Function*> functions;

    functions.push_back(new Parabola(1.0, -4.0, 3.0));
    functions.push_back(new Hiperbola(2.0, 1.0));
    functions.push_back(new Exponenta(1.0, 0.5, -2.0));
    functions.push_back(new Polinom({-6.0, 11.0, -6.0, 1.0}));

    for (const Function* func : functions) {
        func->print();

        double x = 2.0;
        cout << "  Значение f(" << x << ")     = " << func->evaluate(x) << endl;
        cout << "  Производная f'(" << x << ")  = " << func->derivative(x) << endl;

        cout << "  Минимум на [1, 3]    = " << func->find_min(1.0, 3.0) << endl;
        cout << "  Максимум на [1, 3]   = " << func->find_max(1.0, 3.0) << endl;

        cout << "  Интеграл на [1, 2]   = " << func->integrate(1.0, 2.0) << endl;
    }

    for (Function* func : functions) {
        delete func;
    }

    return 0;
}

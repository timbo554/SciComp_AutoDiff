#include <iostream>
#include <cmath>
#include "auto_diff.hpp"

using namespace std;


ForwardDiff<double> F(double x)
{
    ForwardDiff<double> result(x, 1);
    return exp(sin(result) + cos(result) / log(result));
}
int main()
{

    ForwardDiff<double> a(2.0, 1);
    ForwardDiff<double> b(5.0, 1);

    cout << a * a << endl;
    cout << a / b << endl;
    ForwardDiff<double> c(3.41, 1);
    cout << sin(c) << endl;
    cout << cos(c) << endl;
    cout << log(c) << endl;
    cout << exp(c) << endl;
    cout << pow(c, 1) << endl;
    cout << pow(c, 0) << endl;

    ForwardDiff<double> d(2, 1);
    cout << pow(d, 3) << endl;

    ForwardDiff<double> e(2, 1);
    cout << exp(sin(e) + cos(c) / log(c)) << endl;

    cout << F(3.0) << endl;
    
    

}
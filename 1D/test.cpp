#include <iostream>
#include <cmath>
#include "auto_diff.hpp"

using namespace std;


ForwardDiff<double> F(vector<double> const& vars, vector<double> const & diffs)
{
    vector<ForwardDiff<double>> fd_vars = create_fd_vars(vars, diffs);

    return exp(fd_vars[0] * fd_vars[1]) + fd_vars[0];
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

    vector<double> vars = {1.0, 3.0};
    vector<double> diffs1 = {1.0, 0.0};
    vector<double> diffs2 = {0.0, 1.0};
    cout << F(vars, diffs1) << endl;
    cout << F(vars, diffs2) << endl;


}
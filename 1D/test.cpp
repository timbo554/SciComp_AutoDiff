#include <iostream>
#include <cmath>
#include "auto_diff.hpp"

using namespace std;


void F(vector<vector<double>> const& vars, vector<vector<double>> const& diffs)
{
    vector<ForwardDiff<double>> fd_vars;
    for (auto i = 0; i < vars.size(); i++)
    {
        fd_vars = create_fd_vars(vars[i], diffs[i]);
        cout << exp(fd_vars[0] * fd_vars[1]) + fd_vars[0] << endl;
    }
     
}
int main()
{
    /*
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
    */
    vector<vector<double>> vars = {{1.0, 3.0},
                                   {-7.0, 14.6}};
    vector<vector<double>> diffs = {{1.0, 0.0},
                                     {0.0, 1.0}};
    F(vars, diffs);
 


}
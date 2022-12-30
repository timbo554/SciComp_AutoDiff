#include <iostream>
#include "auto_diff.hpp"

using namespace std;

int main()
{

    ForwardDiff<double> a(2.0, 1);
    ForwardDiff<double> b(5.0, 1);

    cout << a * a << endl;
}
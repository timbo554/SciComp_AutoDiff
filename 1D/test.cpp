#include <iostream>
#include "auto_diff.hpp"

using namespace std;

int main()
{
    AutoDiff<int> a(4);
    AutoDiff<int> b(3);
    AutoDiff<int> v = a + b;
}
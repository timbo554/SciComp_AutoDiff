#include <string>
#include <iostream>

#ifndef AUTO_DIFF_H
#define AUTO_DIFF_H

template <typename T>
class AutoDiff
{
    T value;
    // ComputationalGraph<T> c_graph;
    public:
        explicit AutoDiff(T value): value(value) {}
        AutoDiff() {}
        friend AutoDiff operator+(AutoDiff a, AutoDiff b)
        {
            AutoDiff<T> v;
            v.value = a.value + b.value;
            return v;
        }

        friend std::ostream &operator<<(std::ostream &os, AutoDiff v) 
        {
            os << v.value;
            return os;
        }
};

template <typename T>
class ForwardDiff: AutoDiff<T>
{
    T 
};
#endif // AUTO_DIFF_H
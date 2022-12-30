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
        explicit AutoDiff(T value): value(value) {};
        AutoDiff<T>(): value(0) {};
        AutoDiff<T>(AutoDiff<T> const &) = default;
        AutoDiff<T>& operator=(AutoDiff<T> const& old_auto_diff) = default;


        AutoDiff<T> operator+(AutoDiff<T> const& a)
        {
            AutoDiff<T> v;
            v.value = this->value + a.value;
            return v;
        }

        friend std::ostream &operator<<(std::ostream &os, AutoDiff<T> v) 
        {
            os << v.value;
            return os;
        }
};


#endif // AUTO_DIFF_H
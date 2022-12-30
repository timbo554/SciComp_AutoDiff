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

template <typename T>
class ForwardDiff
{
    T value;
    T diff;

    public:
        ForwardDiff<T>(): value(0), diff(1) {};
        ForwardDiff<T>(T value, T diff): value(value), diff(diff) {};
        ForwardDiff<T>(ForwardDiff const& a) = default;
        ForwardDiff<T> operator+(ForwardDiff<T> const& a)
        {
            ForwardDiff<T> v;
            v.value = this->value + a.value;
            v.diff = this->diff + a.diff;
            return v;
        }
        ForwardDiff<T> operator*(ForwardDiff<T> const &a)
        {
            ForwardDiff<T> v;
            v.value = this->value * a.value;
            v.diff = this->diff * a.value + this->value * a.diff;
            return v;
        }
        friend std::ostream &operator<<(std::ostream &os, ForwardDiff<T> v) 
        {
                os << v.value;
                os << " ";
                os << v.diff;
                return os;
        }
};


#endif // AUTO_DIFF_H
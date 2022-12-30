#include <string>
#include <iostream>
#include <cmath>
#include <vector>

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
        ForwardDiff<T>(): value(0), diff(0) {};
        ForwardDiff<T>(T value, T diff): value(value), diff(diff) {};
        ForwardDiff<T>(ForwardDiff const& a) = default;

        ForwardDiff<T> operator+(ForwardDiff<T> const& a)
        {
            ForwardDiff<T> v;
            v.value = this->value + a.value;
            v.diff = this->diff + a.diff;
            return v;
        }

        ForwardDiff<T> operator-(ForwardDiff<T> const& a)
        {
            ForwardDiff<T> v;
            v.value = this->value - a.value;
            v.diff = this->diff - a.diff;
            return v;
        }

        ForwardDiff<T> operator*(ForwardDiff<T> const &a)
        {
            ForwardDiff<T> v;
            v.value = this->value * a.value;
            v.diff = this->diff * a.value + this->value * a.diff;
            return v;
        }

        ForwardDiff<T> operator/(ForwardDiff<T> const &a)
        {
            ForwardDiff<T> v;
            v.value = this->value / a.value;
            v.diff = (this->diff * a.value - this->value * a.diff) / std::pow(a.value, 2);
            return v;
        }

        friend std::ostream &operator<<(std::ostream &os, ForwardDiff<T> v) 
        {
                os << v.value;
                os << " ";
                os << v.diff;
                return os;
        }

        friend ForwardDiff<T> sin(ForwardDiff<T> const a)
        {
            ForwardDiff<T> v;
            v.value = std::sin(a.value);
            v.diff = std::cos(a.value) * a.diff;
            return v;
        }

        friend ForwardDiff<T> cos(ForwardDiff<T> const a)
        {
            ForwardDiff<T> v;
            v.value = std::cos(a.value);
            v.diff = -std::sin(a.value) * a.diff;
            return v;
        }

        friend ForwardDiff<T> log(ForwardDiff<T> const a)
        {
            ForwardDiff<T> v;
            v.value = std::log(a.value);
            v.diff = a.diff / a.value ;
            return v;
        }

        friend ForwardDiff<T> exp(ForwardDiff<T> const a)
        {
            ForwardDiff<T> v;
            v.value = std::exp(a.value);
            v.diff = std::exp(a.value) * a.diff;
            return v;
        }

        friend ForwardDiff<T> pow(ForwardDiff<T> const a, double const exponent)
        {
            ForwardDiff<T> v;
            if (exponent != 0)
            {
                v.value = std::pow(a.value, exponent);
                v.diff = (exponent) * std::pow(a.value, exponent - 1) * a.diff;
            }
            else
            {
                v.value = 0;
                v.diff = 0;
            }
            return v;
        }
};

template <typename T>
struct Diff
{
    T value;
    T diff;
    int index;
};

template <typename T>
class VecDiff
{
    std::vector<Diff<T>> vars;

    public: 
        VecDiff(std::vector<T> values, std::vector<T> diff, std::vector<int> index)
        {
            for (auto i = 0; i < values.length(); i++)
            {
                Diff<T> tmp(values[i], diff[i], index[i]);
                vars.push(tmp);
            }
        }

};

template <typename T>
VecDiff<T> operator+(Diff<T> b)
{
    VecDiff<T> v;
    return v;
}

#endif // AUTO_DIFF_H
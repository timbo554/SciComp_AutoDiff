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
    T value; // f(x)
    T diff; // f'(x)

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
                os << "F(x) = " << v.value << std::endl;
                os << "F'(x) * x' = " << v.diff << std::endl;
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
std::vector<ForwardDiff<T>> create_fd_vars(std::vector<T> const &vars,
                                          std::vector<T> const &diffs)
{
            // TODO check for equal length


    std::vector<ForwardDiff<T>> fd_vars;

    for (auto i = 0; i < vars.size(); i++)
    {
        fd_vars.push_back(ForwardDiff<T> (vars[i], diffs[i]));
    }
    return fd_vars;
}

#endif // AUTO_DIFF_H
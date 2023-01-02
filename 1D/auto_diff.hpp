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

    Diff(T value, T diff, int index): value(value), diff(diff), index(index) {};
};

template <typename T>
class VecDiff
{
    T value;
    std::vector<T> diffs;
    std::vector<int> indices;

    public: 
        explicit VecDiff(T value, std::vector<T> diffs)
        {
            value = value;
            for (auto i = 0; i < diffs.length(); i++)
            {
                diffs.push_back(diffs[i]);
                indices.push_back(i);
            }
        }
        explicit VecDiff(T value): value(value) {};
        explicit VecDiff() = default;
        explicit VecDiff(VecDiff const &) = default;
        
        
        friend std::ostream &operator<<(std::ostream &os, VecDiff<T> v) 
        {
            os << "Values: ";
            for (auto value: v.values)
            {
                os << v << " ";
            }
            os << std::endl;
            
            os << "Diffs";
            for (auto diff: v.diffs)
            {
                os << diff << " ";
            }
            os << std::endl;
            
            return os;
        }

        set_diff_and_index(T diff_value, int index)
        {
            diffs.push_back(diff_value);
            indices.push_back(index);
        }
};

template <typename T>
VecDiff<T> operator+(Diff<T> a, Diff<T> b)
    {
        VecDiff<T> v(a.value + b.value);

        if (a.index == b.index)
        {
            v.diffs.push_back(a.diff + b.diff);
            v.indices.push_back(a.index);
        }
        else
        {
            v.diffs.push_back(a.diff);
            v.indices.push_back(a.index);

            v.diffs.push_back(b.diff);
            v.indices.push_back(b.index);
        }
        return v;
    }

#endif // AUTO_DIFF_H
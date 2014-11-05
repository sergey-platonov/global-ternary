#include "constructed_ternary.h"
#include <stdexcept>

namespace sequences
{

constructed_ternary_pulse::constructed_ternary_pulse(ternary_pulse &left, ternary_pulse &right)
{
    m_left = &left;
    m_right = &right;
    m_sym = zero;
    m_even = true;
}

constructed_ternary_pulse::constructed_ternary_pulse(ternary_pulse &left,
                                                     ternary_pulse::value_type sym, ternary_pulse &right)
{
    m_left = &left;
    m_right = &right;
    m_sym = sym;
    m_even = false;
}

constructed_ternary_pulse::constructed_ternary_pulse(ternary_pulse &left, char sym, ternary_pulse &right)
{
    m_left = &left;
    m_right = &right;
    m_sym = to_ternary( std::string(1, sym) );
    m_even = false;
}

ternary_pulse::value_type constructed_ternary_pulse::operator[](std::size_t n)
{
    if (n > size())
        return zero;

    if ((n == left().size()) && !even())
        return sym();

    if (n < left().size())
        return left()[n];
    else
        if (even())
            return right()[ n - left().size() ];
        else
            return right()[ n - left().size() - 1];
}

ternary_pulse::value_type constructed_ternary_pulse::operator[](std::size_t n) const
{
    if (n > size())
        return zero;

    if ((n == left().size()) && !even())
        return sym();

    if (even())
        return right()[ n - left().size() ];
    else
        return right()[ n - left().size() - 1];
}

std::size_t constructed_ternary_pulse::size() const
{
    return left().size() + right().size() + (even() ? 0 : 1);
}

ternary_correlation constructed_ternary_pulse::half_cf() const
{
    if (left().size() != right().size())
    {
        throw std::logic_error("half_cf() is only acceptable if left.size is equal to right.size");
    }
    if (even())
        return ternary_correlation(left(), right());
    else
        return ternary_correlation(left() | sym() | right());
}

constructed_ternary_pulse::operator ternary_pulse() const
{
    if (even())
        return ternary_pulse(left() | right());
    else
        return ternary_pulse(left() | sym() | right());
}

ternary_pulse &constructed_ternary_pulse::left()
{
    return *m_left;
}

ternary_pulse &constructed_ternary_pulse::right()
{
    return *m_right;
}

const ternary_pulse &constructed_ternary_pulse::left() const
{
    return *m_left;
}

const ternary_pulse &constructed_ternary_pulse::right() const
{
    return *m_right;
}

}

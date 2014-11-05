#ifndef CONSTRUCTED_TERNARY_H
#define CONSTRUCTED_TERNARY_H
#include "ternary.h"
#include "correlation.h"


namespace sequences
{

class constructed_ternary_pulse
{
    ternary_pulse *m_left;
    ternary_pulse *m_right;
    ternary_pulse::value_type m_sym;
    bool m_even;
public:
    constructed_ternary_pulse(ternary_pulse &left, ternary_pulse &right);
    constructed_ternary_pulse(ternary_pulse &left, ternary_pulse::value_type sym, ternary_pulse &right);
    constructed_ternary_pulse(ternary_pulse &left, char sym, ternary_pulse &right);

    ternary_pulse::value_type operator[] (std::size_t n);
    ternary_pulse::value_type operator[] (std::size_t n) const;

    std::size_t size() const;

    // this function is only acceptable if left.size == right.size
    ternary_correlation half_cf() const;

    operator ternary_pulse() const;

    const ternary_pulse &left() const;
    const ternary_pulse &right() const;

protected:
    ternary_pulse &left();
    ternary_pulse &right();

    bool even() const {return m_even;}
    ternary_pulse::value_type sym() const { return m_sym;}

};

}
#endif // CONSTRUCTED_TERNARY_H

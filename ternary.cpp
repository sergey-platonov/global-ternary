#include "ternary.h"
#include "strutils.h"
#include <sstream>
#include <algorithm>

namespace sequences
{

TernaryAlphabet to_ternary(long s)
{
    if (s < 0)
        return minus;
    if (s > 0)
        return plus;
    return zero;
}

TernaryAlphabet to_ternary(std::string s)
{
    if (s.length() > 1)
    {
        str::trim(s, " \t+");
        long i = std::atoi(s.c_str());
        return to_ternary(i);
    }
    else
    {
        return to_ternary(s[0]);
    }
}

TernaryAlphabet to_ternary(char c)
{
    switch (c)
    {
    case '-': return minus;
    case '+': return plus;
    case '0': return zero;
    }
    return zero;
}

ternary_base::ternary_base()
{
}

ternary_base::ternary_base(std::string s)
{
    if (s.find(' ') != s.npos)
    {
        auto v = str::split(s, ' ');
        for (auto &t: v)
            push_back( to_ternary(t) );
    }
    else
    {
        for (std::size_t i = 0 ; i < s.length() ; i++)
            push_back(to_ternary(s[i]));
    }
}

ternary_base::ternary_base(const std::vector<TernaryAlphabet> &v) : std::vector<TernaryAlphabet>(v)
{
}

ternary_base::~ternary_base()
{
}

void ternary_base::append(const std::vector<TernaryAlphabet> &v)
{
    insert(begin() + size(), v.begin(), v.end());
    m_cf.reset();
}

std::shared_ptr<ternary_base::corr> ternary_base::cf()
{
    if (m_cf.get() == nullptr)
    {
        m_cf.reset( new corr(*this) );
    }
    return m_cf;
}

std::shared_ptr<ternary_base> ternary_base::ptr()
{
    return shared_from_this();
}

std::size_t ternary_base::weight() const
{
    return size() - std::count(this->begin(), this->end(), zero);
}

void ternary_base::reset_cf()
{
    m_cf.reset();
}

ternary_base::value_type ternary_pulse::operator[](ternary_base::size_type n)
{
    if (n >= size())
        return zero;
    else
        return ternary_base::at(n);
}

ternary_base::value_type ternary_pulse::operator[](ternary_base::size_type n) const
{
    if (n >= size())
        return zero;
    else
        return ternary_base::at(n);
}

ternary_base::value_type ternary_cycle::operator[](ternary_base::size_type n)
{
    if (n >= size())
        return at( n % size() );
    else
        return at(n);
}

ternary_base::value_type ternary_cycle::operator[](ternary_base::size_type n) const
{
    if (n >= size())
        return at( n % size() );
    else
        return at(n);
}

TernaryAlphabet operator-(TernaryAlphabet a)
{
    switch (a) {
    case minus: return plus;
    case plus: return minus;
    case zero: return zero;
    }
}

}


std::ostream &operator <<(std::ostream &os, sequences::TernaryAlphabet a)
{
    switch (a) {
    case sequences::minus: os << "-"; break;
    case sequences::plus: os << "+"; break;
    case sequences::zero: os << "0"; break;
    }
    return os;
}
